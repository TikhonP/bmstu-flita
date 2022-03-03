//
//  homework_1.h
//  flita
//
//  Created by Тихон on 03.03.2022.
//

#ifndef homework_1_h
#define homework_1_h

#include <stdio.h>

typedef struct intSet intSet;

// Returns set with first initial element
struct intSet *defineIntSet(int value);

void insert(int value, struct intSet *i);

struct intSet *removeValueFromIntSet(int value, struct intSet *i);

void releaseIntSet(struct intSet *i);

void printIntSet(struct intSet *i);

#endif /* homework_1_h */
