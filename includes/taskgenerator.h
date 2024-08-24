#ifndef TASKGENERATOR_H
#define TASKGENERATOR_H
#include<taskmanager.h>
#include<vector>
#include<taskgenerator.h>
#include<random>
#include<algorithm>
template<class scheduler_class>
class TaskGenerator
{
private:
    float m_maxperiod=20.0f;
    float m_minexec=1.0f;
public:
    TaskGenerator(/* args */);
    std::vector<Task> generate(unsigned int n);
    ~TaskGenerator();
};
template<class scheduler_class>
TaskGenerator<scheduler_class>::TaskGenerator(/* args */)
{
}
template <class scheduler_class>
std::vector<Task> TaskGenerator<scheduler_class>::generate(unsigned int n)
{
    unsigned int oldIndex=Task::i;
    std::vector<Task> tasklist;
    float totalutilization=scheduler_class::schedulable_util(n);
    std::cout<<"util:"<<totalutilization<<" "<<((size_t)1-2)+1<<'\n';
    std::random_device rd;
    std::mt19937 rng(rd());
    
    size_t tries=0U;
    if(std::ceil((n)/totalutilization)>=m_maxperiod){
        printf("gen error\n");
        return tasklist;
    }
    for (size_t i = 0; i < n; i++)
    {
        // if(tries>10*n) return tasklist;

        int minperiod=std::ceil((n-i)/totalutilization);
        // std::cout<<"what "<<i<<" minp "<<minperiod<<" total"<<totalutilization<<"\n";
        if(minperiod>=m_maxperiod){
            
            if(i==0){
                // std::cout<<"min "<<minperiod<<"total"<<totalutilization<<"\n";
                // return tasklist;
                i-=1;
                tries++;
                continue;
            }
            else{
                // std::cout<<"kmin "<<minperiod<<"total"<<totalutilization<<"\n";
                totalutilization+=tasklist[tasklist.size()-1].getExectime()/tasklist[tasklist.size()-1].getPeriod();
                tasklist.pop_back();
                
                i-=2;
                tries++;
                continue;
            }
        }
        std::uniform_int_distribution<int> distp=std::uniform_int_distribution<int>(std::max(minperiod,2),m_maxperiod);
        float p=distp(rng);
        float e;
        // std::uniform_real_distribution diste=std::uniform_real_distribution(1.0f,p);
        int maxexec=p*totalutilization;
        if(maxexec<m_minexec){
                // std::cout<<i<<"util "<<totalutilization<<" p "<<p<<" max "<<maxexec<<" min "<<m_minexec<<"\n";
                // std::cout<<"here "<<maxexec<<" \n";
                tries++;
                i--;
                continue;
        }
        do
        {
            
            std::uniform_int_distribution<int> diste=std::uniform_int_distribution<int>(m_minexec,maxexec);
            // std::cout<<p<<" min "<<m_minexec<<" e max:"<<maxexec<<'\n';
            e=diste(rng);
            // std::cout<<"e:"<<e<<'\n';
        } while ((e/p)>=totalutilization);
        
        
        tasklist.emplace_back(0,p,std::min(p,e));
        totalutilization-=(std::min(p,e)/p);
        // std::cout<<"util:"<<totalutilization<<'\n';
    }
    
    // printf("normal\n");
    Task::setIndexId(oldIndex);
    return tasklist;
}
template <class scheduler_class>
TaskGenerator<scheduler_class>::~TaskGenerator()
{
}


#endif