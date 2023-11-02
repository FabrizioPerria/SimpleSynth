#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
	: AudioProcessorEditor(&p), processorRef(p), envelopeComponent(p.getApvts()),
	  oscillatorPickerComponent(p.getApvts(), "OSC_WAVETYPE"), gainComponent(p.getApvts(), "GAIN")
{

	setSize(800, 600);

	addAndMakeVisible(envelopeComponent);
	addAndMakeVisible(oscillatorPickerComponent);
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
	FlexBox fb;
	fb.flexDirection = FlexBox::Direction::row;

	fb.items.add(FlexItem(oscillatorPickerComponent).withFlex(1.0f).withMargin(10));
	fb.items.add(FlexItem(envelopeComponent).withFlex(1.0f).withMargin(10));
	fb.items.add(FlexItem(gainComponent).withFlex(0.2f).withMargin(10));

	fb.performLayout(getLocalBounds());
}
