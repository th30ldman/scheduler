#ifndef SCHED_H
#define SCHED_H

#include <list>

class sched {

public:
  sched() {}
  ~sched() {}
  int schedule(std::list<int>& tasks, std::list<int>& resources, int totalTaskUnits, int totalResources);
};

#endif
