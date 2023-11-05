#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
	: AudioProcessorEditor(&p), processorRef(p),
	  oscillator0(p.getApvts(), "OSC_WAVETYPE0", "OSC_GAIN0", "OSC_LFO_FREQ0", "OSC_LFO_DEPTH0", "Oscillator 0"),
	  oscillator1(p.getApvts(), "OSC_WAVETYPE1", "OSC_GAIN1", "OSC_LFO_FREQ1", "OSC_LFO_DEPTH1", "Oscillator 1"),
	  oscillator2(p.getApvts(), "OSC_WAVETYPE2", "OSC_GAIN2", "OSC_LFO_FREQ2", "OSC_LFO_DEPTH2", "Oscillator 2"),
	  envelopeComponent(p.getApvts(), "ATTACK", "DECAY", "SUSTAIN", "RELEASE", "Envelope"),
	  filterComponent(p.getApvts(), "FILTER_TYPE", "FILTER_CUTOFF", "FILTER_RESONANCE", "Filter"),
	  gainComponent(p.getApvts(), "OUTPUT_GAIN")
{
	setSize(800, 600);

	addAndMakeVisible(oscillator0);
	addAndMakeVisible(oscillator1);
	addAndMakeVisible(oscillator2);
	addAndMakeVisible(filterComponent);
	addAndMakeVisible(envelopeComponent);
	addAndMakeVisible(gainComponent);
	tooltipWindow = std::make_unique<juce::TooltipWindow>(this);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
	FlexBox oscillators;
	oscillators.flexDirection = FlexBox::Direction::column;

	oscillators.items.add(FlexItem(oscillator0).withFlex(1.0f).withMargin(10));
	oscillators.items.add(FlexItem(oscillator1).withFlex(1.0f).withMargin(10));
	oscillators.items.add(FlexItem(oscillator2).withFlex(1.0f).withMargin(10));

	FlexBox filterAndEnvelope;
	filterAndEnvelope.flexDirection = FlexBox::Direction::column;

	filterAndEnvelope.items.add(FlexItem(envelopeComponent).withFlex(1.0f));
	filterAndEnvelope.items.add(FlexItem(filterComponent).withFlex(2.0f));

	FlexBox fb;
	fb.flexDirection = FlexBox::Direction::row;

	fb.items.add(FlexItem(oscillators).withFlex(1.0f));
	fb.items.add(FlexItem(filterAndEnvelope).withFlex(1.0f).withMargin(10));
	fb.items.add(FlexItem(gainComponent).withFlex(0.2f).withMargin(10));

	fb.performLayout(getLocalBounds());
}
