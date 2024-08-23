#include<edf.h>
#include<queue>
#include<cstdio>
#include<algorithm>
EDFComparator::EDFComparator(TaskManager<EDF> &manager) : m_manager(manager)
{
}

inline bool EDFComparator::operator()(Job* j1,Job* j2)
{
    float absd1=m_manager.getTask(j1->gettaskid()).getStartT()+m_manager.getTask(j1->gettaskid()).getPeriod()*(j1->jobindex())+m_manager.getTask(j1->gettaskid()).getRelDeadline();
    float absd2=m_manager.getTask(j2->gettaskid()).getStartT()+m_manager.getTask(j2->gettaskid()).getPeriod()*(j2->jobindex())+m_manager.getTask(j2->gettaskid()).getRelDeadline();
    // printf("abs: %s %f %s %f\n",m_manager.getTask(j1->gettaskid()).getname().c_str(),absd1,
    // m_manager.getTask(j2->gettaskid()).getname().c_str(),absd2);
    if (absd1<=absd2)
    {
        return false;
    }
    return true;
}

EDFComparator::~EDFComparator()
{
}

float EDF::schedulable_util(unsigned int n)
{
    return 1.0f;
}

float EDF::getPriority(Job *jobp)
{
    return m_manager.getTask(jobp->gettaskid()).getStartT()+m_manager.getTask(jobp->gettaskid()).getPeriod()*(jobp->jobindex())+m_manager.getTask(jobp->gettaskid()).getRelDeadline();
}

EDF::EDF(TaskManager<EDF> &manager) : m_manager(manager) //,queue(std::priority_queue<Job*,std::vector<Job*>,EDFComparator> (EDFComparator(manager)))
{

}

Job* EDF::getJob()
{
    if(m_jobsheap.size()==0ULL){
        return NULL;
    }
    Job* job=m_jobsheap[0];
    // std::pop_heap<std::vector<Job*>::iterator,EDFComparator>(m_jobsheap.begin(),m_jobsheap.end(),EDFComparator(m_manager));
    return job;
}

void EDF::addJob(Job* job)
{
    // queue.push(job);
    m_jobsheap.push_back(job);
    std::push_heap<std::vector<Job*>::iterator,EDFComparator>(m_jobsheap.begin(),m_jobsheap.end(),EDFComparator(m_manager));
}
void EDF::removeJob(Job* job){
    if(job==m_jobsheap[0]){
        std::pop_heap<std::vector<Job*>::iterator,EDFComparator>(m_jobsheap.begin(),m_jobsheap.end(),EDFComparator(m_manager));
        // printf("size %u",m_jobsheap.size());
        // exit(0);
        m_jobsheap.pop_back();
    }
    else{
        m_jobsheap.erase(std::find(m_jobsheap.begin(),m_jobsheap.end(),job));
        std::make_heap<std::vector<Job*>::iterator,EDFComparator>(m_jobsheap.begin(),m_jobsheap.end(),EDFComparator(m_manager));
    }
}
EDF::~EDF()
{
}

float EDF::nextEvent()
{
    
    
    return m_manager.nextrelease();
}
