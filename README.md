# To-Do-list
To-Do application written in C.

# Overview
A simple command-line To-Do List application written in C. This program allows users to add tasks, view tasks, mark tasks as completed, and delete tasks. It stores the tasks in a text file so that they persist between application runs.

# Usage
1. After compiling the program, run it using: ./todo
2. The program will prompt you with a menu:
   - Add Task
   - View Tasks
   - Mark Task as Completed
   - Delete Task
   - Exit
3. Select an option by entering the corresponding number.
4. The program will continue running until you select the "Exit" option.

# Functions
- add_task(): Adds a new task to the list.
- view_tasks(): Displays all tasks.
- mark_task_completed(): Marks a task as completed by its ID.
- delete_task(): Deletes a task by its ID.
- load_tasks(): Loads tasks from the tasks.txt file when the program starts.
- save_tasks(): Saves the current list of tasks to the tasks.txt file.

# File format
The tasks are stored in tasks.txt. Each task is stored in the following format:
- ID
- Task Name
- Completed (0 for incomplete, 1 for completed)

# Notes
- If there are too many tasks (more than 100), the program will inform the user that the task list is full.
- Task IDs are automatically assigned sequentially.
- The terminal will be cleared each time you perform an action to keep the screen clean.
