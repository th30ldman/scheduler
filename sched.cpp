#include <iostream>

#include "sched.h"

using namespace std;

int sched::schedule(std::list<int>& tasks, std::list<int>& resources, int& totalTaskUnits){

  list<int>::iterator taskIt;
  int depthOfQueue=0;
  int tasksConsumed=0;

  // Rudimentary concept:
  // Claw through the list (task list is handled as a LIFO with HOL considerations.)
  // and grab whichever task that can be resourced,
  // Wash/rinse/repeat until we're out of resources.
  // This gets around head of line blocking of a FCFS approach.
  // It does increase the risk that we leave a bunch of heavy tasks 'sitting'
  // at the front of the queue. There is a 'guard' of sorts
  // controlled by maxBacklog, that limits the amount of Tasks sitting at the head
  // of the queue.
  // Choice of maxBacklog is crucial wrt latency.
  // An philosophic guideline of sorts is Con Kolivas BFS:
  // http://en.wikipedia.org/wiki/Brain_Fuck_Scheduler
  // The underlying message being that keeping stuff simple tends to work best.
  // Note: BFS outperforms the 'stock' scheduler in the linux kernel under most common
  // situations.
  
  if (verbose)
    cout << "Tasks: " << tasks.size() << " Resources: " << resources.size() << endl; 


  // 1. Only recurse upto maxBackLog
  // 2. If resource queue is empty, bail.
  for (taskIt=tasks.begin(); taskIt != tasks.end() && resources.size() > 0 && depthOfQueue < maxBacklog; ++taskIt){
    
    if (*taskIt <= resources.size()){

      while ((*taskIt)--){
        // Value of tasks is 'units'
        // a resource just simply reflects the availability of a 'unit'.
        // So for each unit of tasks, we consume 1 resource.

        resources.pop_front();

      }
      // update totalTaskUnits;
      totalTaskUnits-=*taskIt;
      taskIt=tasks.erase(taskIt);

      tasksConsumed++;

    }

    if (tasksConsumed==0) {
      // This only ever triggers when it can not consume the first task.
      
      depthOfQueue++;
      continue;
      
    }

  }

  tasksPerCycle+=tasksConsumed;

  // update stats

  // Note that either of these can be pulled to get the number of iterations of the scheduler.
  resourceQueueDepth+=resources.size();
  taskQueueDepth+=tasks.size();
    
  if (depthOfQueue < maxBacklog){

    return tasksConsumed;

  } else {

    // if we reach this point, we're piling up the tasks at the head of the queue, and taking the
    // small tasks of the back of the queue, so skip out, and let the resource queue replenish.
    // This is a pretty good indication, there is more to do than resources available.

    maxDepthReached++;
    return 0;

  }

}

void sched::dumpStats() {

  cout << "Scheduler stats:" << endl << endl;;
  cout << "schedulerIterations " << getIterations() << endl << endl;
  cout << "Task queue:" << endl;
  cout << "Min: " << taskQueueDepth.min() << endl;
  cout << "Max: " << taskQueueDepth.max() << endl;
  cout << "Mean: " << taskQueueDepth.mean() << endl;
  cout << "Std: " << taskQueueDepth.stdDeviation() << endl;
  cout << endl;
  cout << "Tasks per cycle:" << endl;
  cout << "Min: " << tasksPerCycle.min() << endl;
  cout << "Max: " << tasksPerCycle.max() << endl;
  cout << "Mean: " << tasksPerCycle.mean() << endl;
  cout << "Std: " << tasksPerCycle.stdDeviation() << endl;
  cout << endl;
  cout << "Resource queue" << endl;
  cout << "Min: " << resourceQueueDepth.min() << endl;
  cout << "Max: " << resourceQueueDepth.max() << endl;
  cout << "Mean: " << resourceQueueDepth.mean() << endl;
  cout << "Std: " << resourceQueueDepth.stdDeviation() << endl << endl;
  cout << "Maximum backlog reached: " << maxDepthReached << endl;
  

}
