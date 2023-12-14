void displayCriticalPath()
{

    auto criticalTask = std::max_element(taskList.begin(), taskList.end(), [](const task &a, const task &b)
    {
        return a.duration < b.duration;
    });

    if(criticalTask != taskList.end())
    {
        std::cout << "Critical Path Task: " << std::endl;
        std::cout << "Name: " <, criticalTask->name << ", Duration: " << criticalTask->duration << std::endl;
    }
    else
    {
        std::cout << "No task in the schedule. " << std::endl;
    }
}