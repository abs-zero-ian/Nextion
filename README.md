# Nextion
A Modified Nextion Library for ESP8266 with Software Serial support added so as to be compatible with the IOTAppStory framework.
- Nextion serial connection is by softwareserial (the version in the v2.4.2 esp8266 Arduino core)
- Debug serial connection is using the hardware port (i.e. via USB on boards that have it)
- Change Software Serial pins in line 18 of NexHardware.cpp
- Examples added to demonstrate how to use some of the controls - the HMI files are there to allow compilation of the matching TFT files using Nextion Editor
