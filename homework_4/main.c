#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct node {
    int vertex;
    struct node * next;
};

struct Graph {
    int numVertices;
    int * powerVertices;
    struct node** adjLists;
};

struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = malloc(vertices * sizeof(struct node*));
    
    graph->powerVertices = malloc(vertices * sizeof(int));
    
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    
    return graph;
}

void addEdge(struct Graph * graph, int src, int dest) {
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    (graph->powerVertices[src])++;
    
    if (src != dest) {
        newNode = createNode(src);
        newNode->next = graph->adjLists[dest];
        graph->adjLists[dest] = newNode;
        (graph->powerVertices[dest])++;
    } else {
        (graph->powerVertices[dest])++;
    }
}

void removeEdge(struct Graph * graph, int src, int dest) {
    struct node* prev = NULL;
    struct node* temp = graph->adjLists[src];
    while (temp->vertex != dest) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == NULL)
        graph->adjLists[src] = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    (graph->powerVertices[src])--;
    
    if (src != dest) {
        struct node* prev = NULL;
        struct node* temp = graph->adjLists[dest];
        while (temp->vertex != src) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL)
            graph->adjLists[dest] = temp->next;
        else
            prev->next = temp->next;
        free(temp);
        (graph->powerVertices[dest])--;
    } else {
        (graph->powerVertices[src])--;
    }
}

int countMaxPowerVertex(struct Graph * graph) {
    int max = 0, vertex;
    for (int v = 0; v < graph->numVertices; v++) {
        if (graph->powerVertices[v] > max) {
            max = graph->powerVertices[v];
            vertex = v;
        }
    }
    return vertex;
}

void printGraph(struct Graph * graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        printf("Vertex %d -> ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        puts("");
    }
}

void destroyGraph(struct Graph * graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        if (graph->adjLists[v] == NULL)
            continue;
        struct node* curr = graph->adjLists[v];
        struct node* next = curr->next;
        while (curr->next != NULL) {
            free(curr);
            curr = next;
            next = curr->next;
        }
        free(curr);
    }
    free(graph);
}

void captureGraph(struct Graph* graph, const char * filename) {
    FILE *f_input;
    f_input = fopen(filename, "r");
    if (f_input == NULL)
        exit(EXIT_FAILURE);
    int src, dest;
    char line[10] = {0};
    while (fgets(line, 10, f_input)) {
        sscanf(line, "%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    fclose(f_input);
}

int countNodes(const char * filename) {
    FILE *f_input;
    f_input = fopen(filename, "r");
    if (f_input == NULL)
        exit(EXIT_FAILURE);

    char line[10] = {0};
    char prev_node;
    int src;

    while (fgets(line, 10, f_input)) {
        if (line[0] == '\n')
            break;
        if (line[0] != prev_node) {
            sscanf(line, "%d", &src);
            prev_node = line[0];
        }
    }
    fclose(f_input);
    return src + 1;
}

void drawGraph(struct Graph* graph, const char * filename) {
    FILE * f_out;
    f_out = fopen(filename, "w");
    if (f_out == NULL)
        exit(EXIT_FAILURE);
    
    fprintf(f_out, "graph mat {\n");
    fprintf(f_out, "label = \"Max power vertex - %d\"\n", countMaxPowerVertex(graph));
    for (int node_i = 0; node_i < graph->numVertices; node_i++)
        fprintf(f_out, "%d\n", node_i);
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        while (temp) {
            if (temp->vertex >= v)
                fprintf(f_out, "%d -- %d;\n", v, temp->vertex);
            temp = temp->next;
        }
    }
    fprintf(f_out, "}");
    fclose(f_out);
}

int main(int argc, char * argv[]) {
    if (argc == 1) {
        puts("Usage: ./main path_to_matrix_file.txt");
        exit(1);
    }
    
    struct Graph* graph = createGraph(countNodes(argv[1]));
    
    captureGraph(graph, argv[1]);
    
    if (argc > 2) {
        int src, dest;
        for (int i = 2; i < argc; i = i + 2) {
            sscanf(argv[i], "%d", &src);
            sscanf(argv[i + 1], "%d", &dest);
            removeEdge(graph, src, dest);
        }
    }
    
    const char * output_config_filename = "dot.config";
    drawGraph(graph, output_config_filename);
    destroyGraph(graph);
    
    system("dot dot.config -Tpng -o out.png");
    system("open out.png");
    
    return 0;
}
