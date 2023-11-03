#include "ui/OscillatorComponent.h"
#include "BinaryData.h"
#include "utils/SVGData.h"

OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState &apvts, juce::String pickerId,
										 juce::String gainId, juce::String lfoFrequencyId, juce::String lfoDepthId,
										 juce::String name)
	: oscillatorPicker(apvts, pickerId), lfoFrequency(apvts, lfoFrequencyId, "LFO Frequency"),
	  lfoDepth(apvts, lfoDepthId, "LFO Depth"),
	  gain(apvts, gainId, SVGData{BinaryData::volume_svg, BinaryData::volume_svgSize})
{
	gain.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	lfoFrequency.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	lfoDepth.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
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
	juce::FlexBox fbLFO;
	fbLFO.flexDirection = juce::FlexBox::Direction::row;
	fbLFO.items.add(juce::FlexItem(lfoFrequency).withFlex(1.0f));
	fbLFO.items.add(juce::FlexItem(lfoDepth).withFlex(1.0f));

	juce::FlexBox fbMain;
	fbMain.flexDirection = juce::FlexBox::Direction::row;
	fbMain.items.add(juce::FlexItem(oscillatorPicker).withFlex(0.8f));
	fbMain.items.add(juce::FlexItem(gain).withFlex(1.0f));

	juce::FlexBox fb;
	fb.flexDirection = juce::FlexBox::Direction::column;
	fb.items.add(juce::FlexItem(fbMain).withFlex(1.0f));
	fb.items.add(juce::FlexItem(fbLFO).withFlex(2.0f));

	fb.performLayout(getLocalBounds().reduced(10));
}
