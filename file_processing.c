
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_NAME 64
#define MAX_STUDENTS 100

typedef struct {
    char name[MAX_NAME];
    int age;
    float gpa;
} Student;

int parse_student(const char *line, Student *s)
{
    char temp[MAX_LINE];
    strncpy(temp, line, MAX_LINE - 1);
    temp[MAX_LINE - 1] = '\0';

    char *newline = strchr(temp, '\n');
    if (newline) *newline = '\0';
    
    char *cr = strchr(temp, '\r');
    if (cr) *cr = '\0';

    char *token = strtok(temp, ";");
    if (token == NULL) return -1;
    strncpy(s->name, token, MAX_NAME - 1);
    s->name[MAX_NAME - 1] = '\0';

    token = strtok(NULL, ";");
    if (token == NULL) return -1;
    s->age = atoi(token);

    token = strtok(NULL, ";");
    if (token == NULL) return -1;
    s->gpa = (float)atof(token);

    return 0;
}

int compare_by_gpa(const void *a, const void *b)
{
    const Student *sa = (const Student *)a;
    const Student *sb = (const Student *)b;
    if (sb->gpa > sa->gpa) return 1;
    if (sb->gpa < sa->gpa) return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    const char *input_file = (argc > 1) ? argv[1] : "students.txt";
    const char *output_file = (argc > 2) ? argv[2] : "report.txt";

    FILE *fin = fopen(input_file, "r");
    if (fin == NULL) {
        perror("fopen(input)");
        return EXIT_FAILURE;
    }

    Student students[MAX_STUDENTS];
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, MAX_LINE, fin) != NULL && count < MAX_STUDENTS) {
        if (strlen(line) > 1) {
            if (parse_student(line, &students[count]) == 0) {
                count++;
            }
        }
    }
    fclose(fin);

    if (count == 0) {
        fprintf(stderr, "Помилка: файл порожній або не містить валідних даних.\n");
        return EXIT_FAILURE;
    }

    printf("Прочитано %d студентів з файлу '%s'\n", count, input_file);

    float min_gpa = students[0].gpa;
    float max_gpa = students[0].gpa;
    float sum_gpa = 0.0f;

    for (int i = 0; i < count; i++) {
        if (students[i].gpa < min_gpa) min_gpa = students[i].gpa;
        if (students[i].gpa > max_gpa) max_gpa = students[i].gpa;
        sum_gpa += students[i].gpa;
    }
    float avg_gpa = sum_gpa / count;

    qsort(students, (size_t)count, sizeof(Student), compare_by_gpa);

    FILE *fout = fopen(output_file, "w");
    if (fout == NULL) {
        perror("fopen(output)");
        return EXIT_FAILURE;
    }

    fprintf(fout, "=== ЗВІТ ПО УСПІШНОСТІ СТУДЕНТІВ ===\n");
    fprintf(fout, "Загальна кількість студентів: %d\n\n", count);
    fprintf(fout, "%-25s | %-5s | %-5s\n", "ПІБ студента", "Вік", "GPA");
    fprintf(fout, "-----------------------------------------\n");

    for (int i = 0; i < count; i++) {
        fprintf(fout, "%-25s | %-5d | %-5.2f\n", students[i].name, students[i].age, students[i].gpa);
    }

    fprintf(fout, "-----------------------------------------\n");
    fprintf(fout, "Статистика:\n");
    fprintf(fout, "Мінімальний GPA: %.2f\n", min_gpa);
    fprintf(fout, "Максимальний GPA: %.2f\n", max_gpa);
    fprintf(fout, "Середній GPA:     %.2f\n", avg_gpa);

    fclose(fout);
    printf("Звіт успішно збережено у файл '%s'\n", output_file);

    return EXIT_SUCCESS;
}
