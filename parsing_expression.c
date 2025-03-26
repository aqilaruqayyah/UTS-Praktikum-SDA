#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Struct node link list
typedef struct Node {
    char data[MAX];
    struct Node *next;
} Node;

// Struct stack
typedef struct {
    Node *top;
} Stack;

// Fungsi untuk menginisialisasi stack
void initStack(Stack *s) {
