//
//  homework_1.c
//  flita
//
//  Created by Тихон on 03.03.2022.
//

#include <stdlib.h>
#include <stdio.h>


typedef struct IntSet {
    int value;
    struct IntSet *next;
} intSet;


intSet *defineIntSet(int value) {
    intSet *start = malloc(sizeof(intSet));
    start->value = value;
    return start;
}

int _isContains(int value, intSet *i) {
    while (i!=NULL) {
        if (i->value == value) {
            return 1;
        }
        
        i = i->next;
    }
    
    return 0;
}

void insert(int value, intSet *i) {
    if (_isContains(value, i)) {
        fprintf(stderr, "Set already contains this value: `%d`\n", value);
        return;
    }
    
    while (i->next!=NULL) { i = i->next; }
    
    intSet *next = malloc(sizeof(intSet));
    next->value = value;
    i->next = next;
}

intSet *removeValueFromIntSet(int value, intSet *i) {
    if (!_isContains(value, i)) {
        fprintf(stderr, "Can not remove value `%d`, not found in set.\n", value);
        return i;
    }
    
    intSet *outIntSet = i;
    intSet *previous = NULL;
    while (i->value!=value) {
        previous = i;
        i = i->next;
    }
    
    if (previous!=NULL) {
        previous->next = i->next;
    } else {
        outIntSet = i->next; //  if it is one element set there would bug
    }
    free(i);
    
    return outIntSet;
}

void releaseIntSet(intSet *i) {
    intSet *next = NULL;
    for (; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}

void printIntSet(intSet *i) {
    printf("<");
    while (i!=NULL) {
        if (i->next != NULL) {
            printf("%d, ", i->value);
        } else {
            printf("%d", i->value);
        }
        i = i->next;
    }
    printf(">\n");
}

int convertDecrimalToBinary(int value, int *output) {
    int a[100], i;
    
    for (i = 0; value > 0; i++) {
        a[i] = value % 2;
        value = value / 2;
    }
    
    int j = 0;
    for (i = i - 1; i >= 0; i--) {
        output[j] = a[i];
        j++;
    }
    
    return j; // return lenth of binary string
}

void printBinaryArray(int *array, int lenth) {
    for (int i = 0; i < lenth; i++) {
        printf("%d", array[i]);
    }
}

void printBoolSet(intSet * i){
    printf("<");
    while (i!=NULL) {
        int binary[100];
        int lenth = convertDecrimalToBinary(i->value, binary);
        printBinaryArray(binary, lenth);
        
        if (i->next != NULL) {
            printf(", ");
        }
        i = i->next;
    }
    printf(">\n");
}

int main(int argc, const char * argv[]) {
    intSet *intset = NULL;
    char ch;
    int n;
    while (1) {
        printf("> ");
        ch = getchar();
        
        switch (ch) {
            case 'i':
                scanf("%d", &n);
                if (intset == NULL) {
                    intset = defineIntSet(n);
                    puts("Created set.");
                } else {
                    insert(n, intset);
                }
                break;
            case 'r':
                scanf("%d", &n);
                if (intset == NULL)
                    puts("Add something first, set is empty.");
                else
                    intset = removeValueFromIntSet(n, intset);
                break;
            case 'p':
                printIntSet(intset);
                break;
            case 'q':
                releaseIntSet(intset);
                goto exit_loop;
                break;
            case 'b':
                printBoolSet(intset);
                break;
            case 'h':
                puts(
                     "Usage: ./homework1\n\n"
                     "Commands:\n"
                     "i - insert value to set\n"
                     "r - remove value from set\n"
                     "p - print array\n"
                     "q - exit\n"
                     "b - print array of converted boolean values\n"
                     "h - print this help message\n"
                     );
                break;
            default:
                puts("Unknown command. Type 'h' for help.");
                break;
        }
        getchar();
    }
    exit_loop: ;
    return 0;
}
