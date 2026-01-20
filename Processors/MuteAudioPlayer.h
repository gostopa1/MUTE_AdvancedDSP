/*
  ==============================================================================

    MuteAudioPlayer.h
    Created: 23 Mar 2021 11:17:51pm
    Author:  Athanasios Gotsopoulos

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;
class MuteAudioPlayer
{
public:
    AudioSampleBuffer fileBuffer; // This
    File SoundFile; // This is keeps the file that we load for playing
    AudioFormatManager formatManager; // This handles the different types of files that we might want to load (e.g. wav, ogg, mp3)
    
    int bufferLength;
    int position = 0;
    float * sampleBuffer;
    juce::int64 sampleLength = 0;
    int cnt = 0;
    bool readSuccess = false;
    MuteAudioPlayer()
    {
        readSuccess = false;
        
        
    };
    ~MuteAudioPlayer(){};
    void prepare(double sampleRate, int samplesPerBlock){};
    void process(float * buffer, int numSamples)
    {
        if (readSuccess==true)
        {
            for (int sample=0; sample<numSamples;++sample)
            {
                buffer[sample]=sampleBuffer[cnt];
                cnt++; // cnt = cnt + 1;
                if (cnt > bufferLength)
                {
                    cnt=0;
                }
            }
        }
        else
        {
        // Fill it with zeros (silence)
            for (int sample=0; sample<numSamples;++sample)
            {
                buffer[sample]=0;
            }
        }
        
    };
    
    void setAudioFile(juce::String filename)
    {
        // Juce related code to read an audio file as a buffer
        //auto file = File("../../../Source/drums.wav"); // Set the file to load
        //auto file = File("/Users/tanilas/Projects/DSP Applications/JUCE Projects/TestEffect/Source/drums.wav");
        //auto file = File("/Users/tanilas/Projects/DSP Applications/JUCE Projects/TestEffect/Source/piano_melody.wav");
        auto file = File(filename);
        formatManager.registerBasicFormats() ; // Tell to JUCE to look for all basic audio file formats
        
        // Make a reader that will load the audio file
        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor (file));

        if (reader.get() != nullptr)
        {
            bufferLength=reader->lengthInSamples;
            auto duration = (float) reader->lengthInSamples / reader->sampleRate;
            fileBuffer.setSize ((int) reader->numChannels, (int) reader->lengthInSamples);
            reader->read (&fileBuffer,0, (int) reader->lengthInSamples, 0, true, true);
            position = 0;
            sampleBuffer = fileBuffer.getWritePointer(0);
            readSuccess = true;
        }
    };
    
private:
    
};
