#define M_PI 3.14159265359

#pragma once
#include <JuceHeader.h>
class MuteCosine
{
public:
    
    float phase=0;
    float phaseInc=0;

    float fs=48000.0;
    float volume=1.0;
    MuteCosine()
    {
        phaseInc=2*M_PI*f0/fs;
    };
    
    ~MuteCosine(){};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
        fs=sampleRate;
        phaseInc=2*M_PI*f0/fs;
    };
    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer[sample]=volume*cos(phase);
            phase+=phaseInc;
            if (phase>2*M_PI)
            {
                phase-=2*M_PI;
            }
            
            
        }
    };
    
    void processWithMod(float * buffer, float * modBuffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            if (modBuffer[sample]!=0.0)
            {
            phaseInc=2*M_PI*(f0*pow(2,modBuffer[sample]/12))/fs;
            }
            
            buffer[sample]=volume*cos(phase);
            phase+=phaseInc;
            if (phase>2*M_PI)
            {
                phase-=2*M_PI;
            } 
        }
    };
    void setFreq(float newfreq) { f0 = newfreq; phaseInc=2*M_PI*f0/fs;};
    float getFreq(){ return f0;};
    void setPhase(float newPhase){ phase = newPhase;};
    float getPhase(){ return phase;};
private:


    float f0=440;
    
};

