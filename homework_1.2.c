//
//  homework_1.c
//  flita
//
//  Created by Тихон on 03.03.2022.
//

#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, const char * argv[]) {
    int binary[10];
    
    puts("Converting 122 to binary.");
    int lenth = convertDecrimalToBinary(122, binary);
    printBinaryArray(binary, lenth);
    
    return 0;
}
