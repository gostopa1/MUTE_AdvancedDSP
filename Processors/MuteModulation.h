/*
  ==============================================================================

    MuteModulation.h
    Created: 24 Mar 2021 12:30:52am
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class MuteModulation
{
public:
    std::vector<float> tape;
    
    int tapeTotalLength=96000;
    int tapeLength=24000;

    int readHead=0;
    float wet=0.0;
    int writeHead=0;

    float fs=48000;
    MuteModulation()
    {
        tape.resize(tapeTotalLength,0.0);
    };
    
    void resizeTape(int newTapeLength)
    {
        tapeLength = newTapeLength;
    }
    ~MuteModulation(){};
    void prepare(double sampleRate, int samplesPerBlock)
    {
        fs = sampleRate;
    };
    void process(float* buffer, float *modulator,  int numSamples)
    {
        for (int i=0;i<numSamples;++i)
        {
            tape[writeHead] = buffer[i];
            
            // Modulator takes values from 0 to 1
            // The modulatedPos should take values from 0 to tapeLength-1
            float modulatedPos=modulator[i]*float(tapeLength-1);
            
            // To use the ring buffer, needs the "-1" to allow space for the linear interpolation
            double readHeadf = fmod(writeHead - modulatedPos+tapeLength, tapeLength);
            
            readHead = int(readHeadf);
            double remainder = readHeadf - float(readHead);
            
            int readhead_p1 = (readHead+1+tapeLength)%tapeLength;
            buffer[i]=remainder*tape[readhead_p1]+(1-remainder)*tape[readHead];
            
            writeHead++;
            if (writeHead >= tapeLength)
            {
                writeHead = 0;
            }
        }
    };
    
private:
    
};
