#pragma once

#pragma once

#include <JuceHeader.h>
class MuteWaveshaper
{
public:
    float curve=50;
    float A, B, C, D = 0.0;
    
    MuteWaveshaper()
    {
        setABCD();
    };
    ~MuteWaveshaper(){};

    void setABCD()
    {
        A = 1 + (curve + 50.0)/100.0;
        B = -curve / 50.0;
        C = (curve - 50.0)/100.0;
        D = (1.0/16.0) - curve/400.0 + curve*curve/(40000.0);
    };
    void setCurve(float newCurve){
        curve = newCurve;
        setABCD();
    };
    float getCurve(){return curve;};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
    };
    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            float x = buffer[sample];
            float output = A*x+B*x*x+C*x * x * x + D * (x*x - 2*x*x*x + x*x*x*x);
            buffer[sample] = output;
        } 
    };
private:
    
};
