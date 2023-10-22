#pragma once

#include <JuceHeader.h>
#include <SynthSound.h>

class SynthVoice : public juce::SynthesiserVoice
{
  public:
	bool canPlaySound (SynthesiserSound *sound) override;
	void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound,
					int currentPitchWheelPosition) override;
	void stopNote (float velocity, bool allowTailOff) override;
	void pitchWheelMoved (int newPitchWheelValue) override;
	void controllerMoved (int controllerNumber, int newControllerValue) override;
	void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

  private:
	/* juce::dsp::Oscillator<float> osc{[](float x) { return std::sin(x); }}; */
	/* juce::dsp::Oscillator<float> osc{[](float x) { return x < 0.0f ? -1.0f : 1.0f; }}; */
	juce::dsp::Oscillator<float> osc{[] (float x) { return x / juce::MathConstants<float>::pi; }};
};