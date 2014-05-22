#ifndef RANDSIM_H
#define RANDSIM_H

class randsim {

public:
  // arrival rate controls if geftnext will return a value>0
  randsim(float rate, int scale);
  ~randsim() {}
  int getNext();

private:
  float arrivalRate;
  int intRate;
  int scale;

};

#endif
