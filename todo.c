#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_NAME_LENGTH 300
#define TASK_FILE "tasks.txt"

//Task structure
typedef struct {
    int id;
    char task_name[MAX_NAME_LENGTH];
    int completed;  //0 for incomplete, 1 for completed
} Task;

//Global task list and task counter
Task tasks[MAX_TASKS];
int task_count = 0;

void add_task ();
void view_tasks ();
void mark_task_completed ();
void delete_task ();
void display_menu ();
void load_tasks ();
void save_tasks ();

void clear_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main ()
{
    int choice;
    printf("\nTO-DO APPLICATION\n");

    // Load tasks from file at the start
    load_tasks();

    while (1)
    {
        display_menu();
        if (scanf("%d", &choice) != 1)
        {
            //If scanf fails, clear the input buffer and prompt again
            printf("\nInvalid choice. Please enter a number.\n");
            while (getchar() != '\n');  //Clear the input buffer
            continue;   //Skip the rest of the loop and ask for input again
        }

        switch (choice)
        {
            case 1:
                clear_terminal();
                add_task();
                break;
            case 2:
                clear_terminal();
                view_tasks();
                break;
            case 3:
                mark_task_completed();
                break;
            case 4:
                delete_task();
                break;
            case 5:
                printf("\nExiting the application. Goodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}

void add_task ()
{
    if (task_count >= MAX_TASKS)
    {
        printf("Task list is full.\n");
        return;
    }
    
    Task new_task;
    new_task.id = task_count + 1;   //Simple ID assignment
    new_task.completed = 0;     //Initially, task is not completed
    
    printf("Enter task name: ");
    getchar();      //Consume newline left by previous input
    fgets(new_task.task_name, MAX_NAME_LENGTH, stdin);
    new_task.task_name[strcspn(new_task.task_name, "\n")] = 0;  //Remove newline character
    
    tasks[task_count++] = new_task;
    save_tasks();   // Save the updated task list to the file
    printf("Task added successfully!\n");
}

void view_tasks ()
{
    if (task_count == 0)
    {
        printf("No tasks available.\n");
        return;
    }

    printf("Task List:\n");
    for (int i = 0; i < task_count; i++)
    {
        printf("ID: %d - %s [%s]\n", tasks[i].id, tasks[i].task_name, tasks[i].completed ? "COMPLETED" : "Incomplete");
    }
}

void mark_task_completed ()
{
    int task_id;
    printf("Enter task ID to mark as completed: ");
    scanf("%d", &task_id);

    if (task_id <= 0 || task_id > task_count)
    {
        printf("Invalid task ID.\n");
        return;
    }

    tasks[task_id - 1].completed = 1;       //Set task as completed
    save_tasks();   // Save the updated task list to the file
    printf("Task with ID %d marked as completed!\n", task_id);
}

void delete_task ()
{
    int task_id;
    printf("Enter task ID to delete: ");
    scanf("%d", &task_id);

    if (task_id <= 0 || task_id > task_count) {
        printf("Invalid task ID.\n");
        return;
    }

    for (int i = task_id - 1; i < task_count - 1; i++) {
        tasks[i] = tasks[i + 1];  // Shift tasks left
        tasks[i].id--;
    }

    task_count--;  // Reduce the number of tasks
    save_tasks();   // Save the updated task list to the file
    printf("Task with ID %d deleted successfully!\n", task_id);
}

void display_menu ()
{
    printf("\n1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Mark Task as Completed\n");
    printf("4. Delete Task\n");
    printf("5. Exit\n\n");
    printf("Choose an option: ");
}

// Function to load tasks from the file
void load_tasks() {
    FILE *file = fopen(TASK_FILE, "r");
    if (file == NULL) {
        printf("No previous tasks found. Starting a new list.\n");
        return;
    }

    while (fscanf(file, "%d\n%[^\n]\n%d\n", &tasks[task_count].id, tasks[task_count].task_name, &tasks[task_count].completed) != EOF) {
        task_count++;
    }

    fclose(file);
}

// Function to save tasks to the file
void save_tasks() {
    FILE *file = fopen(TASK_FILE, "w");
    if (file == NULL) {
        printf("Error saving tasks to file!\n");
        return;
    }

    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%d\n%s\n%d\n", tasks[i].id, tasks[i].task_name, tasks[i].completed);
    }

    fclose(file);
}
