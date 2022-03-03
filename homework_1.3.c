//
//  homework_1.c
//  flita
//
//  Created by Тихон on 03.03.2022.
//

#include <stdlib.h>
#include <stdio.h>

int convertDecrimalToBinary(int value, int *output) {
    int a[10], i;
    
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

const int binaryArrayLenth = 10;

typedef struct BinarySet {
    int value[binaryArrayLenth];  // may cause big numbers bug
    int lenth;
    struct BinarySet *next;
} BinarySet;


BinarySet *defineBinarySet (int value) {
    BinarySet *start = malloc(sizeof(BinarySet));
    start->lenth = convertDecrimalToBinary(value, start->value);
    return start;
}

int _isContains(int *value, BinarySet *i, int lenth) {
    while (i!=NULL) {
        int isDifferent = 0;
        
        if (lenth == i->lenth) {
            for (int j = 0; j < i->lenth; j++) {
                if (i->value[j] != value[j]) {
                    isDifferent = 1;
                }
            }
        }
        
        if (!isDifferent) {
            return 1;
        }
        
        i = i->next;
    }
    
    return 0;
}

void insert(int value, BinarySet *i) {
    int bufferArray[10];
    int lenth = convertDecrimalToBinary(value, bufferArray);
    
    if (_isContains(bufferArray, i, lenth)) {
        fprintf(stderr, "Set already contains this value: `");
        printBinaryArray(bufferArray, lenth);
        fprintf(stderr, "`\n");
        return;
    }
    
    while (i->next!=NULL) { i = i->next; }
    
    BinarySet *next = malloc(sizeof(BinarySet));
    next->lenth = convertDecrimalToBinary(value, next->value);
    i->next = next;
}

BinarySet *removeValueFromBinarySet(int value, BinarySet *i) {
    int bufferArray[10];
    int lenth = convertDecrimalToBinary(value, bufferArray);
    
    if (_isContains(bufferArray, i, lenth)) {
        fprintf(stderr, "Set already contains this value: `");
        printBinaryArray(bufferArray, lenth);
        fprintf(stderr, "`\n");
        return i;
    }
    
    BinarySet *outIntSet = i;
    BinarySet *previous = NULL;
    
    while (i!=NULL) {
        int isDifferent = 0;
        
        if (lenth == i->lenth) {
            for (int j = 0; j < i->lenth; j++) {
                if (i->value[j] != bufferArray[j]) {
                    isDifferent = 1;
                }
            }
        }
        
        if (!isDifferent) {
            break;
        }
        
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

void releaseBinarySet(BinarySet *i) {
    BinarySet *next = NULL;
    for (; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}


void printBinarySet(BinarySet *i) {
    printf("<");
    while (i!=NULL) {
        printBinaryArray(i->value, i->lenth);
        if (i->next != NULL) {
            printf(", ");
        }
        i = i->next;
    }
    printf(">\n");
}


void test(void) {
    puts("Creating with 1.");
    BinarySet *intset = defineBinarySet(1);
    printBinarySet(intset);
    
    puts("Inserting 2.");
    insert(2, intset);
    printBinarySet(intset);
    
    puts("Inserting 3.");
    insert(3, intset);
    printBinarySet(intset);
    
    puts("Inserting 4.");
    insert(4, intset);
    printBinarySet(intset);
    
    puts("Trying to again insert 3.");
    insert(3, intset);
    printBinarySet(intset);
    
    puts("Removing 2.");
    intset = removeValueFromBinarySet(2, intset);
    printBinarySet(intset);
    
    puts("Removing 4.");
    intset = removeValueFromBinarySet(4, intset);
    printBinarySet(intset);
    
    puts("Removing 1.");
    intset = removeValueFromBinarySet(1, intset);
    printBinarySet(intset);
    
    puts("Trying to remove 5.");
    intset = removeValueFromBinarySet(5, intset);
    printBinarySet(intset);
    
    puts("Releasing set.");
    releaseBinarySet(intset);
}


int main(int argc, const char * argv[]) {
    test();
    
    return 0;
}
