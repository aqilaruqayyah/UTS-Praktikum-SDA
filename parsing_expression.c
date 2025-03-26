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
}

// Fungsi untuk memeriksa apakah suatu karakter adalah operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Fungsi untuk mendapatkan prioritas suatu operator
int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

// Fungsi untuk konversi dari Infix ke Postfix
void infixToPostfix(char infix[], char postfix[]) {
    Stack s;
    initStack(&s);
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

        if (isalnum(c)) { // Periksa apakah karakter adalah huruf atau angka
            postfix[j++] = c;
        } else if (c == '(') {
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (c == ')') {
            while (!isEmpty(&s) && strcmp(peek(&s), "(") != 0) {
                postfix[j++] = pop(&s)[0];
            }
            pop(&s); // Menghapus '(' dari stack
        } else if (isOperator(c)) {
            while (!isEmpty(&s) && precedence(peek(&s)[0]) >= precedence(c)) {
                postfix[j++] = pop(&s)[0];
            }
            char temp[2] = {c, '\0'};
            push(&s, temp);
        }
        i++;
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s)[0];
    }

    postfix[j] = '\0';
}

// Fungsi untuk konversi dari Postfix ke Infix
void postfixToInfix(char postfix[], char infix[]) {
    Stack s;
    initStack(&s);
    int i = 0;

    while (postfix[i] != '\0') {
        char c = postfix[i];

        if (isalnum(c)) { // Periksa apakah karakter adalah huruf atau angka
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (isOperator(c)) {
            char *op1 = pop(&s);
            char *op2 = pop(&s);
            char temp[MAX];
            sprintf(temp, "(%s%c%s)", op2, c, op1);
            push(&s, temp);
        }
        i++;
    }

    strcpy(infix, pop(&s));
}

// Fungsi untuk konversi dari Infix ke Prefix
void infixToPrefix(char infix[], char prefix[]) {
    Stack s;
    initStack(&s);
    int i = 0, j = 0;
    char reversedInfix[MAX], reversedPrefix[MAX];

    // Membalikkan ekspresi Infix
    strcpy(reversedInfix, strrev(infix));

    // Mengganti '(' dengan ')' dan sebaliknya
    for (i = 0; reversedInfix[i] != '\0'; i++) {
        if (reversedInfix[i] == '(') {
            reversedInfix[i] = ')';
        } else if (reversedInfix[i] == ')') {
            reversedInfix[i] = '(';
        }
    }

    // Ubah Infix terbalik menjadi Postfix
    infixToPostfix(reversedInfix, reversedPrefix);

    // Membalikkan ekspresi Postfix untuk mendapat Prefix
    strcpy(prefix, strrev(reversedPrefix));
}

// Fungsi untuk konversi dari Prefix ke Infix
void prefixToInfix(char prefix[], char infix[]) {
    Stack s;
    initStack(&s);
    int i = strlen(prefix) - 1;

    while (i >= 0) {
        char c = prefix[i];

        if (isalnum(c)) { // Periksa apakah karakter adalah huruf atau angka
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (isOperator(c)) {
            char *op1 = pop(&s);
            char *op2 = pop(&s);
            char temp[MAX];
            sprintf(temp, "(%s%c%s)", op1, c, op2);
            push(&s, temp);
        }
        i--;
    }

    strcpy(infix, pop(&s));
}

// Fungsi untuk konversi dari Prefix ke Postfix
void prefixToPostfix(char prefix[], char postfix[]) {
    Stack s;
    initStack(&s);
    int i = strlen(prefix) - 1;

    while (i >= 0) {
        char c = prefix[i];

        if (isalnum(c)) { // Periksa apakah karakter adalah huruf atau angka
            char temp[2] = {c, '\0'};
            push(&s, temp);
        } else if (isOperator(c)) {
            char *op1 = pop(&s);
            char *op2 = pop(&s);
            char temp[MAX];
            sprintf(temp, "%s%s%c", op1, op2, c);
            push(&s, temp);
        }
        i--;
    }

    strcpy(postfix, pop(&s));
}

// Fungsi untuk konversi dari Postfix ke Prefix
void postfixToPrefix(char postfix[], char prefix[]) {
    Stack s;
    initStack(&s);
    int i = 0;

    while (postfix[i] != '\0') {
        char c = postfix[i];
