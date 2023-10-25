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
	osc.setFrequency(static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)));
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

	osc.prepare(spec);

	gain.setGainLinear(0.01f);
	gain.prepare(spec);

	envelope.setSampleRate(sampleRate);

	envelopeParameters.attack = 0.8f;
	envelopeParameters.decay = 0.8f;
	envelopeParameters.sustain = 1.0f;
	envelopeParameters.release = 1.5f;

	envelope.setParameters(envelopeParameters);

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
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
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
