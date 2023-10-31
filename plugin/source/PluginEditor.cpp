#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
	: AudioProcessorEditor(&p), processorRef(p), envelopeComponent(p.getApvts())
{
	/* juce::ComboBox waveType; */
	waveTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
		processorRef.getApvts(), "OSC_WAVETYPE", waveType);

	/* juce::Slider gainSlider; */
	gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(),
																							"GAIN", gainSlider);

	setSize(800, 600);

	addAndMakeVisible(envelopeComponent);
	addAndMakeVisible(oscillatorPickerComponent);
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
	/* fb.flexWrap = FlexBox::Wrap::wrap; */
	/* fb.alignContent = FlexBox::AlignContent::center; */
	/* fb.alignItems = FlexBox::AlignItems::center; */
	/* fb.justifyContent = FlexBox::JustifyContent::center; */

	fb.items.add(FlexItem(envelopeComponent).withFlex(1.0f).withMargin(10));
	fb.items.add(FlexItem(oscillatorPickerComponent).withFlex(1.0f).withMargin(10));

	fb.performLayout(getLocalBounds());
	/* envelopeComponent.setBounds(getLocalBounds().reduced(10)); */
	/* oscillatorPickerComponent.setBounds(getLocalBounds().reduced(10)); */
}
