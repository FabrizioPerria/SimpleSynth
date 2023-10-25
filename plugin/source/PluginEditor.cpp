#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
	: AudioProcessorEditor(&p), processorRef(p)
{
	/* juce::ComboBox waveType; */
	waveTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
		processorRef.getApvts(), "OSC_WAVETYPE", waveType);

	/* juce::Slider attackSlider; */
	attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(),
																							  "ATTACK", attackSlider);
	/* juce::Slider decaySlider;  */
	decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(),
																							 "DECAY", decaySlider);
	/* juce::Slider sustainSlider; */
	sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processorRef.getApvts(), "SUSTAIN", sustainSlider);
	/* juce::Slider releaseSlider; */
	releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		processorRef.getApvts(), "RELEASE", releaseSlider);

	/* juce::Slider gainSlider; */
	gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(),
																							"GAIN", gainSlider);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(800, 600);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	/* g.setColour(juce::Colours::white); */
	/* g.setFont(15.0f); */
	/* g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1); */
}

void AudioPluginAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
}
