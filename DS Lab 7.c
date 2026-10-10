#include <stdio.h>
#include <stdlib.h>

/* Swap two integers */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Partition using the last element as pivot (Lomuto scheme) */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

/* Recursive quick sort */
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(void) {
    int n;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    int *original = malloc(n * sizeof(int));
    int *sorted   = malloc(n * sizeof(int));
    if (original == NULL || sorted == NULL) {
        printf("Memory allocation failed.\n");
        free(original);
        free(sorted);
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &original[i]) != 1) {
            printf("Invalid input at position %d.\n", i + 1);
            free(original);
            free(sorted);
            return 1;
        }
        sorted[i] = original[i];   /* copy to sort separately */
    }

    quickSort(sorted, 0, n - 1);

    /* Before / After comparison */
    printf("\n==============================\n");
    printf("  %-5s | %-10s | %-10s\n", "Index", "Before", "After");
    printf("==============================\n");
    for (int i = 0; i < n; i++) {
        printf("  %-5d | %-10d | %-10d\n", i, original[i], sorted[i]);
    }
    printf("==============================\n");

    printf("\nBefore: ");
    for (int i = 0; i < n; i++) printf("%d ", original[i]);
    printf("\nAfter : ");
    for (int i = 0; i < n; i++) printf("%d ", sorted[i]);
    printf("\n");

    free(original);
    free(sorted);
    return 0;
}
