#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include "utils/OscillatorType.h"
#include "utils/FilterType.h"

#define NUM_VOICES 3
//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
	: AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
						 .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
						 .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
						 ),
	  apvts(*this, nullptr, "PARAMETERS", createParams())
{
	synth.addSound(new SynthSound());
	for (auto voices = 0; voices < NUM_VOICES; voices++)
		synth.addVoice(new SynthVoice(envelope));
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
	return 1; // NB: some hosts don't cope very well if you tell them there are 0
			  // programs, so this should be at least 1, even if you're not really
			  // implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
	return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram(int index)
{
	juce::ignoreUnused(index);
}

const juce::String AudioPluginAudioProcessor::getProgramName(int index)
{
	juce::ignoreUnused(index);
	return {};
}

void AudioPluginAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
	juce::ignoreUnused(index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	synth.setCurrentPlaybackSampleRate(sampleRate);

	dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = ( uint32_t ) samplesPerBlock;
	spec.numChannels = ( uint32_t ) getTotalNumOutputChannels();

	for (auto i = 0; i < synth.getNumVoices(); ++i)
	{
		if (auto voice = dynamic_cast<SynthVoice *>(synth.getVoice(i)))
		{
			voice->prepareToPlay(spec);
		}
	}
	envelope.preparetoPlay(spec);
	filter.prepareToPlay(spec);
}

void AudioPluginAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
		layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

		// This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}

void AudioPluginAudioProcessor::setupEnvelope()
{
	auto attack = apvts.getRawParameterValue("ATTACK")->load();
	auto decay = apvts.getRawParameterValue("DECAY")->load();
	auto sustain = apvts.getRawParameterValue("SUSTAIN")->load();
	auto release = apvts.getRawParameterValue("RELEASE")->load();
	envelope.update(attack, decay, sustain, release);
}

void AudioPluginAudioProcessor::setupFilter()
{
	auto filterType = FilterType::fromInt(static_cast<int>(apvts.getRawParameterValue("FILTER_TYPE")->load()));
	auto filterCutoff = apvts.getRawParameterValue("FILTER_CUTOFF")->load();
	auto filterResonance = apvts.getRawParameterValue("FILTER_RESONANCE")->load();

	filter.setFilterType(filterType);
	filter.setParameters(filterCutoff, filterResonance);
}

void AudioPluginAudioProcessor::setupOscillator(SynthVoice *voice, const int voiceIndex)
{
	auto type = OscillatorType::fromInt(
		static_cast<int>(apvts.getRawParameterValue("OSC_WAVETYPE" + std::to_string(voiceIndex))->load()));
	auto level = apvts.getRawParameterValue("OSC_GAIN" + std::to_string(voiceIndex))->load();
	auto lfoFreq = apvts.getRawParameterValue("OSC_LFO_FREQ" + std::to_string(voiceIndex))->load();
	auto lfoDepth = apvts.getRawParameterValue("OSC_LFO_DEPTH" + std::to_string(voiceIndex))->load();
	voice->updateOscillator(type, level, lfoFreq, lfoDepth);
}

void AudioPluginAudioProcessor::setupOutputGain()
{
	auto gainValue = apvts.getRawParameterValue("OUTPUT_GAIN")->load();
	outputGain.setGainDecibels(gainValue);
}

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumOutputChannels = getTotalNumOutputChannels();
	auto totalNumInputChannels = getTotalNumInputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
	{
		buffer.clear(i, 0, buffer.getNumSamples());
	}

	for (auto i = 0; i < synth.getNumVoices(); ++i)
	{
		if (auto voice = dynamic_cast<SynthVoice *>(synth.getVoice(i)))
		{
			setupEnvelope();
			setupOscillator(voice, i);
			setupFilter();
			setupOutputGain();
		}
	}

	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	juce::dsp::AudioBlock<float> audioBlock{buffer};
	filter.process(audioBlock);
	envelope.process(buffer);
	outputGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor()
{
	return new AudioPluginAudioProcessorEditor(*this);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
	juce::ignoreUnused(destData);
}

void AudioPluginAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory
	// block, whose contents will have been created by the getStateInformation()
	// call.
	juce::ignoreUnused(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
	return new AudioPluginAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout AudioPluginAudioProcessor::createParams()
{
	juce::AudioProcessorValueTreeState::ParameterLayout paramLayout;

	setupOscillatorVoiceParameters(paramLayout);
	setupEnvelopeParameters(paramLayout);
	setupFilterParameters(paramLayout);
	setupOutputGainParameters(paramLayout);

	return paramLayout;
}

void AudioPluginAudioProcessor::setupOscillatorVoiceParameters(
	juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout)
{
	for (int voicesIndex = 0; voicesIndex < NUM_VOICES; voicesIndex++)
	{
		paramLayout.add(std::make_unique<juce::AudioParameterChoice>(
			ParameterID{"OSC_WAVETYPE" + std::to_string(voicesIndex), 1}, "Oscillator " + std::to_string(voicesIndex),
			OscillatorType::toStringArray(), 0));
		paramLayout.add(std::make_unique<juce::AudioParameterFloat>(
			ParameterID{"OSC_GAIN" + std::to_string(voicesIndex), 1}, "Gain " + std::to_string(voicesIndex),
			NormalisableRange<float>{-40.0f, 0.2f, 0.1f}, -10.0f));
		paramLayout.add(
			std::make_unique<juce::AudioParameterFloat>(ParameterID{"OSC_LFO_FREQ" + std::to_string(voicesIndex), 1},
														"LFO Frequency " + std::to_string(voicesIndex),
														NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.3f}, 5.0f));
		paramLayout.add(std::make_unique<juce::AudioParameterFloat>(
			ParameterID{"OSC_LFO_DEPTH" + std::to_string(voicesIndex), 1}, "LFO Depth " + std::to_string(voicesIndex),
			NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.3f}, 500.0f));
	}
}

void AudioPluginAudioProcessor::setupEnvelopeParameters(
	juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout)
{
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"ATTACK", 1}, "Attack",
																NormalisableRange<float>{0.1f, 1.0f}, 0.8f));
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"DECAY", 1}, "Decay",
																NormalisableRange<float>{0.1f, 1.0f}, 0.8f));
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"SUSTAIN", 1}, "Sustain",
																NormalisableRange<float>{0.1f, 1.0f}, 1.0f));
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"RELEASE", 1}, "Release",
																NormalisableRange<float>{0.1f, 3.0f}, 1.5f));
}

void AudioPluginAudioProcessor::setupFilterParameters(juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout)
{
	paramLayout.add(std::make_unique<juce::AudioParameterChoice>(ParameterID{"FILTER_TYPE", 1}, "Filter Type",
																 FilterType::toStringArray(), 0));
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"FILTER_CUTOFF", 1}, "Filter Cutoff",
																NormalisableRange<float>{20.0f, 20000.0f, 0.1f, 0.6f},
																200.0f));
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"FILTER_RESONANCE", 1}, "Filter Resonance",
																NormalisableRange<float>{1.0f, 10.0f, 0.1f}, 1.0f));
}

void AudioPluginAudioProcessor::setupOutputGainParameters(
	juce::AudioProcessorValueTreeState::ParameterLayout &paramLayout)
{
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"OUTPUT_GAIN", 1}, "Gain",
																NormalisableRange<float>{-40.0f, 0.2f, 0.1f}, -10.0f));
}

juce::AudioProcessorValueTreeState &AudioPluginAudioProcessor::getApvts()
{
	return apvts;
}
