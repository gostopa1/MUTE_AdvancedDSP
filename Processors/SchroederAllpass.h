#include <vector>
#include <cstddef>
#include <algorithm>

class SchroederAllpass
{
public:
    SchroederAllpass() = default;

    void prepare(double sampleRate, int samplesPerBlock)
    {
        // For a Schroeder allpass, the delay is typically set to a small prime number of samples.
        // Here we choose 347 samples as an example, which corresponds to about 7.2 ms at 48 kHz.
        const std::size_t delaySamples = 347;
        const float g = 0.5f; // feedback gain  
        setDelay(delaySamples);
        setGain(g);
        reset();
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
            float x = buffer[sample];
            const float x_del = xbuf_[idx_]; // x[n-M]
            const float y_del = ybuf_[idx_]; // y[n-M]

            const float y = (-g_ * x) + x_del + (g_ * y_del);

            xbuf_[idx_] = x;
            ybuf_[idx_] = y;

            idx_++;
            if (idx_ >= delay_) idx_ = 0;

            buffer[sample] = y;
        }
    }

private:
    std::vector<float> xbuf_, ybuf_;
    std::size_t delay_ = 1;
    std::size_t idx_ = 0;
    float g_ = 0.5f;
};
