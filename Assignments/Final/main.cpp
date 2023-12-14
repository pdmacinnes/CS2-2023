#include <iostream>
#include <list>
#include <set>
#include <algorithm>

class Task 
{
public:
    std::string name;
    int priority;
    int duration;
    int uniqueId;
    std::set<Task*> dependencies;

    Task(const std::string& n, int p, int d, int id) : name(n), 
           priority(p), duration(d), uniqueId(id) {}
};

class TaskScheduler 
{
private:
    std::list<Task> taskList;
    std::set<Task*> taskSet;

public:
    // Add Task to scheduler
    void addTask(Task* task) 
    {
        taskList.push_back(*task); // Add the task object itself to the list
        taskSet.insert(task); // Insert the pointer to the task object in the set
    }


    // Establish dependency between tasks
    void addDependency(const std::string& taskName, const std::string& dependentTaskName) 
    {
        Task* task = findTaskByName(taskName);
        Task* dependentTask = findTaskByName(dependentTaskName);

        if (task == nullptr || dependentTask == nullptr) 
        {
            std::cout << "Invalid task names for dependency" << std::endl;
        } else 
        {
            task->dependencies.insert(dependentTask);
        }
    }

    // Remove Task from scheduler
    void removeTask(const std::string& taskName) 
    {
        auto it = std::find_if(taskList.begin(), taskList.end(), [&taskName](const Task& task) {
            return task.name == taskName;
        });

        if (it != taskList.end()) 
        {
            taskSet.erase(&(*it));
            taskList.erase(it);
        } else 
        {
            std::cout << "Task not found: " << taskName << std::endl;
        }
    }

    // Update priority of a task
    void updatePriority(const std::string& taskName, int newPriority) 
    {
        Task* task = findTaskByName(taskName);

        if (task != nullptr) 
        {
            task->priority = newPriority;
        } else 
        {
            std::cout << "Task not found: " << taskName << std::endl;
        }
    }

    // Display scheduled tasks using STL sort algorithm
    void displayScheduledTasks() 
    {
        std::list<Task> sortedTasks = taskList;
        sortedTasks.sort([](const Task& a, const Task& b) 
        {
            return a.priority < b.priority; // Sort tasks based on priority
        });

        for (const auto& task : sortedTasks) 
        {
            std::cout << "Task: " << task.name << ", Priority: " << task.priority << ", Duration: " << task.duration << std::endl;
        }
    }

    // Find task with the longest duration (Critical Task)
    Task* findCriticalTask() 
    {
        if (taskList.empty()) 
        {
            return nullptr;
        }

        auto criticalTask = taskList.begin();
        for (auto it = taskList.begin(); it != taskList.end(); ++it) 
        {
            if (it->duration > criticalTask->duration) 
            {
                criticalTask = it;
            }
        }
        return &(*criticalTask);
    }

    // Display critical path
    void displayCriticalPath() 
    {
        Task* criticalTask = findCriticalTask();

        if (criticalTask == nullptr) 
        {
            std::cout << "No tasks in the schedule" << std::endl;
        } else 
        {
            std::cout << "Critical Task: " << criticalTask->name << ", Duration: " << criticalTask->duration << std::endl;
        }
    }

private:
    // Utility function to find a Task by name
    Task* findTaskByName(const std::string& taskName) 
    {
        auto it = std::find_if(taskList.begin(), taskList.end(), [&taskName](const Task& task) {
            return task.name == taskName;
        });

        if (it != taskList.end()) 
        {
            return &(*it);
        } else 
        {
            return nullptr;
        }
    }
};

int main() 
{
    TaskScheduler scheduler;

    // Define tasks with varying priorities and dependencies
    Task* task1Ptr = new Task("Task1", 1, 10, 1001);
    Task* task2Ptr = new Task("Task2", 2, 8, 1002);
    Task* task3Ptr = new Task("Task3", 3, 12, 1003);

    // Add tasks to the scheduler
    scheduler.addTask(task1Ptr);
    scheduler.addTask(task2Ptr);
    scheduler.addTask(task3Ptr);

    // Establish dependencies between tasks
    scheduler.addDependency("Task1", "Task2");
    scheduler.addDependency("Task2", "Task3");

    // Display scheduled tasks after sorting based on priorities
    scheduler.displayScheduledTasks();

    // Remove a task ("Task2")
    scheduler.removeTask("Task2");

    // Update priority of a task ("Task3")
    scheduler.updatePriority("Task3", 4);

    // Display updated scheduled tasks after changes
    scheduler.displayScheduledTasks();

    // Display the critical path
    scheduler.displayCriticalPath();

    // Clean up dynamically allocated memory
    delete task1Ptr;
    delete task2Ptr;
    delete task3Ptr;

    return 0;
}
