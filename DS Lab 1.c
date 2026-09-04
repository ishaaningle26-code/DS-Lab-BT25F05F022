#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack implementation
int stack[MAX];
int top = -1;

// Push an element
void push(int value) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }

    stack[++top] = value;
}

// Pop an element
int pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }

    return stack[top--];
}

// Check whether character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' ||
           ch == '*' || ch == '/' ||
           ch == '%';
}

// Perform operation
int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
        default:
            printf("Invalid operator\n");
            exit(1);
    }
}

// Evaluate prefix expression
int evaluatePrefix(char expression[]) {
    int length = strlen(expression);

    // Scan from right to left
    for (int i = length - 1; i >= 0; i--) {

        // Ignore spaces
        if (expression[i] == ' ')
            continue;

        // If operand, push onto stack
        if (isdigit(expression[i])) {
            push(expression[i] - '0');
        }

        // If operator
        else if (isOperator(expression[i])) {
            int a = pop();
            int b = pop();

            int result = calculate(a, b, expression[i]);

            push(result);
        }
    }

    return pop();
}

int main() {
    char expression[MAX];

    printf("Enter prefix expression: ");
    fgets(expression, MAX, stdin);

    int result = evaluatePrefix(expression);

    printf("Result = %d\n", result);

    return 0;
}
