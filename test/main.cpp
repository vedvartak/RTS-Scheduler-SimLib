
#include<cstdio>
#include<timer.h>

#include <cstdio>
#include <algorithm>
#include <timer.h>
#include <filesystem>
#include<cmath>
#include<taskmanager.h>
#include<taskgenerator.h>
#include<edf.h>
#include<rma.h>
#include<dma.h>
#include<lst.h>

using curr_scheduler=RMA;
#define USE_RANDOM_TASKS
int main()
{
    TaskManager<curr_scheduler> manager;
    TaskGenerator<curr_scheduler> generator;
    #ifdef USE_RANDOM_TASKS
    auto tlist=generator.generate(3);
    std::cout<<"Random tasks:\n";
    // for (size_t i = 0; i < tlist.size(); i++)
    // {
    //     std::cout << tlist[i].getname() << " "
    //                 <<tlist[i].getStartT() << " "
    //                 <<tlist[i].getPeriod()<<" "
    //                 <<tlist[i].getExectime()<<" "
    //                 <<tlist[i].getRelDeadline() << '\n';
    // }
    // scanf("%*c");
    for (size_t i = 0; i < tlist.size(); i++)
    {
        manager.addTask(tlist[i].getStartT(),tlist[i].getPeriod(),tlist[i].getExectime(),tlist[i].getRelDeadline());
    }
    #else

    // std::cout<<"util "<<TaskManager<RMA>::calcnetutil(tlist)<<'\n';
    // manager.addTask(0,20,3);
    // manager.addTask(0,5,2);
    // manager.addTask(0,10,2);
    // manager.addTask(1,6,1);
    //EDF
    // manager.addTask(0,4,1);
    // manager.addTask(0,5,2);
    // manager.addTask(0,7,2);
    // LST
    // manager.addTask(0,2,0.8);
    // manager.addTask(0,5,1.5);
    // manager.addTask(0,5.1,1.5);
//     0 10 6 10
// T4 0 14 2 14
// T5 0 6 1 6
    // manager.addTask(0 ,10, 6 ,10);
    // manager.addTask(0 ,14, 2 ,14);
    // manager.addTask(0 ,6 ,1, 6);
    #endif
    std::cout<<"=======================================================================================\n";
    std::cout<<"hp:"<<manager.getScheduleIntervel()<<"\n";
    std::cout<<"utilization :"<<TaskManager<curr_scheduler>::calcnetutil(tlist)<<" < "<<curr_scheduler::schedulable_util(tlist.size())<<'\n';

    std::cout<<"target tasks:\n";
    manager.printTasks();
    scanf("%*c");
    std::cout<<"=======================================================================================\n";
    Timer t1("timer");
    t1.begin();
    manager.run();
    t1.end();
    scanf("%*c");
    std::cout<<"history:\n";
    manager.printHistory();

    return 0;
}
