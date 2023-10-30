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

	setupSlider(attackSlider);
	setupSlider(decaySlider);
	setupSlider(sustainSlider);
	setupSlider(releaseSlider);
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
	const auto bounds = getLocalBounds().reduced(10);
	const auto padding = 10;
	const auto sliderWidth = bounds.getWidth() / 4 - padding;
	const auto sliderHeight = bounds.getHeight() / 4 - padding;

	const auto sliderStartX = 0;
	const auto sliderStartY = bounds.getHeight() / 2 - sliderHeight / 2;

	attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
	decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void AudioPluginAudioProcessorEditor::setupSlider(juce::Slider &slider)
{
	slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
	addAndMakeVisible(slider);
}
