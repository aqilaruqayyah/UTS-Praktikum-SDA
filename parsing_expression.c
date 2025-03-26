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
        s->top = NULL;
}

// Fungsi untuk memeriksa apakah stack kosong
int isEmpty(Stack *s) {
    return s->top == NULL;
}

// Fungsi untuk memasukkan elemen ke stack
void push(Stack *s, char *c) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(newNode->data, c);
    newNode->next = s->top;
    s->top = newNode;
}

// Fungsi untuk mengeluarkan elemen dari stack
char *pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return NULL;
    }
    Node *temp = s->top;
    char *data = (char *)malloc(MAX * sizeof(char));
    strcpy(data, temp->data);
    s->top = temp->next;
    free(temp);
    return data;
}

// Fungsi untuk mendapatkan elemen teratas dari stack
char *peek(Stack *s) {
    if (isEmpty(s)) {
        return NULL;
    }
    return s->top->data;
