#include <stdio.h>
#include <stdlib.h>


struct node {
    int vertex;
    struct node * next;
};
struct node * createNode(int);

struct Graph {
    int numVertices;
    struct node** adjLists;
};

struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createAGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = malloc(vertices * sizeof(struct node*));
    
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    
    return graph;
}

void addEdge(struct Graph * graph, int s, int d) {
    struct node* newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;
}

void printGraph(struct Graph * graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        printf("Vertex %d -> ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void destroyGraph(struct Graph * graph) {
    for (int v = 0; v < graph->numVertices; v++) {
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
    int n = 0;

    while (fgets(line, 10, f_input)) {
        if (line[0] == '\n')
            break;
        if (line[0] != prev_node) {
            n++;
            prev_node = line[0];
        }
    }
    fclose(f_input);
    return n;
}

void drawGraph(struct Graph* graph, const char * filename) {
    FILE * f_out;
    f_out = fopen(filename, "w");
    if (f_out == NULL)
        exit(EXIT_FAILURE);
    
    fprintf(f_out, "graph mat {\n");
    for (int node_i = 0; node_i < graph->numVertices; node_i++)
        fprintf(f_out, "%d\n", node_i);
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        while (temp) {
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
    
    struct Graph* graph = createAGraph(countNodes(argv[1]));
    
    captureGraph(graph, argv[1]);
    
    printGraph(graph);
    
    const char * output_config_filename = "dot.config";
    
    drawGraph(graph, output_config_filename);
    
    destroyGraph(graph);
    
    system("dot dot.config -Tpng -o out.png");
    system("open out.png");
    
    return 0;
}
