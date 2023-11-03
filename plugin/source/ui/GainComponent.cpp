#include "GainComponent.h"
#include <string>

GainComponent::GainComponent(juce::AudioProcessorValueTreeState &apvts, juce::String parameterId)
{
	setText("Gain");

	gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 20);
	gainSlider.setRange(-40.0f, 0.2f, 0.1f);
	gainSlider.onValueChange = [this]() { updateTooltip(); };
	addAndMakeVisible(gainSlider);
	updateTooltip();

	gainSliderAttachment =
		std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterId, gainSlider);
}

GainComponent::~GainComponent()
{
}

void GainComponent::resized()
{
	juce::FlexBox fb;

	fb.items.add(juce::FlexItem(gainSlider).withFlex(1.0f).withMargin(5));
	fb.performLayout(getLocalBounds().reduced(10));
}

void GainComponent::updateTooltip()
{
	gainSlider.setTooltip(std::to_string(( int ) gainSlider.getValue()));
}