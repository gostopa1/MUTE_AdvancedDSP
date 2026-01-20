
/*
Compressor implementation based on Joshua Reiss material:
http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Reiss-Tutorialondynamicrangecompression.pdf

*/
#pragma once
#include <JuceHeader.h>
class  MuteComp{
public:
    
    float fs =48000;
    float y_T_prev=0;
    
    float  y_dW, x_T, slope, y_dB;
    float y_L, x_dB, x_G, overshoot, y_G, y_T, c_dB, gain;
    MuteComp()
    {
        alphaAtt = exp(-1 / (tauAttack * fs));
        alphaRel = exp(-1 / (tauRelease * fs));
    };
    
    ~MuteComp(){};
    
    void prepare(double sampleRate, int samplesPerBlock)
    {
        fs=sampleRate;
    };
    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {           // LEVEL DETECTION
            y_L = abs(buffer[sample]);
            
            //DECIBEL CONVERSION
            x_dB= y_L;
            y_dB = 20*log10(x_dB+0.0001);
            x_G=y_dB;
            //GAIN COMPUTER
            slope = (1 / R) - 1;
            overshoot = x_G - T;
            
            //KNEE
            if (overshoot <= (-W/2))
            {
                y_G = x_G;
            }
            else if ((overshoot > (-W/2)) && (overshoot < (W/2)))
            {
                y_G = x_G + slope * pow((overshoot + W / 2), 2)/ (2*W) ;
            }
            else if (overshoot >= (W/2))
            {
                y_G = x_G+slope * overshoot;
            }
            
            x_T= y_G - x_G;
            if (x_T > y_T_prev)
            {
                y_T= alphaAtt * y_T_prev + (1-alphaAtt)*x_T;
            }
            else
            {
                y_T= alphaRel * y_T_prev + (1-alphaRel)*x_T;
            }
            y_T_prev=y_T;
            
            c_dB = M-y_T; //CONTROL VECTOR, WITH MAKE‐UP GAIN
            gain = pow(10.0,(c_dB/20.0)); //CONVERT TO LINEAR
            
            buffer[sample] = buffer[sample] * gain; //GAIN STAGE
        }
    }
    void setAttack(float newAttack){tauAttack = newAttack; alphaAtt = exp(-1 / (tauAttack * fs));}
    float getAttack(){return tauAttack;}
    
    void setRelease(float newRelease){tauRelease = newRelease; alphaRel = exp(-1 / (tauRelease * fs));}
    float getRelease(){return tauRelease;};
    
    void setKneeWidth(float newW){W=newW;}
    float getKneeWidth(){return W;};
    
    void setThreshold(float newThreshold){T = newThreshold;};
    float getThreshold(){return T;};
    
    void setRatio(float newRatio){R = newRatio;};
    float getRatio(){return R;};
    
    void setMakeupgain(float newMakeupGain){M = newMakeupGain;};
    float getMakeupGain(){return M;};
private:

    float R=1.0f/10.0; // RATIO
    float T=-10; // THRESHOLD
    float W=6; // WIDTH OF KNEE
    float M=0; // Make up gain
    float tauAttack=0.01; // Attack in seconds
    float tauRelease=0.1; // Release in seconds
    float alphaAtt = 0;
    float alphaRel = 0;
    
};

