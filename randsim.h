#ifndef RANDSIM_H
#define RANDSIM_H

class randsim {

public:
  // arrival rate controls if geftnext will return a value>0
  randsim(float rate, uint32_t scale, bool verbose);
  ~randsim() {}
  int getNext();

private:

  static bool once;

  float arrivalRate;
  uint32_t intRate;
  uint32_t scale;
  bool verbose;

};

#endif
