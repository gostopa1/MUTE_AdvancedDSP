#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class z_mod
{
public:
    z_mod(){}
    ~z_mod(){}

    float fs=44100.0f;

    std::vector<float> tape;
    int tapeLen=0;
    int writeIndex=0;
    int readIndex=0;
    
    bool modOn=true;
    
    // Modulation parameters
    int modAmount=0; // Keeps track of the maximum modulation offset in samples
    double modValue=0.0; // Current modulation value between 0.0 and 1.0, which will be scaled to the modulation amount
    int modint=0; // Keeps track of the current modulation offset in samples
    
    // The modulation is based on a low-pass filtered random value that updates every randomInterval samples. The modCoeff controls the smoothing of the modulation, with values closer to 1.0 resulting in smoother modulation.
    double newRandom=0.0;
    double modCoeff=0.99999; // Smoothing coefficient for the modulation
    int randomcnt=0.0;
    int randomInterval=4410; // Update modulation every 100ms at 44.1kHz
    

    void setModOn(bool on)
    {
        modOn=on;
    }

    // Set delay in seconds (will be converted to samples using current sampleRate)
    void setDelaySamples(int delaySamples)
    {
        tape.resize(delaySamples, 0.0f);
        tapeLen = delaySamples;
        modAmount = 240;
        
        if (modAmount > tapeLen)
        {
            modAmount = tapeLen;
        }
    }

    void prepare(double sampleRate, int /*samplesPerBlock*/)
    {
        if (modOn)
        {
            srand((unsigned int)time(NULL));  // Seed the random number generator
        }
        fs = sampleRate;
    }

    double getRandom()
    {
        double r = (double)rand() / RAND_MAX;
        return r;
    }
    void process(float* buffer, int numSamples)
    {
        for (int i=0; i<numSamples; ++i)
        {
            if (modOn && randomcnt >= randomInterval)
            {
                newRandom = getRandom();
                randomcnt = 0;
            }
            randomcnt++;

            float temp = tape[writeIndex];

            if (modOn)
            {
                modValue = modValue * modCoeff + newRandom * (1.0 - modCoeff);
                modint = (int)(modValue * modAmount);
                readIndex = writeIndex + modint;
                if (readIndex >= tapeLen)
                {
                    readIndex -= tapeLen;
                }
                temp = tape[readIndex];
            }
            
            tape[writeIndex] = buffer[i];
            
            buffer[i]=temp;
            writeIndex=writeIndex+1;
            if (writeIndex>=tapeLen)
                writeIndex=0;
            
        }
    }
private:
   
};
