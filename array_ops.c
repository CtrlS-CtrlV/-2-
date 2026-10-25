
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *arr, size_t n)
{
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - 1 - i; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                swap(arr + j, arr + j + 1);
            }
        }
    }
}

int *linear_search(int *arr, size_t n, int target)
{
    for (size_t i = 0; i < n; i++) {
        if (*(arr + i) == target) {
            return arr + (ptrdiff_t)i;
        }
    }
    return NULL;
}

void print_array(const int *arr, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

int main(void)
{
    size_t n;
    printf("Введіть розмір масиву: ");
    if (scanf("%zu", &n) != 1 || n == 0) {
        fprintf(stderr, "Помилка: невірний розмір\n");
        return EXIT_FAILURE;
    }

    int *data = malloc(n * sizeof(int));
    if (data == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));
    for (size_t i = 0; i < n; i++) {
        *(data + i) = rand() % 100;
    }

    printf("До сортування: ");
    print_array(data, n);

    bubble_sort(data, n);

    printf("Після сортування: ");
    print_array(data, n);

    int target;
    printf("Введіть число для пошуку: ");
    if (scanf("%d", &target) == 1) {
        int *result = linear_search(data, n, target);
        if (result != NULL) {
            ptrdiff_t index = result - data;
            printf("Елемент %d знайдено! Індекс: %td, Адреса: %p\n", target, index, (void *)result);
        } else {
            printf("Елемент %d не знайдено у масиві.\n", target);
        }
    }

    free(data);
    return EXIT_SUCCESS;
}
