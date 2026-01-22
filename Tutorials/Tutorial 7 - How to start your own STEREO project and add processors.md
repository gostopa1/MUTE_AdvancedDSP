**THIS TUTORIAL IS VERY SIMILAR TO THE ONE FOR MAKING A MONO EFFECT THAT CAN BE FOUND [HERE](./Tutorial%203%20-%20How%20to%20start%20your%20own%20project%20and%20add%20processors.md)\!**

In this tutorial we go through the process of making a new project with a **stereo** effect class where we will start adding processors that will be doing whatever we need for our plugin.

Make a new project by following the instructions in the tutorial [​”Setting up a new JUCE project”](./Tutorial%201%20-%20Setting%20up%20a%20new%20JUCE%20project.md). In this example I made a project called `TestEffect`.

Once your project is ready you are ready to make a new class that will be handling all the processors of your effect. 

Right click on the Source folder and select “Add New CPP & Header File…”  
![Image](./images/tutorial7_image1.png)

Then you will be prompted to choose a name for the new class. I use TestEffect as a name for this new class, which is the same name as the Project. IT DOESN’T HAVE TO BE THE SAME.

Then the .h and .cpp files will be created and appear in the project:  
![Image](./images/tutorial7_image2.png)

Then we need to set up the new class before we can use it for processing in the `PluginProcessor`. We will edit the TestEffect.h so that it looks like this:

---
```
#pragma once  
#include <JuceHeader.h>

class TestEffect  
{  
    public:  
    TestEffect(){};  
    ~TestEffect(){};  
      
    void prepare(double sampleRate, int samplesPerBlock)  
    {  
    };  
    void processStereo(float * bufferL, float * bufferR, int numSamples)  
    {  
    };  
    private:  
      
};  
```
---

Keep in mind that the name of the constructor and the destructor should be the same as the class. But if you have chosen a different name, you have to adjust them accordingly

### Adding the processor functionality in the plugin

Now it’s time to add the effect to our plugin, although the plugin does nothing yet.  
Let’s add it to the plugin and in the next section we will start doing some processing.

First we need to include the header

![Image](./images/tutorial7_image3.png)

 and then add a new object of this class in the `PluginProcessor` header (`.h`):

![Image](./images/tutorial7_image4.png)

Now we switch to the PluginProcessor.cpp and prepare the effect in the prepareToPlay function so that the function looks like this:
```
void TestEffectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)  
{  
    TestEffect1.prepare(sampleRate, samplesPerBlock);  
    // Use this method as the place to do any pre-playback  
    // initialisation that you need..  
}
```

then process the plugin in the processBlock function, so that the function looks like this:
```
void TestEffectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)  
{  
    juce::ScopedNoDenormals noDenormals;  
    auto totalNumInputChannels  = getTotalNumInputChannels();  
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)  
        buffer.clear (i, 0, buffer.getNumSamples());

    int numSamples = buffer.getNumSamples(); // THIS  
      
    auto* channelDataL = buffer.getWritePointer (0);  
    auto* channelDataR = buffer.getWritePointer (1);  
    TestEffect1.processStereo(channelDataL, channelDataR, numSamples);  
}
```
---

### Adding processor to the effect

Now if our plugin builds fine (as it should) we will start adding some processors. We will make a plugin that generates a sine wave on the left channel and white noise on the right channel

Download the `MuteSine` and `MuteRandomSignal1 processors from [the uploaded processors](../Processors/), copy them to the Source folder of your plugin and add them to the project. Then the project will look like this:

![Image](./images/tutorial7_image5.png)

### Adding the processors to your effect

Now you need to add objects to your effect. The following changes are only in the header (`.h` file) of your effect (`TestEffect.h` in this example). You don’t need to change anything anymore in any other file.

First you need to include the processors you will use:  
![Image](./images/tutorial7_image6.png)

Then you need to declare one object per processors

![Image](./images/tutorial7_image7.png)

In the prepare function you will prepare all of your objects:

![Image](./images/tutorial7_image8.png)

Then on the process function you decide what you will do with the processing. In this example we just generate a sine wave on the left channel using MuteSine1 applied to the ChannelDataL and white noise using MuteRandomSignal1 applied to ChannelDataR.

![Image](./images/tutorial7_image9.png)

Now the project should build and run fine