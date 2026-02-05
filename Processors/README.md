### List of processors

* `MuteSine:` sine wave generator  
  * `setFreq(float newFreq):` set new frequency  
  * `setPhase(float newFreq):` set new phase  
* `MuteCosine:` cosine wave generator  
  * `setFreq(float newFreq):` set new frequency  
  * `setPhase(float newFreq):` set new phase  
* `MuteOsc`: general oscillator supporting sine, square, sawtooth and triangle waveforms. All waveforms produce a waveform in the range of \-1 to \+1  
  * `setFreq(float newFreq):` set new frequency in Hz, default is 440  
  * `setVolume(float newVolume)`: choose new volume value, default is 1.0  
  * `setOsc(int newOsc)`: sets an oscillator based on an integer, to implement with a slider. 0 is sine, 1 is square, 2 is sawtooth and 3 is triangle  
  * `setSine()`: choose the sine oscillator  
  * `setSquare()`: choose the square wave oscillator  
  * `setSaw()`: choose the sawtooth oscillator  
  * `setTriangle()`: choose the triangle wave oscillator  
* `MuteRandomSignal:` white noise generator  
* `MuteTanh:` Distortion processors using a hyperbolic tangent (tanh)  
  * `setGain(float newGain):` set input gain (amount of distortion)  
  * `setVolume(float newVolume):` set output gain (output Volume)  
  * `setBias(float newBias):` set Bias value (for asymmetric clipping)  
* `MuteEnvelope`: Processor to extract the envelope of a signal, for compression or other effects  
  * `setAttack(float newAttack)`: set new attack value for the envelope calculation  
  * `setRelease(float newRelease)`: set new release value for the envelope calculation  
* `MuteCubicSoftClipper:` A cubic soft clipper function found [here](https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html)  
  * `setGain(float newGain):` set input gain (amount of distortion)  
  * `setVolume(float newVolume):` set output gain (output Volume)  
  * `setBias(float newBias):` set Bias value (for asymmetric clipping)  
* `MuteComp:` Basic compressor based on [this](http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Reiss-Tutorialondynamicrangecompression.pdf)  
  * `setThreshold(float newThreshold):` set Threshold parameter in dBs  
  * `setAttack(float newAttack)`: set attack time in seconds  
  * `setRelease(float newRelease):` set release time in seconds  
  * `setRatio(float newRatio):` set compression ratio  
  * `setKneeWidth(float newKneeWidth):` set knee width for the transition area  
  * `setMakeupGain(float newMakeupGain):` set amount of dBs to add in the end to compensate for lowered energy  
* `MuteGain`: Just multiplying the signal with a constant. Use a number lower than 1 for attenuation and larger than 1 to boost volume. Useful for distortion effects, volume adjustment and general scaling  
  * `setGain(float newGain)`: Setting a new gain. Default value \= 0.5   
* `MuteAdd`: Add a constant value to the signal. May cause artifacts if used on audio, yet it is useful when you need to add an offset, for example scale a signal that ranges from \-1 to \+1, to 0 to 1\.  
  * `setAmount(float newAmount)`: Setting a new gain. Default value \= 0.5   
* `MuteDelay`: A simple delay that records and plays back from a “tape”. A “feedback” parameter controls how much the “tape” is renewed by the current input, “wet” controls how much of the delay will pass through, and “length” controls the length of the “tape”.  
  * `setLength(int newLength)`: set the new Length of the tape, corresponding to the number of samples in the delay. This divided by the sample rate, gives the delay in seconds  
  * `setFeedback(float newFeedback)`: set new feedback parameter which controls how much the tape will be preserved at each loop of the tape  
  * `setWet(float newWet)`: controls how much of the delayed signal will be fed to the output. When set to 0, the signal is dry, which means that only the clean signal is fed to the output. Wet at 1, allows only the delayed signal to pass through.  
* `MuteWaveshaper:` Waveshaper function based on [this](https://gearspace.com/board/showpost.php?p=15125058&postcount=118)   
  * `setCurve(float newCurve):` set a new curve parameter  
* `MuteAudioPlayer:` simple processor to play back a wave file repeatedly  
  * `setAudioFile(juce::String filename)`: set the absolute path of the filename you want to play. `Do that in the prepare function (i.e. before the processor runs)`  
  * for example:  
    * MuteAudioPlayer1.setAudioFile("/Users/tanilas/Projects/DSP Applications/JUCE Projects/TestEffect/Source/piano\_melody.wav")  
  * check [this](../Tutorials/Tutorial%204%20-%20Using%20the%20MuteAudioPlayer.md) tutorial for more details

Filters:

* `MuteBandPass`: bandpass filter  
  * setFreq(float newf0): set new center frequency for the filter  
  * setQ(float newQ): set new Q value for the filter  
* `MuteLowPass`: Low pass filter implementation  
  * `setFreq(float newf0)`: set new cutoff frequency for the filter  
  * `setQ(float newQ):` set new Q value for the filter  
* `MuteHighPass`: High pass filter implementation  
  * `setFreq(float newf0)`: set new cutoff frequency for the filter  
  * `setQ(float newQ):` set new Q value for the filter  
* `MutePeak:` Peaking filter implementation  
  * `setFreq(float newf0)`: set new center frequency for the filter  
  * `setQ(float newQ):` set new Q value for the filter  
  * `setGainDB(float newGainDB):` set amount of dBs to boost (positive number) or attenuate (negative number)  
* `MuteDCFilter`: A DC blocking filter (first order high-pass with very low cutoff frequency). It has no parameters.
* `IRConv`: A convolution processor to convolve with a monophonic impulse response.
  * `loadIRFromWavFile(const juce::String& fullPath)`: set the path to the wave file for convolution. Pass a path as text, e.g. `/Users/myUser/myIRS/IR1.wav`  
* `SchroederAllpass`: An schroeder based all pass filter [see here](https://ccrma.stanford.edu/~jos/pasp/Schroeder_Allpass_Sections.html).
  * `setDelay(int M)`: sets the delay in samples
  * `setGain`: sets the feedback gain for the all pass. Should be between -1 and 1 otherwise, it can cause weird behavior


`Special classes:`

* `MuteSplit:` making a copy of the signal for parallel signal processing  
  * To use you need to get access to the copied buffer by adding the:  
    * `float * buffer2 = MuteSplit1.getPtr();`  
  * An example is here:  
  * ![Image](../Tutorials/images/processors_image1.png)

`Complex processors (processors that use other existing processors)`

* `MuteSSB:` A frequency-shifter based on ring modulation introduced by Weaver in 1956, see Figure 13.2 in [this link](http://www.cim.mcgill.ca/~clark/nordmodularbook/nm_spectrum_shift.html)  
  * Functions  
    * `setF1(float newF1):` Sets the frequency of the first sine wave in the ring modulator  
    * `setF2(float newF2):` Sets the frequency of the second sine wave in the ring modulator. Typically higher frequency than F1  
  * Uses the following processors (have to include them in the project):  
    * MuteSine  
    * MuteCosine  
    * MuteLowPass  
    * MuteSplit  
    * MuteMix  
    * MuteMulitply

**Processors that use two signals**

* These processors get two buffers as input and the result is stored in the first buffer. For example:  
  * `MuteAdd.processs(buffer1, buffer2, numSamples)` will add the samples of buffer1 and buffer2 and the result is stored in buffer1.  
* `MuteMultiply:` Multiplying two signals. Useful for implementing tremolo, ring modulation, compressors etc.  
* `MuteMix:` Adding two signals, that is, mixing them together. They are equally summed, so you may want to use MuteGain to adjust the volume of each signal.  
* `MuteModulation`: Modulate the first signal using the second buffer as a modulator. Useful for tape-like modulation effects.  
  * `setTapeLength(int newTapeLength)`: Setting a new modulation length that the head will be moving ahead. Currently the maximum tape size is set to 96000, but this can be changed for  
    * The modulator signal should range between 0 and 1, hence modulating with normal audio might cause artifact, For some audio that ranges from `-1` to `+1`, you will need to use the MuteAdd to add 1 to the signal and then scale it using MuteGain, setting the gain to 0.5. Then the range of the signal will be between 0 and 1, modulating “the tape head” position  
    * The process function looks like this:  
    * ​​	`void process(float* buffer, float *modulator,  int numSamples)`