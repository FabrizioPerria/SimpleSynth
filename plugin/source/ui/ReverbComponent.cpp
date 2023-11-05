#include "ui/ReverbComponent.h"
#include "BinaryData.h"
#include "ui/IconSliderComponent.h"
#include "utils/SVGData.h"

ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState &apvts, juce::String wetdryId, juce::String widthId,
								 juce::String dampingId, juce::String roomSizeId, juce::String name)
	: wetdrySlider(apvts, wetdryId, SVGData{BinaryData::wetdry_svg, BinaryData::wetdry_svgSize},
				   IconSliderDirection::column),
	  widthSlider(apvts, widthId, SVGData{BinaryData::width_svg, BinaryData::width_svgSize},
				  IconSliderDirection::column),
	  dampingSlider(apvts, dampingId, SVGData{BinaryData::highpass_svg, BinaryData::highpass_svgSize},
					IconSliderDirection::column),
	  roomSizeSlider(apvts, roomSizeId, SVGData{BinaryData::room_svg, BinaryData::room_svgSize},
					 IconSliderDirection::column)
{
	wetdrySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	addAndMakeVisible(wetdrySlider);
	widthSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	addAndMakeVisible(widthSlider);
	dampingSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	addAndMakeVisible(dampingSlider);
	roomSizeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	addAndMakeVisible(roomSizeSlider);
	setText(name);
}

void ReverbComponent::resized()
{
	juce::FlexBox flexBox;
	flexBox.flexDirection = juce::FlexBox::Direction::column;

	flexBox.items.add(juce::FlexItem(wetdrySlider).withFlex(1.0f));
	flexBox.items.add(juce::FlexItem(widthSlider).withFlex(1.0f));
	flexBox.items.add(juce::FlexItem(dampingSlider).withFlex(1.0f));
	flexBox.items.add(juce::FlexItem(roomSizeSlider).withFlex(1.0f));

	flexBox.performLayout(getLocalBounds().reduced(10));
}
