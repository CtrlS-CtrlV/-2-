
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 64
#define MAX_STUDENTS 100

typedef struct {
    char name[MAX_NAME];
    int age;
    float gpa;
} Student;

int add_student(Student *students, int *count, const char *name, int age, float gpa)
{
    if (*count >= MAX_STUDENTS) {
        fprintf(stderr, "Масив студентів переповнений\n");
        return -1;
    }

    strncpy(students[*count].name, name, MAX_NAME - 1);
    students[*count].name[MAX_NAME - 1] = '\0';
    students[*count].age = age;
    students[*count].gpa = gpa;
    (*count)++;
    return 0;
}

Student *find_student(Student *students, int count, const char *name)
{
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            return &students[i];
        }
    }
    return NULL;
}

float calculate_average_gpa(const Student *students, int count)
{
    if (count <= 0) return 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < count; i++) {
        sum += students[i].gpa;
    }
    return sum / count;
}

void print_student(const Student *s)
{
    printf("  %-22s  Вік: %d  Середній бал: %.2f\n", s->name, s->age, s->gpa);
}

void print_all_students(const Student *students, int count)
{
    printf("\n=== Список студентів (%d) ===\n", count);
    for (int i = 0; i < count; i++) {
        printf("[%d]", i + 1);
        print_student(&students[i]);
    }
}

int compare_by_gpa(const void *a, const void *b)
{
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    if (sb->gpa > sa->gpa) return 1;
    if (sb->gpa < sa->gpa) return -1;
    return 0;
}

int main(void)
{
    Student students[MAX_STUDENTS];
    int count = 0;

    add_student(students, &count, "Шевченко Тарас", 20, 4.5f);
    add_student(students, &count, "Франко Іван", 21, 4.8f);
    add_student(students, &count, "Леся Українка", 19, 4.9f);
    add_student(students, &count, "Коцюбинський Михайло", 22, 4.2f);
    add_student(students, &count, "Стефаник Василь", 20, 4.6f);
    add_student(students, &count, "Сковорода Григорій", 23, 4.3f);
    add_student(students, &count, "Котляревський Іван", 21, 4.7f);
    add_student(students, &count, "Довженко Олександр", 24, 4.4f);

    print_all_students(students, count);

    qsort(students, (size_t)count, sizeof(Student), compare_by_gpa);
    printf("\n=== Після сортування за GPA (спадання) ===\n");
    print_all_students(students, count);

    printf("\nЗагальний середній бал студентів: %.2f\n", calculate_average_gpa(students, count));

    char search_name[MAX_NAME];
    printf("\nВведіть повне ім'я студента для пошуку (напр., Франко Іван): ");
    if (fgets(search_name, sizeof(search_name), stdin) != NULL) {
        char *nl = strchr(search_name, '\n');
        if (nl) *nl = '\0';

        Student *found = find_student(students, count, search_name);
        if (found != NULL) {
            printf("Студента знайдено:\n");
            print_student(found);
        } else {
            printf("Студента з ім'ям '%s' не знайдено.\n", search_name);
        }
    }

    return 0;
}
