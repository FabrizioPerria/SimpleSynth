#pragma once

#include <JuceHeader.h>
#include <SynthSound.h>
#include "data/FilterData.h"
#include "data/OscillatorData.h"
#include "utils/OscillatorType.h"
#include "data/EnvelopeData.h"

class SynthVoice : public juce::SynthesiserVoice
{
  public:
	SynthVoice();
	bool canPlaySound(SynthesiserSound *sound) override;
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void prepareToPlay(juce::dsp::ProcessSpec &spec);
	void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
	void updateOscillator(const OscillatorType type, const float level, const float lfoFreq, const float lfoDepth);
	void updateAmpEnvelope(const float attack, const float decay, const float sustain, const float release);
	void updateFilter(const FilterType filterType, const float freq, const float res);
	void updateModEnvelope(const float attack, const float decay, const float sustain, const float release);

  private:
	OscillatorData oscillator;
	EnvelopeData ampEnvelope;
	FilterData filter;
	EnvelopeData modEnvelope;
	juce::AudioBuffer<float> voiceBuffer;

	bool isPrepared{false};
};
