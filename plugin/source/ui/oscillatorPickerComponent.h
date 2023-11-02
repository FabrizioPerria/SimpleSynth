#pragma once

#include "JuceHeader.h"
#include "ui/RadioButtonComponent.h"
#include "attachments/RadioButtonAttachment.h"

class OscillatorPickerComponent : public juce::GroupComponent
{
  public:
	OscillatorPickerComponent(juce::AudioProcessorValueTreeState &apvts, const juce::String &parameterID);
	~OscillatorPickerComponent() override;

	void resized() override;

  private:
	RadioButtonComponent radioButton;
	std::unique_ptr<RadioButtonAttachment> attachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorPickerComponent)
};
