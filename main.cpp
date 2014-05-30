#include <iostream>

#include "randsim.h"
#include "sched.h"

using namespace std;

int main (int argc, char *argv[]){

  // ideally parsed from commandline.
  // rate of arrival of tasks and resources is independent.
  // scale in case of tasks refers to size of tasks.
  // scale in case of resources, refers to the max size of the pool of resources.
  uint32_t maxTaskSize=10;
  float taskRate=0.5;
  uint32_t maxResources=10;
  float resourceRate=0.25;
  int taskIterations=400000;
  int maxTaskQueueDepth=10;
  bool verbose=0;

  list<int> taskList;
  list<int> resList;
  int totalTaskUnits=0; 
  randsim task(taskRate,maxTaskSize,verbose);
  randsim resource(resourceRate,maxResources,verbose);
  sched scheduler(maxTaskQueueDepth, verbose); 

  do {

    // Only generate tasks if we have iterations left.
    if (taskIterations > 0){ 

      int newTask=task.getNext();
      if (newTask>0){

        taskList.push_back(newTask);
        totalTaskUnits+=newTask;

      }

    }

    // Generate resources
    // Since resources are 1 unit each, in order to scale correctly wrt tasks
    // we need to generate at least the same amount of resources as the possible size
    // of tasks per cycle.
    // As per the assignment we don't have to worry about duplicates, since a particular
    // resource may have multiple cores. 
    // if uniqueness was required than this should be a set instead of a list, and 
    // maxResources would have to be sufficient. Duplicates generated would simply be
    // dropped. That would affect the nature of the random distribution. (Given machinations
    // in randsim.cpp it is unlikely uniform anyway.)
    for (int i=0; i<maxTaskSize; i++){

      int newResource=resource.getNext();

      if (newResource>0){

        resList.push_back(newResource);
        
      }

    }

    // schedule!

    scheduler.schedule(taskList,resList, totalTaskUnits);
    
  } while (--taskIterations > 0 || !taskList.empty());

  scheduler.dumpStats();
  
  cout << "Needed " << (~taskIterations)+1 << " extra iterations to clean up task queue" << endl;

  return 0;
  
}
