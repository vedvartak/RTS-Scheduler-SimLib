#include<dma.h>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<cmath>

DMAComparator::DMAComparator(TaskManager<DMA> &manager) : m_manager(manager)
{
}

inline bool DMAComparator::operator()(Job* j1,Job* j2)
{
    float reld1=m_manager.getTask(j1->gettaskid()).getRelDeadline();
    float reld2=m_manager.getTask(j2->gettaskid()).getRelDeadline();
    // printf("abs: %s %f %s %f\n",m_manager.getTask(j1->gettaskid()).getname().c_str(),absd1,
    // m_manager.getTask(j2->gettaskid()).getname().c_str(),absd2);
    if (reld1<=reld2)
    {
        return false;
    }
    return true;
}

DMAComparator::~DMAComparator()
{
}

float DMA::schedulable_util(unsigned int n)
{
    if(n==0) return 1.0f;
    return n*(std::pow(2,1.0f/n)-1.0f);
}

float DMA::getPriority(Job *jobp)
{
    return m_manager.getTask(jobp->gettaskid()).getRelDeadline();
}

DMA::DMA(TaskManager<DMA> &manager) : m_manager(manager) //,queue(std::priority_queue<Job*,std::vector<Job*>,DMAComparator> (DMAComparator(manager)))
{

}

Job* DMA::getJob()
{
    if(m_jobsheap.size()==0ULL){
        return NULL;
    }
    Job* job=m_jobsheap[0];
    // std::pop_heap<std::vector<Job*>::iterator,DMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),DMAComparator(m_manager));
    return job;
}

void DMA::addJob(Job* job)
{
    // queue.push(job);
    m_jobsheap.push_back(job);
    std::push_heap<std::vector<Job*>::iterator,DMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),DMAComparator(m_manager));
}
void DMA::removeJob(Job* job){
    if(job==m_jobsheap[0]){
        std::pop_heap<std::vector<Job*>::iterator,DMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),DMAComparator(m_manager));
        // printf("size %u",m_jobsheap.size());
        // exit(0);
        m_jobsheap.pop_back();
    }
    else{
        m_jobsheap.erase(std::find(m_jobsheap.begin(),m_jobsheap.end(),job));
        std::make_heap<std::vector<Job*>::iterator,DMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),DMAComparator(m_manager));
    }
}
DMA::~DMA()
{
}

float DMA::nextEvent()
{
    
    
    return m_manager.nextrelease();
}
