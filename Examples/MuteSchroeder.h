#pragma once

#include "MuteAudioPlayer.h"
#include "IRConv.h"
#include "MuteDelay.h"
#include "MuteSplit.h"
#include "MuteSine.h"
#include "MuteMix.h"
#include "SchroederAllpass.h"

#define NUM_REVS 10

class MuteSchroeder
{
public:
    SchroederAllpass SchroederAllpass[NUM_REVS];
    MuteAudioPlayer MuteAudioPlayer1;
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
        MuteAudioPlayer1.setAudioFile("/Users/tan/Documents/MUTE/AdvancedDSP26/drums.wav");
        MuteAudioPlayer1.prepare(sampleRate, samplesPerBlock);
        for (int i=0; i<NUM_REVS;++i)
            {
                SchroederAllpass[i].prepare(sampleRate, samplesPerBlock);
                SchroederAllpass[i].setDelay(M[i]);
                //SchroederAllpass[i].setGain(gains[i]);
                SchroederAllpass[i].setGain(0.9);
                SchroederAllpass[i].reset();
            }

    }
    void process(float * buffer, int numSamples)
    {
        MuteAudioPlayer1.process(buffer, numSamples);
        for (int i=0; i<NUM_REVS;++i)
        {
                SchroederAllpass[i].process(buffer, numSamples);
        }
    }
    
private:
};
