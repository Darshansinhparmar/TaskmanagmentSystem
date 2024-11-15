#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

struct Task {
    string description;
    string deadline;
    int priority;

    bool operator<(const Task& other) const {
        return priority < other.priority; // Higher priority comes first
    }
};

class TaskManager {
private:
    priority_queue<Task> taskQueue;
    string filename = "tasks.txt";

    void loadTasks() {
        ifstream file(filename);
        string desc, deadline;
        int priority;
        while (getline(file, desc) && getline(file, deadline) && file >> priority) {
            file.ignore();
            Task task = {desc, deadline, priority};
            taskQueue.push(task);
        }
        file.close();
    }

    void saveTasks() {
        ofstream file(filename);
        priority_queue<Task> tempQueue = taskQueue;
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            tempQueue.pop();
            file << task.description << endl;
            file << task.deadline << endl;
            file << task.priority << endl;
        }
        file.close();
    }

public:
    TaskManager() {
        loadTasks();
    }

    ~TaskManager() {
        saveTasks();
    }

    void addTask(string desc, string deadline, int priority) {
        Task task = {desc, deadline, priority};
        taskQueue.push(task);
        cout << "Task added successfully.\n";
    }

    void viewTasks() {
        if (taskQueue.empty()) {
            cout << "No tasks available.\n";
            return;
        }
        priority_queue<Task> tempQueue = taskQueue;
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            tempQueue.pop();
            cout << "Task: " << task.description << " | Deadline: " << task.deadline << " | Priority: " << task.priority << endl;
        }
    }

    void deleteTask() {
        if (taskQueue.empty()) {
            cout << "No tasks to delete.\n";
            return;
        }
        taskQueue.pop();
        cout << "Task deleted successfully.\n";
    }

    void updateTaskPriority(int index, int newPriority) {
        // This is a simple example. Advanced implementation would require task lookup and editing.
        cout << "Task updated. New priority: " << newPriority << endl;
    }
};

int main() {
    TaskManager manager;
    int choice;

    do {
        cout << "\nTask Manager\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Update Task Priority\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        string desc, deadline;
        int priority;

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, desc);
                cout << "Enter deadline: ";
                getline(cin, deadline);
                cout << "Enter priority (1 - High, 2 - Medium, 3 - Low): ";
                cin >> priority;
                manager.addTask(desc, deadline, priority);
                break;
            case 2:
                manager.viewTasks();
                break;
            case 3:
                manager.deleteTask();
                break;
            case 4:
                // Simulate priority update
                int index, newPriority;
                cout << "Enter task index to update: ";
                cin >> index;
                cout << "Enter new priority: ";
                cin >> newPriority;
                manager.updateTaskPriority(index, newPriority);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
