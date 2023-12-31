#include "ui/OscillatorComponent.h"
#include "BinaryData.h"
#include "utils/SVGData.h"

OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState &apvts, juce::String pickerId,
										 juce::String gainId, juce::String lfoFrequencyId, juce::String lfoDepthId,
										 juce::String name)
	: oscillatorPicker(apvts, pickerId),
	  gain(apvts, gainId, SVGData{BinaryData::volume_svg, BinaryData::volume_svgSize}),
	  lfo(apvts, lfoFrequencyId, lfoDepthId)
{
	gain.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	addAndMakeVisible(oscillatorPicker);
	addAndMakeVisible(gain);
	addAndMakeVisible(lfo);
	setText(name);
}

OscillatorComponent::~OscillatorComponent()
{
}

void OscillatorComponent::resized()
{
	juce::FlexBox fbSliders;
	fbSliders.flexDirection = juce::FlexBox::Direction::column;
	fbSliders.items.add(juce::FlexItem(gain).withFlex(0.8f));
	fbSliders.items.add(juce::FlexItem(lfo).withFlex(1.0f));

	juce::FlexBox fb;
	fb.flexDirection = juce::FlexBox::Direction::row;
	fb.items.add(juce::FlexItem(oscillatorPicker).withFlex(1.0f));
	fb.items.add(juce::FlexItem(fbSliders).withFlex(3.0f));

	fb.performLayout(getLocalBounds().reduced(10));
}
