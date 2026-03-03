#pragma once

#include "MuteDelay.h"
#include "MuteMix.h"
#include "ap1_mod.h"

#define NUM_REVS 10
class MuteSchroeder
{
public:
    ap1_mod ap1_mods[NUM_REVS];

    float gains[NUM_REVS] = {0.7, 0.7, 0.7};
    //int M[NUM_REVS] = {125,42,12};
    static constexpr int M[NUM_REVS] = {
    113,   // 2.354 ms
    173,   // 3.604 ms
    257,   // 5.354 ms
    389,   // 8.104 ms
    577,   // 12.021 ms
    821,   // 17.104 ms
    1153,  // 24.021 ms
    1601,  // 33.354 ms
    2203,  // 45.896 ms
    3001   // 62.521 ms
};
    
    MuteSchroeder(){};
    ~MuteSchroeder(){};
    float * buffer2;
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
        for (int i=0; i<NUM_REVS;++i)
            {   ap1_mods[i].setModOn(true);
                ap1_mods[i].prepare(sampleRate, samplesPerBlock);
                ap1_mods[i].setDelay(M[i]);
                ap1_mods[i].setModAmount(M[i]/4);
                ap1_mods[i].setGain(0.9);
                ap1_mods[i].reset();
            }
    }
    void process(float * buffer, int numSamples)
    {
        for (int i=0; i<NUM_REVS;++i)
        {
                ap1_mods[i].process(buffer, numSamples);
        }
    }
    
private:
};
