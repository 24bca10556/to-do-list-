#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Task {
    char title[MAX];
    int done;
    struct Task* next;
} Task;

Task *head = NULL;

Task* newTask(const char* t) {
    Task* task = malloc(sizeof(Task));
    strncpy(task->title, t, MAX);
    task->done = 0;
    task->next = NULL;
    return task;
}

void addTask(const char* t) {
    Task *task = newTask(t), *cur = head;
    if (!head) head = task;
    else {
        while (cur->next) cur = cur->next;
        cur->next = task;
    }
    printf("Task added.\n");
}

void showTasks() {
    Task* cur = head;
    int i = 1;
    if (!cur) { printf("No tasks.\n"); return; }
    while (cur) {
        printf("%d. [%c] %s\n", i++, cur->done ? 'X' : ' ', cur->title);
        cur = cur->next;
    }
}

void completeTask(int n) {
    Task* cur = head;
    for (int i = 1; cur && i < n; i++) cur = cur->next;
    if (cur) { cur->done = 1; printf("Marked done.\n"); }
    else printf("Not found.\n");
}

void deleteTask(int n) {
    if (!head) { printf("Nothing to delete.\n"); return; }
    Task *cur = head, *prev = NULL;
    for (int i = 1; cur && i < n; i++) { prev = cur; cur = cur->next; }
    if (!cur) { printf("Not found.\n"); return; }
    if (!prev) head = cur->next;
    else prev->next = cur->next;
    free(cur);
    printf("Deleted.\n");
}

void clearList() {
    Task* tmp;
    while (head) { tmp = head; head = head->next; free(tmp); }
}

int main() {
    int ch, n;
    char t[MAX];
    do {
        printf("\n1.Add 2.Show 3.Done 4.Delete 5.Exit\n> ");
        scanf("%d", &ch); getchar();
        switch (ch) {
            case 1: printf("Title: "); fgets(t, MAX, stdin); t[strcspn(t, "\n")] = 0; addTask(t); break;
            case 2: showTasks(); break;
            case 3: printf("Num: "); scanf("%d", &n); completeTask(n); break;
            case 4: printf("Num: "); scanf("%d", &n); deleteTask(n); break;
        }
    } while (ch != 5);
    clearList();
    return 0;
}
