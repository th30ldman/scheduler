#ifndef SCHED_H
#define SCHED_H

#include <list>

class sched {

public:
sched(int maxBacklog, bool verbose):maxBacklog(maxBacklog),verbose(verbose){
    maxTaskQueueDepth=0;
    maxResourceQueueDepth=0;
    maxDepthReached=0;
    schedulerIterations=0;
  }

  ~sched() {}

  int schedule(std::list<int>& tasks, std::list<int>& resources, int& totalTaskUnits);
  // meddles with the task, resources lists, and totalTaskUnits.
  // returns 0 if it could not schedule tasks
  // returns number of tasks it processed if it scheduled tasks succesfully.
  
  void dumpStats();

private:
  int maxBacklog;
  bool verbose;
  int maxTaskQueueDepth;
  int maxResourceQueueDepth;
  int maxDepthReached;
  int schedulerIterations;
   
};

#endif
