#ifndef SCHEDULER_H
#define SCHEDULER_H
#include<taskmanager.h>
class Scheduler
{
private:
    /* data */
public:
    // Scheduler();
    // template<class Scheduler_class>
    // Scheduler(TaskManager<Scheduler_class>& manager);
    int getJob(const std::vector<Job>& jobs,Job* job);
    void addJob(Job job);
    ~Scheduler();
};
// template<class Scheduler_class>
// Scheduler::Scheduler(TaskManager<Scheduler_class>& manager)
// {
// }


#endif