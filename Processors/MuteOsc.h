/*
  ==============================================================================

    MuteOsc.h
    Created: 11 Apr 2022 1:14:53pm
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once

#define M_PI 3.14159265359

#pragma once
#include <JuceHeader.h>

class MuteOsc
{
public:
 
    enum Osc {Sine, Square, Saw, Triangle};
    Osc currentOsc = Sine;
    float phase=0;
    float phaseInc=0;
    float phaseTri=0;
    float phaseTriInc=0;
    // To calculate phase for the triangle
    float direction = 1.0f;
    float PI1o4=2.0f*M_PI*0.25f; // 1 * 2*PI / 4
    float PI2o4=2.0f*M_PI*0.50f;  // 2 * 2*PI / 4
    float PI3o4=2.0f*M_PI*0.75f; // 3 * 2*PI / 4

    float fs=48000.0;
    float volume=1.0;
    MuteOsc()
    {
        phaseInc=2*M_PI*f0/fs;
    };
    
    ~MuteOsc(){};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
        fs=sampleRate;
        phaseInc=2*M_PI*f0/fs;
    };
    void process(float * buffer, int numSamples)
    {
        switch(currentOsc)
        {
            case Osc::Sine:
                processSine(buffer, numSamples);
                break;
            case Osc::Square:
                processSquare(buffer, numSamples);
                break;
            case Osc::Triangle:
                processTriangle(buffer, numSamples);
                break;
            case Osc::Saw:
                processSaw(buffer, numSamples);
                break;
        }
    };
    
    void processSine(float * buffer, int numSamples)
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
    void processSquare(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer[sample]=volume*signFunc(phase-M_PI);
            phase+=phaseInc;
            if (phase>2*M_PI)
            {
                phase-=2*M_PI;
            }
        }
    };
    void processSaw(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            buffer[sample]=volume*((phase/M_PI)-1.0f);
            phase+=phaseInc;
            if (phase>2*M_PI)
            {
                phase-=2*M_PI;
            }
        }
    };
    void processTriangle(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            float temp = 2.0*phaseInc /M_PI;
            if ((phaseTri + temp)>1.0f)
            {
                direction=-1.0f;
            }
            else if ((phaseTri - temp)<(-1.0f))
            {
                direction=1.0f;
            }
           
            phaseTri += direction*temp;
            buffer[sample]=volume*phaseTri;
            phase+=phaseInc;
            if (phase>2*M_PI)
            {
                phase-=2*M_PI;
            }
        }
    };
    
    void setTriangle(){ phase=0; currentOsc=Osc::Triangle;}
    void setSine(){ phase=0; currentOsc=Osc::Sine;}
    void setSaw(){ phase=0; currentOsc=Osc::Saw;}
    void setSquare(){ phase=0; currentOsc=Osc::Square;}
    
    void setVolume(float newVolume){volume = newVolume};
    float getVolume(){return volume;};
    
    void setOsc(int newOsc)
    {
        phase=0;
        currentOsc = Osc(newOsc);
    }
    int getOsc()
    {
        return int(currentOsc);
    }
    void setFreq(float newfreq) { f0 = newfreq; phaseInc=2*M_PI*f0/fs;};
    float getFreq(){ return f0;};
private:


    float f0=440;
    float signFunc(float sample)
    {
        if(sample>0)
            sample=1;
        else if(sample<0)
            sample=-1;
            
        return sample;
    }
    
};

