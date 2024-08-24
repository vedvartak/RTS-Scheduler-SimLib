# RTS-Scheduler-SimLib
## Introduction
A simple RTS (Real-time system) priority-based scheduler simulation library for periodic tasks in C++.
## Features
<ol>
<li>Task Manager to create and manage task jobs.</li>
<li>Task set generator to generate schedulable task set with zero starting phase.</li>
<li>Inbuilt scheduling algorithms.</li>
</ol>
## Inbuilt algorithms
<ul>
<li>RMA</li>
<li>DMA</li>
<li>EDF</li>
<li>LST</li>
</ul>

## How to compile
To use this library you only require implimentation files in [src](src/) and header files in [includes](includes/).
The library can be compiled using any prefered C++ compiler e.g., GCC, MSVC, Clang etc. You just need to compile implimentation files in [src](src/) along with your project with [includes](includes/) folder added as include folder using compiler options ("-I {folder-path}" for GCC and Clang).
```sh
gcc {path-to-src}/* {path-to-your-src-files} -I {path-to-includes}
```
If required, you can compile the source code into static library that way you will only have to link it with [includes](includes/) folder added as include folder while compiling your project.
## How to use
Once you add [includes](includes/) folder as include folder for your compiler simply include header files that you require into your source files.
E.g.,
```c++
#include <taskmanager.h>
#include <rma.h>
```
## Usage sample
```c++
#include <cstdio>
#include <iostream>
#include<taskmanager.h>
#include<taskgenerator.h>
#include<rma.h>

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
