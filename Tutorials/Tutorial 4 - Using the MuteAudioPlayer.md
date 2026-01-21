This tutorial covers the process of adding a MuteAudioPlayer object to your project. This is handy for testing purposes as it will be playing repeatedly the wave file you set it to play. If the wave file is not found, then it will only output silence. 

This tutorial assumes you have started your own effect, based on the the tutorial “[How to start your own project and add processors](Tutorial%203%20-%20How%20to%20start%20your%20own%20project%20and%20add%20processors.md)”

Add the processors to your JUCE project

![Image1](./images/tutorial4_image1.png)

 and include it in your effect:

![Image2](./images/tutorial4_image2.png)

Make a new object of the class

![Image3](./images/tutorial4_image3.png)

Then in the `prepare` function we need to prepare the object and also set the audio file to be used using the setAudioFile function:

![Image4](./images/tutorial4_image4.png)

WARNING \#1: Use the full path of the file so that the plugin always detects correctly the wave file. If it is not found, the processor will output silence\!

WARNING \#2: Don’t use the setAudioFile in the process function\! It might try to process the file before loading it. This may cause unexpected behavior and even crash your plugin.

WARNING \#3: If the wave file has more than one channel, it will only use the first (Left) channel

Then in the process function of your effect, use the process function of the object:  
![Image5](./images/tutorial4_image5.png)

Most probably you want to do that before any other processor so that you evaluate the whole chain based on this file.  
The audio file should now play repeatedly.
