#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
	: AudioProcessorEditor(&p), processorRef(p), envelopeComponent(p.getApvts()),
	  oscillatorComponent(p.getApvts(), "OSC_WAVETYPE", "OSC_GAIN", "OSC_LFO_FREQ", "OSC_LFO_DEPTH", "Oscillator"),
	  gainComponent(p.getApvts(), "OUTPUT_GAIN")
{

	setSize(800, 600);

	addAndMakeVisible(envelopeComponent);
	addAndMakeVisible(oscillatorComponent);
	addAndMakeVisible(gainComponent);
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

	oscillators.items.add(FlexItem(oscillatorComponent).withFlex(1.0f).withMargin(10));

	FlexBox fb;
	fb.flexDirection = FlexBox::Direction::row;

	fb.items.add(FlexItem(oscillators).withFlex(1.0f).withMargin(10));
	fb.items.add(FlexItem(envelopeComponent).withFlex(1.0f).withMargin(10));
	fb.items.add(FlexItem(gainComponent).withFlex(0.2f).withMargin(10));

	fb.performLayout(getLocalBounds());
}
