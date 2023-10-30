#include "envelopeComponent.h"

EnvelopeComponent::EnvelopeComponent(juce::AudioProcessorValueTreeState &apvts)
{
	attackAttachment =
		std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "ATTACK", attackSlider);
	decayAttachment =
		std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "DECAY", decaySlider);
	sustainAttachment =
		std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
	releaseAttachment =
		std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "RELEASE", releaseSlider);

	setupSlider(attackSlider);
	setupSlider(decaySlider);
	setupSlider(sustainSlider);
	setupSlider(releaseSlider);
}

EnvelopeComponent::~EnvelopeComponent()
{
}

void EnvelopeComponent::paint(juce::Graphics &g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void EnvelopeComponent::resized()
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

void EnvelopeComponent::setupSlider(juce::Slider &slider)
{
	slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
	addAndMakeVisible(slider);
}
