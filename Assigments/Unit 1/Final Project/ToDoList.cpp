#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;


struct TodoItem {
    string task;
    int priority;
}; 


string getCurrentDateTime() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return string(buffer);
}


void customSort(vector<TodoItem>& todoList) {
    int n = todoList.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (todoList[j].priority > todoList[j + 1].priority) {
                TodoItem temp = todoList[j];
                todoList[j] = todoList[j + 1];
                todoList[j + 1] = temp;
            }
        }
    }
}


void customSortAlphabetical(vector<TodoItem>& todoList) {
    int n = todoList.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (todoList[j].task > todoList[j + 1].task) {
                TodoItem temp = todoList[j];
                todoList[j] = todoList[j + 1];
                todoList[j + 1] = temp;
            }
        }
    }
}


void customSortReverseAlphabetical(vector<TodoItem>& todoList) {
    int n = todoList.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (todoList[j].task < todoList[j + 1].task) {
                TodoItem temp = todoList[j];
                todoList[j] = todoList[j + 1];
                todoList[j + 1] = temp;
            }
        }
    }
}


void displayTodoList(const vector<TodoItem>& todoList) {
    if (todoList.empty()) {
        cout << "\nYour TODO list is empty.\n";
        return;
    }
    
    cout << "\n========== YOUR TODO LIST ==========\n";
    for (int i = 0; i < todoList.size(); i++) {
        cout << i + 1 << ". [Priority " << todoList[i].priority << "] " 
             << todoList[i].task << "\n";
    }
    cout << "===================================\n";
}


void addTodoItem(vector<TodoItem>& todoList) {
    string task;
    int priority;
    bool validPriority = false;
    
    cout << "\nEnter task description: ";
    cin.ignore();
    getline(cin, task);
    
    while (!validPriority) {
        cout << "Enter priority (1-5): ";
        cin >> priority;
        
        if (priority < 1 || priority > 5) {
            cout << "Invalid priority. Please enter a number between 1 and 5.\n";
            continue;
        }
        
        // Check if priority already exists
        for (const auto& item : todoList) {
            if (item.priority == priority) {
                cout << "Priority " << priority << " already exists. Choose another.\n";
                break;
            }
            validPriority = true;
        }
        
        if (todoList.empty()) {
            validPriority = true;
        }
    }
    
    todoList.push_back({task, priority});
    cout << "Task added successfully!\n";
}


void removeTodoItem(vector<TodoItem>& todoList) {
    if (todoList.empty()) {
        cout << "\nTODO list is empty. Nothing to remove.\n";
        return;
    }
    
    displayTodoList(todoList);
    int index;
    cout << "Enter task number to remove: ";
    cin >> index;
    
    if (index < 1 || index > todoList.size()) {
        cout << "Invalid task number.\n";
        return;
    }
    
    todoList.erase(todoList.begin() + index - 1);
    cout << "Task removed successfully!\n";
}


void saveTodoListToFile(const vector<TodoItem>& todoList) {
    ofstream outFile("todolist.txt");
    
    if (!outFile.is_open()) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }
    
    outFile << "TODO LIST - Generated: " << getCurrentDateTime() << "\n";
    outFile << "=====================================\n\n";
    
    if (todoList.empty()) {
        outFile << "Your TODO list is empty.\n";
    } else {
        for (int i = 0; i < todoList.size(); i++) {
            outFile << i + 1 << ". [Priority " << todoList[i].priority << "] " 
                    << todoList[i].task << "\n";
        }
    }
    
    outFile.close();
    cout << "TODO list saved to todolist.txt\n";
}


void loadTodoListFromFile(vector<TodoItem>& todoList) {
    ifstream inFile("todolist.txt");
    
    if (!inFile.is_open()) {
        cout << "No saved TODO list found. Starting with empty list.\n";
        return;
    }
    
    string line;
    getline(inFile, line);
    getline(inFile, line); 
    
    todoList.clear();
    
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        
        // Parse: "1. [Priority 3] Buy milk"
        size_t priorityStart = line.find("[Priority ") + 10;
        size_t priorityEnd = line.find("]", priorityStart);
        size_t taskStart = line.find("] ") + 2;
        
        int priority = stoi(line.substr(priorityStart, priorityEnd - priorityStart));
        string task = line.substr(taskStart);
        
        todoList.push_back({task, priority});
    }
    
    inFile.close();
    cout << "TODO list loaded from todolist.txt\n";
}


void displayMenu() {
    cout << "\n========== TODO LIST MENU ==========\n";
    cout << "1. Add a task\n";
    cout << "2. Read/View list\n";
    cout << "3. Remove a task\n";
    cout << "4. Sort alphabetically (A-Z)\n";
    cout << "5. Sort reverse alphabetically (Z-A)\n";
    cout << "6. Sort by priority\n";
    cout << "7. Reset list\n";
    cout << "8. Exit\n";
    cout << "===================================\n";
}


int main() {
    vector<TodoItem> todoList;
    int numInitialTasks;
    int choice;
    bool running = true;
    
    cout << "Welcome to TODO List Manager!\n";
    
    loadTodoListFromFile(todoList);
    
    if (todoList.empty()) {
        cout << "How many initial tasks would you like to add? ";
        cin >> numInitialTasks;
        
        for (int i = 0; i < numInitialTasks; i++) {
            cout << "\nTask " << i + 1 << ":\n";
            addTodoItem(todoList);
        }
    } else {
        cout << "Loaded " << todoList.size() << " tasks from file.\n";
        displayTodoList(todoList);
    }
    
    while (running) {
        displayMenu();
        cout << "Enter your choice (1-8): ";
        cin >> choice;
        
        if (choice == 1) {
            addTodoItem(todoList);
        }
        else if (choice == 2) {
            displayTodoList(todoList);
        }
        else if (choice == 3) {
            removeTodoItem(todoList);
        }
        else if (choice == 4) {
            customSortAlphabetical(todoList);
            cout << "List sorted alphabetically (A-Z).\n";
            displayTodoList(todoList);
        }
        else if (choice == 5) {
            customSortReverseAlphabetical(todoList);
            cout << "List sorted alphabetically (Z-A).\n";
            displayTodoList(todoList);
        }
        else if (choice == 6) {
            customSort(todoList);
            cout << "List sorted by priority.\n";
            displayTodoList(todoList);
        }
        else if (choice == 7) {
            todoList.clear();
            cout << "\nList reset. Starting over...\n";
            cout << "How many initial tasks would you like to add? ";
            cin >> numInitialTasks;
            for (int i = 0; i < numInitialTasks; i++) {
                cout << "\nTask " << i + 1 << ":\n";
                addTodoItem(todoList);
            }
        }
        else if (choice == 8) {
            cout << "\nSaving TODO list...\n";
            saveTodoListToFile(todoList);
            cout << "Goodbye!\n";
            running = false;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}