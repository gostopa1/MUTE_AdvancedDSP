/*
  ==============================================================================

    MuteDelay.h
    Created: 23 Mar 2021 11:30:33pm
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once
#pragma once
#include <vector>

class MuteDelay 
{
public:
    std::vector<float> tape;
    int tapeTotalLength=48000;
    int tapeLength=24000;
    int readHead=0;
    float wet=0.5;
    float feedback = 0.5;
    float clean_signal = 0.0f;
    int writeHead;
    
    void setLength(int newLength){tapeLength = newLength;};
    int getLength(){return tapeLength;};
    
    void setFeedback(float newFeedback){feedback = newFeedback;};
    float getFeedback(){return feedback;};
    
    void setWet(float newWet){ wet = newWet;};
    float getWet(){ return wet;};
    
    MuteDelay()
    {
        tape.resize(tapeTotalLength,0.0);
    };
    ~MuteDelay(){};
    void prepare(double sampleRate, int samplesPerBlock){};
    void process(float* buffer, int numSamples)
    {
        for (int i=0;i<numSamples;++i)
        {
            clean_signal = buffer[i];
            //tape[writeHead]=feedback*tape[writeHead]+(1-feedback)*buffer[i];
            //tape[writeHead]=feedback*tape[writeHead]+buffer[i];
            tape[writeHead]=feedback*tape[writeHead]+buffer[i];
            buffer[i] = wet * tape[writeHead] + (1-wet)*clean_signal;
            writeHead=(writeHead+1)%tapeLength;
        }
    };
    
private:
};
