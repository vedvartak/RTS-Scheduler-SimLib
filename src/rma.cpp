#include<rma.h>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<cmath>
RMAComparator::RMAComparator(TaskManager<RMA> &manager) : m_manager(manager)
{
}

inline bool RMAComparator::operator()(Job* j1,Job* j2)
{
    if (m_manager.getTask(j1->gettaskid()).getPeriod()<=m_manager.getTask(j2->gettaskid()).getPeriod())
    {
        return false;
    }
    
    return true;
}

RMAComparator::~RMAComparator()
{
}



RMA::RMA(TaskManager<RMA> &manager):m_manager(manager)//,queue(std::priority_queue<Job*,std::vector<Job*>,RMAComparator> (RMAComparator(manager)))
{

}
float RMA::schedulable_util(unsigned int n){
    if(n==0) return 1.0f;
    return n*(std::pow(2,1.0f/n)-1.0f);
}
Job* RMA::getJob()
{
    if(m_jobsheap.size()==0ULL){
        return NULL;
    }
    Job* job=m_jobsheap[0];
    // std::pop_heap<std::vector<Job*>::iterator,RMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),RMAComparator(m_manager));
    return job;
}

float RMA::getPriority(Job* jobp)
{

    return m_manager.getTask(jobp->gettaskid()).getPeriod();
}

void RMA::addJob(Job* job)
{
    // queue.push(job);
    m_jobsheap.push_back(job);
    std::push_heap<std::vector<Job*>::iterator,RMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),RMAComparator(m_manager));
}
void RMA::removeJob(Job* job){
    if(job==m_jobsheap[0]){
        std::pop_heap<std::vector<Job*>::iterator,RMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),RMAComparator(m_manager));
        // printf("size %u",m_jobsheap.size());
        // exit(0);
        m_jobsheap.pop_back();
    }
    else{
        m_jobsheap.erase(std::find(m_jobsheap.begin(),m_jobsheap.end(),job));
        std::make_heap<std::vector<Job*>::iterator,RMAComparator>(m_jobsheap.begin(),m_jobsheap.end(),RMAComparator(m_manager));
    }
}
RMA::~RMA()
{
}

float RMA::nextEvent()
{
    
    
    return m_manager.nextrelease();
}
