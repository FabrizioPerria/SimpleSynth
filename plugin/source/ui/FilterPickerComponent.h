#pragma once

#include "JuceHeader.h"
#include "attachments/RadioButtonAttachment.h"
#include "ui/RadioButtonComponent.h"

class FilterPickerComponent : public juce::Component
{
  public:
	FilterPickerComponent(juce::AudioProcessorValueTreeState &apvts, juce::String id);
	void resized() override;

  private:
	RadioButtonComponent radioButton;
	std::unique_ptr<RadioButtonAttachment> attachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterPickerComponent)
};
