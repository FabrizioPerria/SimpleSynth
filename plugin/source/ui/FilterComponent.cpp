#include "ui/FilterComponent.h"
#include "BinaryData.h"
#include "utils/SVGData.h"

FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState &apvts, juce::String filterId,
								 juce::String cutoffId, juce::String resonanceId, juce::String name)
	: filterType(apvts, filterId),
	  cutoff(apvts, cutoffId, SVGData{BinaryData::filterCutoff_svg, BinaryData::filterCutoff_svgSize},
			 IconSliderDirection::column),
	  resonance(apvts, resonanceId, SVGData{BinaryData::filterResonance_svg, BinaryData::filterResonance_svgSize},
				IconSliderDirection::column),
	  envelope(apvts, "FILTER_ATTACK", "FILTER_DECAY", "FILTER_SUSTAIN", "FILTER_RELEASE", "")
{
	addAndMakeVisible(filterType);
	cutoff.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	addAndMakeVisible(cutoff);
	resonance.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	addAndMakeVisible(resonance);
	addAndMakeVisible(envelope);
	setText(name);
}

void FilterComponent::resized()
{
	juce::FlexBox fbSliders;
	fbSliders.flexDirection = juce::FlexBox::Direction::row;
	fbSliders.items.add(juce::FlexItem(cutoff).withFlex(1.0f));
	fbSliders.items.add(juce::FlexItem(resonance).withFlex(1.0f));

	juce::FlexBox fb;

	fb.flexDirection = juce::FlexBox::Direction::column;

	fb.items.add(juce::FlexItem(filterType).withFlex(0.2f).withMaxHeight(50).withMargin(10));
	fb.items.add(juce::FlexItem(fbSliders).withFlex(1.0f));
	fb.items.add(juce::FlexItem(envelope).withFlex(1.0f));

	fb.performLayout(getLocalBounds());
}
