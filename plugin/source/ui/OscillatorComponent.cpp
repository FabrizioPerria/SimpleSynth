#include "ui/OscillatorComponent.h"

OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState &apvts, juce::String pickerId,
										 juce::String gainId, juce::String lfoFrequencyId, juce::String lfoDepthId,
										 juce::String name)
	: oscillatorPicker(apvts, pickerId), lfoFrequency(apvts, lfoFrequencyId, "LFO Frequency"),
	  lfoDepth(apvts, lfoDepthId, "LFO Depth"), gain(apvts, gainId, "Gain")
{
	gain.setSliderOrientation(juce::Slider::SliderStyle::LinearHorizontal);
	lfoFrequency.setSliderOrientation(juce::Slider::SliderStyle::LinearHorizontal);
	lfoDepth.setSliderOrientation(juce::Slider::SliderStyle::LinearHorizontal);
	addAndMakeVisible(oscillatorPicker);
	addAndMakeVisible(lfoFrequency);
	addAndMakeVisible(lfoDepth);
	addAndMakeVisible(gain);
	setText(name);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::resized()
{
	juce::FlexBox fbSliders;
	fbSliders.flexDirection = juce::FlexBox::Direction::column;
	fbSliders.items.add(juce::FlexItem(gain).withFlex(1.0f));
	fbSliders.items.add(juce::FlexItem(lfoFrequency).withFlex(1.0f));
	fbSliders.items.add(juce::FlexItem(lfoDepth).withFlex(1.0f));

	juce::FlexBox fb;
	fb.flexDirection = juce::FlexBox::Direction::row;
	fb.flexWrap = juce::FlexBox::Wrap::wrap;

	fb.items.add(juce::FlexItem(oscillatorPicker).withFlex(1.0f));
	fb.items.add(juce::FlexItem(fbSliders).withFlex(2.0f));
	fb.performLayout(getLocalBounds().reduced(10));
}
