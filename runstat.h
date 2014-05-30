#ifndef RUNSTAT_H
#define RUNSTAT_H

#include <climits>
#include <cmath>

// Simple class to maintain running stats on integer values
// mean and stddev are calculated per B.P Welford's article.
// See TAOCP/Knuth Vol 2 page 232.

class runstat {

public:

  runstat(){

    samples=0;
    m_sum=0;
    m_mean=0;
    m_min=ULLONG_MAX;
    m_max=0;

  }

  ~runstat() {}

  runstat& operator+= (const uint64_t sample){

    double prevMean=m_mean;

    samples++;
    m_max  = sample>m_max?sample:m_max;
    m_min  = sample<m_min?sample:m_min;
    m_mean +=(sample-prevMean)/(double)samples;
    m_sum  +=(sample-prevMean)*(sample-m_mean);

  }
  
  uint64_t noSamples(){
    return samples;
  }

  uint64_t min(){
    return m_min;
  }

  uint64_t max(){
    return m_max;
  }

  double mean(){
    return m_mean;
  }
  
  double variance(){
    if (samples > 1) // make sure we don't div/0
      return m_sum/(double)(samples-1);
    else
      return 0;
  }

  double stdDeviation(){
    return sqrt(variance());
  }


private:
  uint64_t samples;
  uint64_t m_min;
  uint64_t m_max;
  double m_sum;
  double m_mean;

  
};

#endif
