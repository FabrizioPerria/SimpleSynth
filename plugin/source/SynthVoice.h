#pragma once

#include <JuceHeader.h>
#include <SynthSound.h>
#include "data/EnvelopeData.h"
#include "data/OscillatorData.h"
#include "utils/OscillatorType.h"

class SynthVoice : public juce::SynthesiserVoice
{
  public:
	bool canPlaySound(SynthesiserSound *sound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels);
	void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
	void updateEnvelope(const float attack, const float decay, const float sustain, const float release);
	void updateOscillator(const OscillatorType type, const float level, const float lfoFreq, const float lfoDepth);

  private:
	EnvelopeData envelope;
	OscillatorData oscillator;

	juce::AudioBuffer<float> voiceBuffer;

	bool isPrepared{false};
};
