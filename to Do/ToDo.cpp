#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
struct Task {
    std::string name;
    bool isCompleted;
    std::chrono::system_clock::time_point deadline;
};
Task create(std::vector<Task>& Tasks) {
    std::string name;
    std::cout << "Enter task name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    Task newTask;
    newTask.name = name;
    newTask.isCompleted = false;
    std::string deadlineStr;
    std::cout << "Enter task deadline (YYYY-MM-DD HH:MM:SS): ";
    std::getline(std::cin, deadlineStr);
    std::tm deadlineTm = {};
    std::stringstream ss(deadlineStr);
    ss >> deadlineTm.tm_year;
    ss.ignore();
    ss >> deadlineTm.tm_mon;
    ss.ignore();
    ss >> deadlineTm.tm_mday;
    ss.ignore();
    ss >> deadlineTm.tm_hour;
    ss.ignore();
    ss >> deadlineTm.tm_min;
    ss.ignore();
    ss >> deadlineTm.tm_sec;
    if (ss.fail()) {
        std::cout << "Failed to parse deadline string!" << std::endl;
    }
    else {
        deadlineTm.tm_year -= 1900;
        deadlineTm.tm_mon -= 1;
        auto tp = std::chrono::system_clock::from_time_t(std::mktime(&deadlineTm));
        newTask.deadline = tp;
        Tasks.push_back(newTask);
        std::cout << "Task created successfully!\n";
    }
    return newTask;
}
void del(std::vector<Task>& Tasks, int index) {
    if (index >= 0 && index < Tasks.size()) {
        Tasks.erase(index + Tasks.begin());
        std::cout << "Task is deleted " << std::endl;
    }
    else {
        std::cout << "error" << std::endl;
    }
}
void modify(std::vector<Task>& Tasks, int index) {
    if (index >= 0 && index < Tasks.size()) {
        std::string newName;
        std::cout << "Enter new task name: ";
        std::cin.ignore();
        std::getline(std::cin, newName);
        Tasks[index].name = newName;
        std::cout << "Task is modified " << std::endl;
    }
    else {
        std::cout << "error" << std::endl;
    }
}
void Completed(std::vector<Task>& Tasks, int index) {
    if (index >= 0 && index < Tasks.size()) {
        Tasks[index].isCompleted = true;
        std::cout << "Task is completed!" << std::endl;
    }
    else {
        std::cout << "error" << std::endl;
    }
}
void display(const std::vector<Task>& Tasks) {
    int compCount = 0;
    int notcompCount = 0;
    for (int i = 0; i < Tasks.size(); i++) {
        const Task& task = Tasks[i];
        std::time_t deadlineTime = std::chrono::system_clock::to_time_t(task.deadline);
        std::cout << i << ": " << task.name;
        if (task.isCompleted) {
            std::cout << "[Completed]";
            compCount++;
        }
        else {
            auto currentTime = std::chrono::system_clock::now();
            std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
            if (task.deadline - currentTime <= std::chrono::hours(1)) {
                std::cout << "Approaching Deadline";
            }
            else if (std::difftime(deadlineTime, currentTimeT) <= 86400) {
                std::cout << "One Day Remaining";
            }
            else {
                std::cout << "[Not Completed]";
                notcompCount++;
            }
        }
        std::cout << " Deadline: " << std::ctime(&deadlineTime);
    }
    std::cout << "Completed tasks: " << compCount << std::endl;
    std::cout << "Not completed tasks: " << notcompCount << std::endl;
}
int main() {
    std::vector<Task> Tasks;
    while (true) {
        std::cout << "Create" << std::endl;
        std::cout << "Delete " << std::endl;
        std::cout << "Modify" << std::endl;
        std::cout << "Completed" << std::endl;
        std::cout << "Display " << std::endl;
        std::cout << "Exit" << std::endl;
        std::cout << "which one?: ";
        std::string smth;
        std::cin >> smth;
        if (smth == "Create") {
            create(Tasks);
        }
        else if (smth == "Delete") {
            int index;
            std::cout << "Enter task index: ";
            std::cin >> index;
            del(Tasks, index);
        }
        else if (smth == "Modify") {
            int index;
            std::cout << "Enter task index: ";
            std::cin >> index;
            modify(Tasks, index);
        }
        else if (smth == "Completed") {
            int index;
            std::cout << "Enter task index: ";
            std::cin >> index;
            Completed(Tasks, index);
        }
        else if (smth == "Display") {
            display(Tasks);
        }
        else if (smth == "Exit") {
            break;
        }
        else {
            std::cout << "error" << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}