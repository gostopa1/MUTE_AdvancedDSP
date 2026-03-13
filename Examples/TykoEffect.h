#pragma once
#include "ap1_mod.h"
#include "MuteSplit.h"
#include "MuteMix.h"
#include "MuteSine.h"


#define NUMALLPASS 8 // How many all pass filters to use
class TykoEffect
{
public:
    MuteSplit ms1, ms2;
    ap1_mod aps[NUMALLPASS]; // An array of all pass filters (i.e. multiple objects of the all pass class)
    MuteMix mx1;
    MuteSine sine1;
    
    float * buffer1;
    float * modBuffer;
    TykoEffect(){};
    ~TykoEffect(){};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
        sine1.prepare(sampleRate, samplesPerBlock);
        sine1.setFreq(0.5);
        sine1.setMinMaxValue(0, 1.0);
        
        ms1.prepare(sampleRate, samplesPerBlock);
        buffer1 = ms1.getPtr();
        
        ms2.prepare(sampleRate, samplesPerBlock); 
        modBuffer = ms2.getPtr();
        
        // Set up all the all pass filters in the array
        for (int i=0; i< NUMALLPASS; ++i)
        {
            aps[i].prepare(sampleRate, samplesPerBlock);
            aps[i].setMinMaxFrequency(300.0f, 3000.0f);
            aps[i].setDelay(2);
        }
    }
    void process(float * buffer, int numSamples)
    {
        ms1.process(buffer, numSamples); // Now buffer1 contains buffer
        ms2.process(buffer, numSamples); // Make another copy to have for the sine wave(s)
       
        sine1.process(modBuffer, numSamples);

        // Process all the all pass filters in the array with the same modulator (you can also have different modulators for each if you want)
        for (int i=0; i< NUMALLPASS; ++i)
        {
            aps[i].process_gain_with_mod(buffer1, modBuffer, numSamples);
        }
        
        mx1.process(buffer, buffer1, numSamples);
    }
    
private:
};
