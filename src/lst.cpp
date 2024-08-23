#include<lst.h>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<cmath>

LSTComparator::LSTComparator(TaskManager<LST> &manager) : m_manager(manager)
{
}

inline bool LSTComparator::operator()(Job* j1,Job* j2)
{
    float absd1=m_manager.getTask(j1->gettaskid()).getStartT()+m_manager.getTask(j1->gettaskid()).getPeriod()*(j1->jobindex())+m_manager.getTask(j1->gettaskid()).getRelDeadline();
    float absd2=m_manager.getTask(j2->gettaskid()).getStartT()+m_manager.getTask(j2->gettaskid()).getPeriod()*(j2->jobindex())+m_manager.getTask(j2->gettaskid()).getRelDeadline();
    float slack1=absd1-((j1->gettotalexecT())-(j1->getexecutedT()))-m_manager.t;
    float slack2=absd2-((j2->gettotalexecT())-(j2->getexecutedT()))-m_manager.t;
    // printf("abs: %s %f %s %f\n",m_manager.getTask(j1->gettaskid()).getname().c_str(),slack1,
    // m_manager.getTask(j2->gettaskid()).getname().c_str(),slack2);
    if (slack1<=slack2)
    {
        return false;
    }
    return true;
}

LSTComparator::~LSTComparator()
{
}

float LST::schedulable_util(unsigned int n)
{
    // if(n==0) return 1.0f;
    return 1.0f;
}

float LST::getPriority(Job *jobp)
{
    float absd=m_manager.getTask(jobp->gettaskid()).getStartT()+m_manager.getTask(jobp->gettaskid()).getPeriod()*(jobp->jobindex())+m_manager.getTask(jobp->gettaskid()).getRelDeadline();
    float slack1=absd-((jobp->gettotalexecT())-(jobp->getexecutedT()))-m_manager.t;
    return slack1;
}

LST::LST(TaskManager<LST> &manager) : m_manager(manager) //,queue(std::priority_queue<Job*,std::vector<Job*>,LSTComparator> (LSTComparator(manager)))
{

}

Job* LST::getJob()
{
    if(m_jobsheap.size()==0ULL){
        return NULL;
    }
    std::make_heap(m_jobsheap.begin(),m_jobsheap.end(),LSTComparator(m_manager));
    // std::cout<<"heap"<<'\n';
    // for (size_t i = 0; i < m_jobsheap.size(); i++)
    // {
    //     std::cout<<m_manager.getTask(m_jobsheap[i]->gettaskid()).getname()<<'\n';
    // }
    
    Job* job=m_jobsheap[0];
    // std::pop_heap<std::vector<Job*>::iterator,LSTComparator>(m_jobsheap.begin(),m_jobsheap.end(),LSTComparator(m_manager));
    return job;
}

void LST::addJob(Job* job)
{
    // queue.push(job);
    m_jobsheap.push_back(job);
    std::push_heap<std::vector<Job*>::iterator,LSTComparator>(m_jobsheap.begin(),m_jobsheap.end(),LSTComparator(m_manager));
}
void LST::removeJob(Job* job){
    if(job==m_jobsheap[0]){
        std::pop_heap<std::vector<Job*>::iterator,LSTComparator>(m_jobsheap.begin(),m_jobsheap.end(),LSTComparator(m_manager));
        // printf("size %u",m_jobsheap.size());
        // exit(0);
        m_jobsheap.pop_back();
    }
    else{
        m_jobsheap.erase(std::find(m_jobsheap.begin(),m_jobsheap.end(),job));
        std::make_heap<std::vector<Job*>::iterator,LSTComparator>(m_jobsheap.begin(),m_jobsheap.end(),LSTComparator(m_manager));
    }
}
LST::~LST()
{
}

float LST::nextEvent()
{
    
    
    return m_manager.nextrelease();
}
