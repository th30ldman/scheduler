#include <iostream>

#include "sched.h"

using namespace std;

int sched::schedule(std::list<int>& tasks, std::list<int>& resources, int totalTaskUnits, int totalResources){

  list<int>::iterator taskIt;
  list<int>::iterator taskRes;

  // this is pretty ugly O(n) badness
  for (taskIt=tasks.begin(); taskIt != tasks.end(); ++taskIt){

    if (*taskIt > totalResources){
      // Can't schedule task, no resources available
      return 0;
        
    }
      
    while (*taskIt--)
      resources.pop_front();

  }

}
