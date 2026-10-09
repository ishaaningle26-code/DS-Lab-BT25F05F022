#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

/* ---------- Merge Sort: O(n log n) time, O(n) space ---------- */
static void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    if (!L || !R) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(L, &arr[left], n1 * sizeof(int));
    memcpy(R, &arr[mid + 1], n2 * sizeof(int));

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];   /* <= keeps the sort stable */
        else              arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/* ---------- Input helpers ---------- */

/* Prompts until a valid integer in [min, max] is entered.
   Returns 1 on success, 0 on end of input (EOF). */
int read_int(const char *prompt, int min, int max, int *out) {
    char line[64];
    while (1) {
        printf("%s", prompt);
        fflush(stdout);
        if (!fgets(line, sizeof(line), stdin)) return 0;

        char *end;
        long v = strtol(line, &end, 10);
        while (*end == ' ' || *end == '\t') end++;

        if (end == line || (*end != '\n' && *end != '\0')) {
            printf("  Please enter a whole number.\n");
        } else if (v < min || v > max) {
            printf("  Please enter a value between %d and %d.\n", min, max);
        } else {
            *out = (int)v;
            return 1;
        }
    }
}

/* Reads a y/n answer. Returns 1 for yes, 0 for no or EOF. */
int ask_yes_no(const char *prompt) {
    char line[16];
    printf("%s", prompt);
    fflush(stdout);
    if (!fgets(line, sizeof(line), stdin)) return 0;
    return line[0] == 'y' || line[0] == 'Y';
}

void print_array(const char *label, const int arr[], int n) {
    printf("%s", label);
    if (n == 0) printf("(empty)");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

/* ---------- Menu actions ---------- */

int enter_array(int arr[]) {
    int n;
    if (!read_int("How many numbers? ", 1, MAX_SIZE, &n)) return -1;
    for (int i = 0; i < n; i++) {
        char prompt[40];
        snprintf(prompt, sizeof(prompt), "  Element %d: ", i + 1);
        if (!read_int(prompt, -2000000000, 2000000000, &arr[i])) return -1;
    }
    return n;
}

void amend_element(int arr[], int n) {
    if (n == 0) { printf("The array is empty.\n"); return; }
    int pos, val;
    print_array("Current array: ", arr, n);
    if (!read_int("Position to change (1-based): ", 1, n, &pos)) return;
    if (!read_int("New value: ", -2000000000, 2000000000, &val)) return;
    printf("Changed element %d from %d to %d.\n", pos, arr[pos - 1], val);
    arr[pos - 1] = val;
}

int add_element(int arr[], int n) {
    if (n >= MAX_SIZE) { printf("Array is full (max %d).\n", MAX_SIZE); return n; }
    int val;
    if (!read_int("Value to add: ", -2000000000, 2000000000, &val)) return n;
    arr[n] = val;
    printf("Added %d at position %d.\n", val, n + 1);
    return n + 1;
}

int delete_element(int arr[], int n) {
    if (n == 0) { printf("The array is empty.\n"); return n; }
    int pos;
    print_array("Current array: ", arr, n);
    if (!read_int("Position to delete (1-based): ", 1, n, &pos)) return n;
    printf("Deleted %d.\n", arr[pos - 1]);
    for (int i = pos - 1; i < n - 1; i++) arr[i] = arr[i + 1];
    return n - 1;
}

void sort_and_show(int arr[], int n) {
    if (n == 0) { printf("The array is empty. Enter some numbers first.\n"); return; }

    int sorted[MAX_SIZE];
    memcpy(sorted, arr, n * sizeof(int));

    merge_sort(sorted, 0, n - 1);
    print_array("Sorted with merge sort: ", sorted, n);

    if (ask_yes_no("Keep the sorted order as your current array? (y/n): "))
        memcpy(arr, sorted, n * sizeof(int));
}

int main(void) {
    int arr[MAX_SIZE];
    int n;
    int choice;

    printf("=== Merge Sort Program ===\n");

    n = enter_array(arr);
    if (n < 0) return 0;

    while (1) {
        printf("\n--- Menu ---\n");
        print_array("Current array: ", arr, n);
        printf("1. Enter a new array\n");
        printf("2. Change an element\n");
        printf("3. Add an element\n");
        printf("4. Delete an element\n");
        printf("5. Sort with merge sort and display\n");
        printf("6. Exit\n");

        if (!read_int("Your choice: ", 1, 6, &choice)) break;

        switch (choice) {
            case 1: {
                int m = enter_array(arr);
                if (m < 0) return 0;
                n = m;
                break;
            }
            case 2: amend_element(arr, n);      break;
            case 3: n = add_element(arr, n);    break;
            case 4: n = delete_element(arr, n); break;
            case 5: sort_and_show(arr, n);      break;
            case 6: printf("Goodbye!\n");       return 0;
        }
    }
    return 0;
}