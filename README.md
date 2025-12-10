# RTS-Scheduler-SimLib
## Introduction
A simple RTS (Real-time system) priority-based scheduler simulation library for periodic tasks in C++.
## Features
<ol>
<li>Task Manager to create and manage task jobs.</li>
<li>Task set generator to generate schedulable task set with zero starting phase.</li>
<li>Inbuilt scheduling algorithms.</li>
</ol>

### Inbuilt algorithms
<ul>
<li>RMA - Rate monotonic algorithm</li>
<li>DMA - Deadline monotonic algorithm</li>
<li>EDF - Earliest deadline first</li>
<li>LST - Least slack time</li>
</ul>

## How to build
This library uses [CMake](https://cmake.org/) based build system.
To build with default configuration following commands can be ran from root directory of the project.
```sh
# To configure
cmake -S . -B build
# To build
cmake --build build
```
Alternatively, you can use generator specific methods to build. (E.g. By opening project solution in case of Visual Studio)
## How to use
Once you add [includes](includes/) folder as include folder for your project and linked to the compiled static library simply include header files that you require into your source files.
E.g.,
```c++
#include <taskmanager.h>
#include <algorithms/rma.h>
```
## Usage sample
```c++
#include <cstdio>
#include <iostream>
#include<taskmanager.h>
#include<taskgenerator.h>
#include<algorithms/rma.h>

int main()
{
    TaskManager<RMA> manager; //Creating a task manager with RMA as scheduler.
    TaskGenerator<RMA> generator; //Creating a task generator for RMA.
    auto tlist=generator.generate(3); //Generate 3 tasks.
    std::cout<<"Random tasks:\n";
    //Adding generated tasks to task manager.
    for (size_t i = 0; i < tlist.size(); i++)
    {
        manager.addTask(tlist[i].getStartT(),tlist[i].getPeriod(),tlist[i].getExectime(),tlist[i].getRelDeadline());
    }
    std::cout<<"=======================================================================================\n";
    std::cout<<"hp:"<<manager.getScheduleIntervel()<<"\n";
    std::cout<<"utilization :"<<TaskManager<RMA>::calcnetutil(tlist)<<" < "<<RMA::schedulable_util(tlist.size())<<'\n';

    std::cout<<"target tasks:\n";
    manager.printTasks();
    scanf("%*c");
    std::cout<<"=======================================================================================\n";
    manager.run(); //Run simulation for default duration.
    scanf("%*c");
    std::cout<<"history:\n";
    manager.printHistory(); //Print simulation history.

    return 0;
}
```
