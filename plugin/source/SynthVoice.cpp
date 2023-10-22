#include "SynthVoice.h"
#include "SynthSound.h"

bool SynthVoice::canPlaySound(SynthesiserSound *sound)
{
	return dynamic_cast<SynthSound *>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
	juce::ignoreUnused(midiNoteNumber);
	juce::ignoreUnused(velocity);
	juce::ignoreUnused(sound);
	juce::ignoreUnused(currentPitchWheelPosition);
}
void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	juce::ignoreUnused(velocity);
	juce::ignoreUnused(allowTailOff);
}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
	juce::ignoreUnused(newPitchWheelValue);
}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
	juce::ignoreUnused(controllerNumber);
	juce::ignoreUnused(newControllerValue);
}
void SynthVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
	juce::ignoreUnused(startSample);
	juce::ignoreUnused(numSamples);
	juce::dsp::AudioBlock<float> audioBlock{outputBuffer};
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}
