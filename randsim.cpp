#include <iostream>
#include <random>

#include "randsim.h"

randsim::randsim(float rate, int scale): arrivalRate(rate), scale(scale) {
  srandom(time(NULL));
  intRate=rate*0x7FFF; // scale to a rate we can compare to directly.
  std::cout << "rate " << intRate << std::endl;
}

int randsim::getNext() {

  long int compound=random();
  // use top 15 bits as prob, use lower 16 as val mod scale;
  int pb=(compound>>16)&0x7FFF; 
  // use bottom half as the value
  int val=(compound&0x7FFF)%scale;

  return pb<intRate?val:0;

}
