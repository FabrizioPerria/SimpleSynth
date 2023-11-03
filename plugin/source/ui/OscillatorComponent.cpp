#include "ui/OscillatorComponent.h"
#include "BinaryData.h"
#include "utils/SVGData.h"

OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState &apvts, juce::String pickerId,
										 juce::String gainId, juce::String lfoFrequencyId, juce::String lfoDepthId,
										 juce::String name)
	: oscillatorPicker(apvts, pickerId),
	  lfoFrequency(apvts, lfoFrequencyId, SVGData{BinaryData::LFOFreq_svg, BinaryData::LFOFreq_svgSize}),
	  lfoDepth(apvts, lfoDepthId, SVGData{BinaryData::LFODepth_svg, BinaryData::LFODepth_svgSize}),
	  gain(apvts, gainId, SVGData{BinaryData::volume_svg, BinaryData::volume_svgSize})
{
	gain.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	lfoFrequency.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	lfoDepth.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
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
	fb.items.add(juce::FlexItem(oscillatorPicker).withFlex(1.0f));
	fb.items.add(juce::FlexItem(fbSliders).withFlex(3.0f));

	fb.performLayout(getLocalBounds().reduced(10));
}
