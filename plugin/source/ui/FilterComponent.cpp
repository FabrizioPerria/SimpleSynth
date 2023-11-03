#include "ui/FilterComponent.h"
#include "BinaryData.h"
#include "utils/SVGData.h"

FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState &apvts, juce::String filterId,
								 juce::String cutoffId, juce::String resonanceId)
	: filterType(apvts, filterId),
	  cutoff(apvts, cutoffId, SVGData{BinaryData::filterCutoff_svg, BinaryData::filterCutoff_svgSize}),
	  resonance(apvts, resonanceId, SVGData{BinaryData::filterResonance_svg, BinaryData::filterResonance_svgSize})
{
	addAndMakeVisible(filterType);
	addAndMakeVisible(cutoff);
	addAndMakeVisible(resonance);
}

void FilterComponent::resized()
{
	juce::FlexBox fbSliders;
	fbSliders.flexDirection = juce::FlexBox::Direction::column;
	fbSliders.items.add(juce::FlexItem(cutoff).withFlex(1.0f));
	fbSliders.items.add(juce::FlexItem(resonance).withFlex(1.0f));

	juce::FlexBox fb;

	fb.flexDirection = juce::FlexBox::Direction::row;

	fb.items.add(juce::FlexItem(filterType).withFlex(1.0f));
	fb.items.add(juce::FlexItem(fbSliders).withFlex(4.0f));

	fb.performLayout(getLocalBounds());
}
