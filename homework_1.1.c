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


void test(void) {
    puts("Creating with 1.");
    intSet *intset = defineIntSet(1);
    printIntSet(intset);
    
    puts("Inserting 2.");
    insert(2, intset);
    printIntSet(intset);
    
    puts("Inserting 3.");
    insert(3, intset);
    printIntSet(intset);
    
    puts("Inserting 4.");
    insert(4, intset);
    printIntSet(intset);
    
    puts("Trying to again insert 3.");
    printIntSet(intset);
    insert(3, intset);
    
    puts("Removing 2.");
    intset = removeValueFromIntSet(2, intset);
    printIntSet(intset);
    
    puts("Removing 4.");
    intset = removeValueFromIntSet(4, intset);
    printIntSet(intset);
    
    puts("Removing 1.");
    intset = removeValueFromIntSet(1, intset);
    printIntSet(intset);
    
    puts("Trying to remove 5.");
    intset = removeValueFromIntSet(5, intset);
    printIntSet(intset);
    
    puts("Releasing set.");
    releaseIntSet(intset);
}


int main(int argc, const char * argv[]) {
    test();
    
    return 0;
}
