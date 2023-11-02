#include "ui/OscillatorComponent.h"

OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState &apvts, juce::String pickerId,
										 juce::String gainId, juce::String name)
	: oscillatorPicker(apvts, pickerId), gain(apvts, gainId, "Gain")
{
	gain.setSliderOrientation(juce::Slider::SliderStyle::LinearHorizontal);
	addAndMakeVisible(oscillatorPicker);
	addAndMakeVisible(gain);
	setText(name);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::resized()
{
	juce::FlexBox fb;
	fb.flexDirection = juce::FlexBox::Direction::row;
	fb.flexWrap = juce::FlexBox::Wrap::wrap;

	fb.items.add(juce::FlexItem(oscillatorPicker).withFlex(1.0f));
	fb.items.add(juce::FlexItem(gain).withFlex(1.0f));
	fb.performLayout(getLocalBounds().reduced(10));
}
