#include<taskmanager.h>
#include<iostream>
unsigned int Task::i=0;
std::string Task::getname()
{
    return name;
}
float Task::getStartT() const
{
    return m_startphase;
}
float Task::getPeriod() const
{
    return m_period;
}
float Task::getExectime() const
{
    return m_exectime;
}
float Task::getRelDeadline() const
{
    return m_reldeadline;
}
size_t Task::lastJob() const
{
    return m_lastJob;
}
void Task::jobadded()
{
    m_lastJob++;
}

Task::Task(float startp, float p, float e, float relatived) : m_startphase(startp), m_period(p), m_exectime(e), m_reldeadline(relatived)
{
    name="T";
    name+=std::to_string(i);
    i++;
}
Task::Task(float startp, float p, float e):m_startphase(startp),m_period(p),m_exectime(e),m_reldeadline(p)
{
    name="T";
    name+=std::to_string(i);
    i++;
}

Task::~Task()
{
}


JobInstance::JobInstance(size_t taskid, float startT, float executedT):m_id(taskid),m_startT(startT),m_executedT(executedT)
{
}

JobInstance::~JobInstance()
{
}

Job::Job(size_t id,size_t jobindex,float e):m_taskid(id),m_jobindex(jobindex),m_totalexecT(e)
{
}

size_t Job::gettaskid() const
{
    return m_taskid;
}

float Job::getexecutedT() const
{
    return m_executedT;
}

float Job::gettotalexecT() const
{
    return m_totalexecT;
}

size_t Job::jobindex() const
{
    return m_jobindex;
}

void Job::exec(float t)
{
    m_executedT+=t;
    if(m_executedT>m_totalexecT) m_executedT=m_totalexecT;
}

Job::~Job()
{
}
