#include <vector>
#include <cstddef>
#include <algorithm>

class ap1_mod
{
public:
    ap1_mod(){}
    ~ap1_mod(){}

    float fs = 48000.0f;

    // Modulation parameters
    int modAmount=0; // Keeps track of the maximum modulation offset in samples
    double modValue=0.0; // Current modulation value between 0.0 and 1.0, which will be scaled to the modulation amount
    int modint=0; // Keeps track of the current modulation offset in samples
    int readIndex=0;
    
    // The modulation is based on a low-pass filtered random value that updates every randomInterval samples. The modCoeff controls the smoothing of the modulation, with values closer to 1.0 resulting in smoother modulation.
    double newRandom=0.0;
    double modCoeff=0.99999; // Smoothing coefficient for the modulation
    int randomcnt=0.0;
    int randomInterval=4410; // Update modulation every 100ms at 44.1kHz

    bool modOn=true;

    void setModOn(bool on)
    {
        modOn=on;
    }

    void prepare(double sampleRate, int samplesPerBlock)
    {
        fs = sampleRate;
        // For a Schroeder allpass, the delay is typically set to a small prime number of samples.
        // Here we choose 347 samples as an example, which corresponds to about 7.2 ms at 48 kHz.
        const std::size_t delaySamples = 347;
        const float g = 0.7f; // feedback gain  
        setDelay(delaySamples);
        setGain(g);

        if (modOn)
        {
            srand((unsigned int)time(NULL));  // Seed the random number generator
        }
        modAmount = 240;

        reset();
    }

    void setModAmount(int amount)
    {        
        modAmount=amount;
    }

     double getRandom()
    {
        double r = (double)rand() / RAND_MAX;
        return r;
    }

    void setDelay(std::size_t delaySamples)
    {
        delay_ = std::max<std::size_t>(1, delaySamples);
        // We store x[n-M] and y[n-M] each in their own circular buffer.
        xbuf_.assign(delay_, 0.0f);
        ybuf_.assign(delay_, 0.0f);
        idx_ = 0;
    }

    void setGain(float g)
    {
        // keep strictly inside (-1, 1) for safety
        const float limit = 0.9999f;
        g_ = std::clamp(g, -limit, limit);
    }

    void reset()
    {
        std::fill(xbuf_.begin(), xbuf_.end(), 0.0f);
        std::fill(ybuf_.begin(), ybuf_.end(), 0.0f);
        idx_ = 0;
    }

    void process(float * buffer, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {

            if (modOn && randomcnt >= randomInterval)
            {
                newRandom = getRandom();
                randomcnt = 0;
            }
            randomcnt++;

            if (modOn)
            {
                modValue = modValue * modCoeff + newRandom * (1.0 - modCoeff);
                modint = (int)(modValue * modAmount);
                readIndex = idx_ + modint;
                if (readIndex >= delay_)
                {
                    readIndex -= delay_;
                }
                
            }
            else
            {
                readIndex = idx_;
            }

            float x = buffer[sample];
            const float x_del = xbuf_[readIndex]; // x[n-M]
            const float y_del = ybuf_[readIndex]; // y[n-M]

            const float y = (-g_ * x) + x_del + (g_ * y_del);

            xbuf_[idx_] = x;
            ybuf_[idx_] = y;

            idx_++;
            if (idx_ >= delay_) idx_ = 0;

            buffer[sample] = y;
        }
    }

    void process_delay_with_mod(float * buffer, float * modulator, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {

            if (modOn)
            {
                modValue = modulator[sample];
                modint = (int)(modValue * modAmount);
                readIndex = idx_ + modint;
                if (readIndex >= delay_)
                {
                    readIndex -= delay_;
                }
                
            }
            else
            {
                readIndex = idx_;
            }

            float x = buffer[sample];
            const float x_del = xbuf_[readIndex]; // x[n-M]
            const float y_del = ybuf_[readIndex]; // y[n-M]

            const float y = (-g_ * x) + x_del + (g_ * y_del);

            xbuf_[idx_] = x;
            ybuf_[idx_] = y;

            idx_++;
            if (idx_ >= delay_) idx_ = 0;

            buffer[sample] = y;
        }
    }

    void process_gain_with_mod(float * buffer, float * modulator, int numSamples)
    {
        for (int sample=0;sample<numSamples;++sample)
        {

            readIndex = idx_;

            float x = buffer[sample];
            const float x_del = xbuf_[readIndex]; // x[n-M]
            const float y_del = ybuf_[readIndex]; // y[n-M]
            
            const float fc = minFrequency_ + modulator[sample] * (maxFrequency_ - minFrequency_);

            // 1st-order allpass coefficient from target corner frequency
            const float t = std::tan(static_cast<float>(M_PI) * fc / fs);
            g_ = (1.0f - t) / (1.0f + t);

            const float y = (-g_ * x) + x_del + (g_ * y_del);
            // const float y = (-g_ * x) + x_del + (g_ * y_del);

            xbuf_[idx_] = x;
            ybuf_[idx_] = y;

            idx_++;
            if (idx_ >= delay_) idx_ = 0;

            buffer[sample] = y;
        }
    }
    void  setMinMaxFrequency(float minFreq, float maxFreq)
    {
        minFrequency_ = minFreq;
        maxFrequency_ = maxFreq;
    }
private:

    float maxFrequency_ = 3000.0f;
    float minFrequency_ = 300.0f;
    std::vector<float> xbuf_, ybuf_;
    std::size_t delay_ = 1;
    std::size_t idx_ = 0;
    float g_ = 0.5f;
};
