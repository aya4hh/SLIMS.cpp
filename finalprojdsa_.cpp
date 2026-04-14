#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <windows.h>

using namespace std;

map<string, float> expenses;

struct Task {
    string task;
    string type;
    bool done;
};

vector<Task> tasks;
map<string, int> study_log;

// EXPENSES
void add_expense() {
    string category;
    float amount;
    cout << "Enter expense category (e.g., food, transport): ";
    cin >> category;
    cout << "Enter amount: ";
    cin >> amount;
    
    if (expenses.find(category) != expenses.end()) {
        expenses[category] += amount;
    } else {
        expenses[category] = amount;
    }
    
    cout << "\n\nAdded " << amount << " to " << category << ".\n\n";
}

void view_expenses() {
    cout << "\nMonthly Expenses Summary:\n";
    float total = 0;
    
    for (auto p : expenses) {
        cout << p.first << ": " << p.second << "\n";
        total += p.second;
    }
    
    cout << "Total Expenses: " << total << "\n\n";
}

void expense_menu() {
    while (true) {
        cout << "\n--- Expense Tracker ---\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Back to Main Menu\n";
        cout << "Choose an option: ";
        
        string choice;
        cin >> choice;
        
        if (choice == "1") {
            add_expense();
        } else if (choice == "2") {
            view_expenses();
        } else if (choice == "3") {
            break;
        }
    }
}

// TASKS
void add_task() {
    string task, type;
    cout << "Enter task description: ";
    cin >> task;
    cout << "Task type (study/chores): ";
    cin >> type;
    
    tasks.push_back({task, type, false});
    cout << "Task added.\n\n";
}

void mark_done() {
    if (tasks.empty()) {
        cout << "No tasks available.\n\n";
        return;
    }
    
    for (int i = 0; i < tasks.size(); i++) {
        string status = tasks[i].done ? "YES" : "NO";
        cout << (i + 1) << ". [" << status << "] " << tasks[i].task << " (" << tasks[i].type << ")\n";
    }
    
    cout << "Enter task number to mark as done: ";
    int choice;
    cin >> choice;
    
    if (choice > 0 && choice <= tasks.size()) {
        tasks[choice - 1].done = true;
        cout << "Task marked as done.\n\n";
    }
}

void task_menu() {
    while (true) {
        cout << "\n--- Task Manager ---\n";
        cout << "1. Add Task\n";
        cout << "2. Mark Task Done\n";
        cout << "3. View Tasks\n";
        cout << "4. Back to Main Menu\n";
        cout << "Choose an option: ";
        
        string choice;
        cin >> choice;
        
        if (choice == "1") {
            add_task();
        } else if (choice == "2") {
            mark_done();
        } else if (choice == "3") {
            cout << "\n";
            for (int i = 0; i < tasks.size(); i++) {
                string status = tasks[i].done ? "YES" : "NO";
                cout << "[" << status << "] " << tasks[i].task << " (" << tasks[i].type << ")\n";
            }
            cout << "\n";
        } else if (choice == "4") {
            break;
        }
    }
}

// TIMER
void exam_timer() {
    string subject;
    int study_minutes, break_minutes;
    
    cout << "Enter subject: ";
    cin >> subject;
    cout << "Enter study time (minutes): ";
    cin >> study_minutes;
    cout << "Enter break time (minutes): ";
    cin >> break_minutes;
    
    if (study_minutes <= 0 || break_minutes < 0) {
        cout << "Please enter valid positive numbers.\n\n";
        return;
    }
    
    // STUDY SESSION
    cout << "\nStudying " << subject << " for " << study_minutes << " minutes...\n";
    int seconds = study_minutes * 60;
    
    while (seconds > 0) {
        int mins = seconds / 60;
        int secs = seconds % 60;
        
        cout << "Study Time Left: ";
        if (mins < 10) cout << "0";
        cout << mins << ":";
        if (secs < 10) cout << "0";
        cout << secs << "\r";
        cout.flush();
        
        time_t start = time(0);
        while (time(0) - start < 1);
        
        seconds--;
    }
    

    for (int i = 0; i < 3; i++) {
        Beep(1000, 500); 
    }
    
    cout << "\nStudy session complete!\n\n";
    
    // TRACK SUBJECTS
    if (study_log.find(subject) != study_log.end()) {
        study_log[subject] += study_minutes;
    } else {
        study_log[subject] = study_minutes;
    }
    
    // BREAK
    if (break_minutes > 0) {
        cout << "Break time for " << break_minutes << " minutes...\n";
        seconds = break_minutes * 60;
        
        while (seconds > 0) {
            int mins = seconds / 60;
            int secs = seconds % 60;
            
            cout << "Break Time Left: ";
            if (mins < 10) cout << "0";
            cout << mins << ":";
            if (secs < 10) cout << "0";
            cout << secs << "\r";
            cout.flush();
            
            time_t start = time(0);
            while (time(0) - start < 1);
            
            seconds--;
        }
    }    
        for (int i = 0; i < 3; i++) {
            Beep(1000, 500); 
        
        cout << "\nBreak finished!\n\n";
    }
    
    // Summary
    cout << "\nStudy Time Summary:\n";
    for (auto p : study_log) {
        cout << p.first << ": " << p.second << " minutes\n";
    }
    cout << "\n";
}

void exam_timer_menu() {
    while (true) {
        cout << "\n--- Exam Review Timer ---\n";
        cout << "1. Start Timer\n";
        cout << "2. Back to Main Menu\n";
        cout << "Choose an option: ";
        
        string choice;
        cin >> choice;
        
        if (choice == "1") {
            exam_timer();
        } else if (choice == "2") {
            break;
        }
    }
}

// MAIN MENU
int main() {
    while (true) {
        cout << "\n=== Student Management System ===\n";
        cout << "1. Expense Tracker\n";
        cout << "2. Task Manager\n";
        cout << "3. Exam Review Timer\n";
        cout << "4. Exit\n";
        cout << "Choose a module: ";
        
        string choice;
        cin >> choice;
        
        if (choice == "1") {
            expense_menu();
        } else if (choice == "2") {
            task_menu();
        } else if (choice == "3") {
            exam_timer_menu();
        } else if (choice == "4") {
            cout << "Goodbye!\n";
            break;
        }
    }
    
    return 0;
}
