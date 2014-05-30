#ifndef SCHED_H
#define SCHED_H

#include <list>
#include "runstat.h"

class sched {

public:
sched(int maxBacklog, bool verbose):maxBacklog(maxBacklog),verbose(verbose){
    maxDepthReached=0;
  }

  ~sched() {}

  int schedule(std::list<int>& tasks, std::list<int>& resources, int& totalTaskUnits);
  // meddles with the task, resources lists, and totalTaskUnits.
  // returns 0 if it could not schedule tasks
  // returns number of tasks it processed if it scheduled tasks succesfully.
  
  void dumpStats();

  uint64_t getIterations(){

    return (resourceQueueDepth.noSamples());
            
  }
  
private:
  int maxBacklog;
  bool verbose;
  // stat stuff
  
  runstat taskQueueDepth;
  runstat resourceQueueDepth;
  runstat tasksPerCycle;
  int maxDepthReached;
   
};

#endif
