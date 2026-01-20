/*
  ==============================================================================

    MuteBandPass.h
    Created: 17 Mar 2021 12:26:57pm
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once
#define M_PI 3.14159265359


#include <JuceHeader.h>
class MuteLowPass
{
public:
    float fs = 48000;
    float f0 = 200;
    float constF0 = 200;
    float Q = 2;
    float gainDB=3;
    double w0,A,cosw0,sinw0,alpha=0;
    double b0,b1,b2,a0,a1,a2=0;
    
    double xt=0, xtm1=0, xtm2=0;
    double yt=0, ytm1=0, ytm2=0;
    MuteLowPass()
    {
        updateParameters();
    };
    
    void setFreq(float newf0){ constF0 = newf0; f0=newf0; updateParameters(); };
    float getFreq(){return f0; };
    
    void setQ(float newQ){ Q=newQ; updateParameters(); };
    float getQ(){return Q; };

    ~MuteLowPass(){};
    
    void updateParameters()
    {
        //A=pow(10.0,gainDB/40.0);
        A=sqrt(pow(10,gainDB/20.0));
        w0=2.0*M_PI*f0/fs;
        cosw0=cos(w0);
        sinw0=sin(w0);

        alpha=sinw0/(2.0*Q);
        
        b0=(1.0-cos(w0))/2.0;
        b1=(1.0-cos(w0));
        b2=(1.0-cos(w0))/2.0;
        
        a0=1+alpha;
        a1=-2*cosw0;
        a2=1-alpha;
        
        b2=b2/a0;
        b1=b1/a0;
        b0=b0/a0;

        a2=a2/a0;
        a1=a1/a0;
        a0=1.0; // a0/a0;
    };
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
        fs=sampleRate;
        updateParameters();
    };
    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            xtm2 = xtm1;
            xtm1 = xt;
            xt=buffer[sample];
            ytm2=ytm1;
            ytm1=yt;
            yt= (b0*xt) + (b1*xtm1) + (b2*xtm2) - (a1*ytm1) - (a2*ytm2);
            buffer[sample]=yt;
        }

        
    };
    void processWithMod(float * buffer, float * bufferMod, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {
            f0=constF0*pow(2,bufferMod[sample]/12);
            updateParameters();
            
            xtm2 = xtm1;
            xtm1 = xt;
            xt=buffer[sample];
            ytm2=ytm1;
            ytm1=yt;
            yt= (b0*xt) + (b1*xtm1) + (b2*xtm2) - (a1*ytm1) - (a2*ytm2);
            buffer[sample]=yt;
        }

        
    };
private:
    
};
