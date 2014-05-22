#include <iostream>

#include "randsim.h"
#include "sched.h"

using namespace std;

int main (int argc, char *argv[]){

  // ideally parsed from commandline.
  // rate of arrival of tasks and resources is independent.
  // scale in case of tasks refers to size of tasks.
  // scale in case of resources, refers to the max size of the pool of resources.
  int maxTaskSize=20;
  float taskRate=0.3;
  int maxResources=60;
  float resourceRate=0.3;
  int taskIterations=100;
  list<int> taskList; // do.. while drawback.

  do {

    randsim task(taskRate,maxTaskSize);
    randsim resource(resourceRate,maxResources); // srand gets called twice :(
    sched scheduler; 
    list<int> resList;
    int totalResources=0;
    int totalTaskUnits=0; 

    // Only generate tasks if we have iterations left.
    if (taskIterations > 0){ 

      int newTask=task.getNext();
      if (newTask>0){

        taskList.push_back(newTask);
        totalTaskUnits+=newTask;

      }

    }

    // Generate resources
    int newResource=resource.getNext();
    if (newResource>0){
      resList.push_back(newResource);
      totalResources++;
    }

    // schedule!

    scheduler.schedule(taskList,resList, totalTaskUnits, totalResources);


  } while (taskIterations-- || !taskList.empty());

  
}
