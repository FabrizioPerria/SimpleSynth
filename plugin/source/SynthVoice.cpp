#include "SynthVoice.h"
#include "SynthSound.h"
#include "data/EnvelopeData.h"

SynthVoice::SynthVoice()
{
}

bool SynthVoice::canPlaySound(SynthesiserSound *sound)
{
	return isPrepared && dynamic_cast<SynthSound *>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
	juce::ignoreUnused(velocity);
	juce::ignoreUnused(sound);
	juce::ignoreUnused(currentPitchWheelPosition);
	ampEnvelope.noteOn();
	modEnvelope.noteOn();
	oscillator.setOscillatorFrequency(midiNoteNumber);
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	juce::ignoreUnused(velocity);
	ampEnvelope.noteOff();
	modEnvelope.noteOff();

	if (!allowTailOff || !ampEnvelope.isActive())
	{
		clearCurrentNote();
	}
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

void SynthVoice::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
	oscillator.prepareToPlay(spec);
	ampEnvelope.preparetoPlay(spec);
	filter.prepareToPlay(spec);
	modEnvelope.preparetoPlay(spec);

	isPrepared = true;
}

void SynthVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
	jassert(isPrepared);

	if (!isVoiceActive())
	{
		return;
	}

	voiceBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	modEnvelope.process(voiceBuffer);
	voiceBuffer.clear();

	juce::dsp::AudioBlock<float> audioBlock{voiceBuffer};
	oscillator.getNextAudioBlock(audioBlock);

	ampEnvelope.process(voiceBuffer);
	filter.process(voiceBuffer);

	for (auto channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
	{
		outputBuffer.addFrom(channel, startSample, voiceBuffer, channel, 0, numSamples);
		if (!ampEnvelope.isActive())
		{
			clearCurrentNote();
		}
	}
	modEnvelope.getNextSample();
}

void SynthVoice::updateOscillator(const OscillatorType oscillatorType, const float level, const float lfoFreq,
								  const float lfoDepth)
{
	oscillator.setOscillatorType(oscillatorType);
	oscillator.setOscillatorLevel(level);
	oscillator.setLFO(lfoFreq, lfoDepth);
}

void SynthVoice::updateAmpEnvelope(const float attack, const float decay, const float sustain, const float release)
{
	ampEnvelope.update(attack, decay, sustain, release);
}

void SynthVoice::updateModEnvelope(const float attack, const float decay, const float sustain, const float release)
{
	modEnvelope.update(attack, decay, sustain, release);
}

void SynthVoice::updateFilter(const FilterType filterType, const float freq, const float res)
{
	float modulator = modEnvelope.getNextSample();
	filter.setParameters(filterType, freq, res, modulator);
}
