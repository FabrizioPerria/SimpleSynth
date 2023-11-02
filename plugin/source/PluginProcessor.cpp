#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include "utils/OscillatorType.h"

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
	synth.addVoice(new SynthVoice());
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
	for (auto i = 0; i < synth.getNumVoices(); ++i)
	{
		if (auto voice = dynamic_cast<SynthVoice *>(synth.getVoice(i)))
		{
			voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
		}
	}
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

void AudioPluginAudioProcessor::setupEnvelope(SynthVoice *voice)
{
	auto attack = apvts.getRawParameterValue("ATTACK")->load();
	auto decay = apvts.getRawParameterValue("DECAY")->load();
	auto sustain = apvts.getRawParameterValue("SUSTAIN")->load();
	auto release = apvts.getRawParameterValue("RELEASE")->load();
	voice->updateEnvelope(attack, decay, sustain, release);
}

void AudioPluginAudioProcessor::setupOscillator(SynthVoice *voice)
{
	auto type = OscillatorType::fromInt(static_cast<int>(apvts.getRawParameterValue("OSC_WAVETYPE")->load()));
	auto level = apvts.getRawParameterValue("OSC_GAIN")->load();
	voice->updateOscillator(type, level);
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
			setupEnvelope(voice);
			setupOscillator(voice);
			setupOutputGain();
		}
	}

	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	juce::dsp::AudioBlock<float> audioBlock{buffer};
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

	paramLayout.add(std::make_unique<juce::AudioParameterChoice>(ParameterID{"OSC_WAVETYPE", 1}, "Oscillator",
																 OscillatorType::toStringArray(), 2));
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"OSC_GAIN", 1}, "Gain",
																NormalisableRange<float>{-40.0f, 0.2f, 0.1f}, -10.0f));

	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"ATTACK", 1}, "Attack",
																NormalisableRange<float>{0.1f, 1.0f}, 0.8f));
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"DECAY", 1}, "Decay",
																NormalisableRange<float>{0.1f, 1.0f}, 0.8f));
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"SUSTAIN", 1}, "Sustain",
																NormalisableRange<float>{0.1f, 1.0f}, 1.0f));
	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"RELEASE", 1}, "Release",
																NormalisableRange<float>{0.1f, 3.0f}, 1.5f));

	paramLayout.add(std::make_unique<juce::AudioParameterFloat>(ParameterID{"OUTPUT_GAIN", 1}, "Gain",
																NormalisableRange<float>{-40.0f, 0.2f, 0.1f}, -10.0f));

	return paramLayout;
}

juce::AudioProcessorValueTreeState &AudioPluginAudioProcessor::getApvts()
{
	return apvts;
}
