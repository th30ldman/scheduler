#include <iostream>
#include <random>

#include "randsim.h"

using namespace std;

bool randsim::once=true;

randsim::randsim(float rate, uint32_t scale, bool verbose): arrivalRate(rate), scale(scale), verbose(verbose) {

  if(once){
    // only execute srandom once for the lifetime of the program.
    srandom(time(NULL));
    once=false;
  }

  intRate=rate*0xFFFF; // scale to a rate we can compare to directly.
  if (verbose)
    cout << "rate edge at " << intRate << endl;

}

int randsim::getNext() {

  long int compound=random();
  // use top 16 bits as prob, use lower 16 as val mod scale;
  uint32_t pb=(compound>>16)&0xFFFF; 
  // use bottom half as the value
  uint32_t val=(compound&0xFFFF)%scale;

  return pb<intRate?val:0;

}
