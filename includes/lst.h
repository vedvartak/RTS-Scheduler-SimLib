#ifndef LST_H
#define LST_H
// #include<scheduler.h>
#include<taskmanager.h>
#include<queue>
class LST;
class LSTComparator
{
private:
    TaskManager<LST>& m_manager;
public:
    LSTComparator(TaskManager<LST>& manager);
    bool operator()(Job* j1,Job* j2);
    ~LSTComparator();
};



class LST//:public Scheduler
{
private:
    /* data */
    TaskManager<LST>& m_manager;
    std::vector<Job*> m_jobsheap;
public:
    // LST();
    static float schedulable_util(unsigned int n);
    LST(TaskManager<LST>& manager);
    Job* getJob();
    float getPriority(Job* jobp);
    void addJob(Job* job);
    void removeJob(Job* job);
    float nextEvent();
    ~LST();
};



#endif