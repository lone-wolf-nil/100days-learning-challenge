#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int size, i;

    // Ask the user for the number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &size);

    // Allocate memory for 'size' integers
    array = (int *)malloc(size * sizeof(int));

    // Check if the memory allocation was successful
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit the program if malloc fails
    }

    // Assign values to the allocated memory
    for (i = 0; i < size; i++) {
        array[i] = i * 2; // Example values: 0, 2, 4, 6, ...
    }

    // Print the values
    printf("The array elements are: ");
    for (i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(array);

    return 0;
}
