/*
 ==============================================================================
 
 MuteSine.h
 Created: 15 Mar 2021 1:48:39am
 Author:  Athanasios Gotsopoulos
 
 ==============================================================================
 */
#define M_PI 3.14159265359

#pragma once
#include <JuceHeader.h>
class MuteSine
{
public:
    
    float phase=0;
    float phaseInc=0;

    float fs=48000.0;
    float volume=1.0;
    MuteSine()
    {
        phaseInc=2*M_PI*f0/fs;
    };
    
    ~MuteSine(){};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
        fs=sampleRate;
        phaseInc=2*M_PI*f0/fs;
    };
    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer[sample]=volume*sin(phase);
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
            
            buffer[sample]=volume*sin(phase);
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
    float setVolume(float newVolume){volume=newVolume;};
    float getVolume(){return volume;};
    
private:


    float f0=440;
    
};
