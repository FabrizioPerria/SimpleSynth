#include "SynthVoice.h"
#include "SynthSound.h"

bool SynthVoice::canPlaySound(SynthesiserSound *sound)
{
	return isPrepared && dynamic_cast<SynthSound *>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
{
	juce::ignoreUnused(velocity);
	juce::ignoreUnused(sound);
	juce::ignoreUnused(currentPitchWheelPosition);
	envelope.noteOn();
	oscillator.setOscillatorFrequency(midiNoteNumber);
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	juce::ignoreUnused(velocity);
	juce::ignoreUnused(allowTailOff);
	envelope.noteOff();

	if (!allowTailOff || !envelope.isActive())
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

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels)
{
	dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = ( uint32_t ) samplesPerBlock;
	spec.numChannels = ( uint32_t ) numOutputChannels;

	oscillator.prepareToPlay(spec);
	envelope.preparetoPlay(spec);

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
	voiceBuffer.clear();

	juce::dsp::AudioBlock<float> audioBlock{voiceBuffer};
	oscillator.getNextAudioBlock(audioBlock);
	envelope.applyEnvelopeToBuffer(voiceBuffer, 0, voiceBuffer.getNumSamples());

	for (auto channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
	{
		outputBuffer.addFrom(channel, startSample, voiceBuffer, channel, 0, numSamples);
		if (!envelope.isActive())
		{
			clearCurrentNote();
		}
	}
}

void SynthVoice::updateEnvelope(const float attack, const float decay, const float sustain, const float release)
{
	envelope.update(attack, decay, sustain, release);
}

void SynthVoice::updateOscillator(const OscillatorType type, const float level, const float lfoFreq,
								  const float lfoDepth)
{
	oscillator.setOscillatorType(type);
	oscillator.setOscillatorLevel(level);
	oscillator.setLFO(lfoFreq, lfoDepth);
}
