#include <vector>
#include <algorithm>
#include <cmath>

class z
{
public:
    z(){}
    ~z(){}

    std::vector<float> tape;
    int tapeLen=0;
    int writeIndex=0;
    int readIndex=0;

    float fs=44100.0f;
    // Set delay in seconds (will be converted to samples using current sampleRate)
    void setDelaySamples(int delaySamples)
    {
        tape.resize(delaySamples, 0.0f);
        tapeLen = delaySamples;
    }

    void prepare(double sampleRate, int /*samplesPerBlock*/)
    {
        fs = sampleRate;
    }

    void process(float* buffer, int numSamples)
    {
        for (int i=0; i<numSamples; ++i)
        {
            float temp = tape[writeIndex];
            tape[writeIndex] = buffer[i];
            buffer[i]=temp;
            writeIndex=writeIndex+1;
            if (writeIndex>=tapeLen)
                writeIndex=0;
            
        }
    }
private:
   
};
