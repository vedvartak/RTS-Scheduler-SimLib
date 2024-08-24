#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<numeric>//new
class Task
{
private:
    std::string name="Task";
    float m_startphase=0;
    float m_period=1;
    float m_exectime=1;
    float m_reldeadline=m_period;
    size_t m_lastJob=0;
public:
    static unsigned int i;
    static unsigned int setIndexId(unsigned int i);
    // Task(/* args */)=default;
    std::string getname();
    float getStartT() const;
    float getPeriod() const;
    float getExectime() const;
    float getRelDeadline() const;
    size_t lastJob() const;
    void jobadded();
    Task(float startp,float p,float e,float relatived);
    Task(float startp,float p,float e);
    ~Task();
};
class JobInstance
{
private:
public:
    size_t m_id=0;//task id
    float m_startT=0;
    float m_executedT=0;
    float m_totalexecT;
    JobInstance(size_t taskid,float startT,float executedT);
    ~JobInstance();
};

class Job
{
private:
    size_t m_taskid=0;
    size_t m_jobindex;
    float m_executedT=0;
    float m_totalexecT;
public:
    Job(size_t id,size_t jobindex,float e);
    size_t gettaskid() const;
    float getexecutedT() const;
    float gettotalexecT() const;
    size_t jobindex() const;
    void exec(float t);
    ~Job();
};




template<class Scheduler_class>
class TaskManager
{
public:
    std::vector<Job*> jobs;
    static float calcnetutil(const std::vector<Task>& tasklist);
private:
    // float t=0;
    std::vector<Task> tasks;
    Scheduler_class scheduler;
    void addJob(size_t taski);
    void removeJob(Job* jobp);
public:
    std::vector<JobInstance> history;//time diagram
    
    size_t taskcount();
    float getScheduleIntervel();
    bool testdeadline(float t);
    void printHistory();
    float t=0;
    TaskManager(/* args */);
    Task getTask(size_t taskid);
    void addTask(float startp,float p,float e,float relatived);
    void addTask(float startp,float p,float e);
    void printTasks();
    void update();
    Job* schedule();
    float nextrelease();
    float exec(Job* jobp);

    void run(float interval);
    void run();
    ~TaskManager();
};

template <class Scheduler_class>
float TaskManager<Scheduler_class>::calcnetutil(const std::vector<Task>& tasklist)
{
    float util=0;
    for (size_t i = 0; i < tasklist.size(); i++)
    {
        util+=tasklist[i].getExectime()/tasklist[i].getPeriod();
        // std::cout<<"e "<<tasklist[i].getExectime()<<" p "<<tasklist[i].getPeriod()<<'\n';
    }
    return util;
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::printHistory()
{
    for (size_t i = 0; i < history.size(); i++)
    {
        std::cout<<tasks[history[i].m_id].getname()<<" "<<history[i].m_startT<<" "<<history[i].m_executedT<<'\n';
    }
    
}
template<class Scheduler_class>
size_t TaskManager<Scheduler_class>::taskcount()
{
    return tasks.size();
    
}
template<class Scheduler_class>
float TaskManager<Scheduler_class>::getScheduleIntervel()
{
    if(tasks.size()==0) return 0.0f;
    if(tasks.size()==1) return (std::floor(tasks[0].getStartT()/tasks[0].getPeriod())+1)*tasks[0].getPeriod();
    unsigned int lcm=std::lcm<unsigned int,unsigned int>(tasks[0].getPeriod(),tasks[1].getPeriod());
    float maxphase=std::max(tasks[0].getStartT(),tasks[1].getStartT());
    for (size_t i = 2; i < tasks.size(); i++)
    {
        lcm=std::lcm<unsigned int,unsigned int>((lcm),tasks[i].getPeriod());
        maxphase=std::max(maxphase,tasks[i].getStartT());
    }
    
    return (std::floor(maxphase/lcm)+1)*lcm;
    
}

template<class Scheduler_class>
bool TaskManager<Scheduler_class>::testdeadline(float t){
    bool out=0;
    for (size_t i = 0; i < jobs.size(); i++)
    {
        float absd=tasks[jobs[i]->gettaskid()].getStartT()+(jobs[i]->jobindex())*(tasks[jobs[i]->gettaskid()].getPeriod());
        absd+=tasks[jobs[i]->gettaskid()].getRelDeadline();
        if(absd<=t){
            out=1;
            removeJob(jobs[i]);
        }
    }
    return out;
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::addJob(size_t taski)
{
    printf("<add job> at %f task_id %lu job index %lu\n",t,taski,tasks[taski].lastJob());
    Job* newjob=new Job(taski,tasks[taski].lastJob(),tasks[taski].getExectime());
    jobs.push_back(newjob);
    scheduler.addJob(newjob);
    tasks[taski].jobadded();
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::removeJob(Job* jobp)
{
    // printf("job completed %f\n",t);
    scheduler.removeJob(jobp);
    delete jobp;
    jobs.erase(std::find(jobs.begin(),jobs.end(),jobp)); //TODO
    // tasks[taski].jobadded();
}
template<class Scheduler_class>
TaskManager<Scheduler_class>::TaskManager():scheduler(Scheduler_class(*this))
{
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::addTask(float startp, float p, float e, float relatived)
{
    tasks.emplace_back(startp,p,e,relatived);
}
template <class Scheduler_class>
inline Task TaskManager<Scheduler_class>::getTask(size_t taskid)
{
    return tasks[taskid];
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::addTask(float startp, float p, float e)
{
    tasks.emplace_back(startp,p,e);
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::printTasks()
{
    for (size_t i = 0; i < tasks.size(); i++)
    {
        std::cout << tasks[i].getname() << " "
                    <<tasks[i].getStartT() << " "
                    <<tasks[i].getPeriod()<<" "
                    <<tasks[i].getExectime()<<" "
                    <<tasks[i].getRelDeadline() << '\n';
    }
}
template<class Scheduler_class>
void TaskManager<Scheduler_class>::update()
{
    for (size_t i = 0; i < tasks.size(); i++)
    {
        Task& temptask=tasks[i];
        if((temptask.getStartT()+temptask.getPeriod()*(temptask.lastJob()))<=t){
            addJob(i);
        }
    }
    
}
template<class Scheduler_class>
Job* TaskManager<Scheduler_class>::schedule()
{
    return scheduler.getJob();
    
}
template<class Scheduler_class>
float TaskManager<Scheduler_class>::nextrelease()
{
    
    float nextreleaseT=tasks[0].getStartT()+tasks[0].getPeriod()*(tasks[0].lastJob());
    float temprel=0;
    for (size_t i = 1; i < tasks.size(); i++)
    {
        temprel=tasks[i].getStartT()+tasks[i].getPeriod()*(tasks[i].lastJob());
        if(temprel<nextreleaseT) nextreleaseT=temprel;
    }
    return nextreleaseT;
}
template<class Scheduler_class>
float TaskManager<Scheduler_class>::exec(Job* jobp)
{
    float nextevent=scheduler.nextEvent();
    if(jobp==NULL){
        
        return nextevent-t;
    }
    float runT=std::min((jobp->gettotalexecT())-(jobp->getexecutedT()),nextevent-t);

    jobp->exec(runT);
    history.emplace_back(jobp->gettaskid(),t,runT);
    if((jobp->gettotalexecT())==(jobp->getexecutedT())){
        // printf("job completed %f\n",t+runT);
        removeJob(jobp);
    }
    
    return runT;
}
template <class Scheduler_class>
void TaskManager<Scheduler_class>::run(float interval)
{
    Job* jobp=NULL;
    float tpassed=0.0f;
    std::string name;
    while (t<interval)
    {
        update(); //update jobs ready queue
        jobp=schedule();
        if(jobp!=NULL){
        name=getTask(jobp->gettaskid()).getname();
        printf("<scheduling> %s at %f job index:%u\n",name.c_str(),t,jobp->jobindex());
        }

        tpassed=exec(jobp);
        if(jobp!=NULL)
        printf("<run> %s for %f\n",name.c_str(),tpassed);
        else printf("<idle> for %f\n",tpassed);
        if(testdeadline(t+tpassed)){
            printf("<<deadline missed>>\n");
            break;
        }
        t+=tpassed;
    }
}
template <class Scheduler_class>
void TaskManager<Scheduler_class>::run()
{
    run(std::min(getScheduleIntervel(),200.0f));
}
template <class Scheduler_class>
TaskManager<Scheduler_class>::~TaskManager()
{
}




#endif