# SimpleSynth
Simple polyphonic synth **inspired** by [TAP's Youtube Synth series](https://www.youtube.com/playlist?list=PLLgJJsrdwhPwJimt5vtHtNmu63OucmPck). 
It provides:
 - 3 voices, each containing an oscillator and an amplitude modulator. Oscillators can play:
   - Sine wave
   - square wave
   - sawtooth wave
   - triangle wave
 - a common filter that can be set as:
   - high pass
   - low pass
   - bandpass
 - a common envelope module

This is developed for educational purposes:
 - learn JUCE programming
 - learn CMake integration with JUCE
 - learn to integrate unit test and diagnostic tooling with JUCE
 - have a sandbox where to run quick experiments while working on other projects

This is developed using OSX Sonoma and i won't be building/testing in any other platform unless my sandboxing requires it.

## Getting started
This repository is built using cmake. You can run 
```
./doit.sh
```
to build the plugin and run your unit tests. The plugin will be generated and copied in the system plugins location.


