#pragma once

#include "JuceHeader.h"
#include "ui/RadioButtonComponent.h"

class RadioButtonParameterAttachment : public juce::Button::Listener
{
  public:
	RadioButtonParameterAttachment(juce::RangedAudioParameter &parameter, RadioButtonComponent &pickerToControl,
								   juce::UndoManager *undoManager = nullptr);

	~RadioButtonParameterAttachment() override;

	void valueChanged(float newValue);
	void buttonClicked(juce::Button *button) override;

  private:
	juce::ParameterAttachment attachment;
	RadioButtonComponent &picker;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RadioButtonParameterAttachment)
};

class RadioButtonAttachment
{
  public:
	RadioButtonAttachment(juce::AudioProcessorValueTreeState &stateToUse, const juce::String &parameterID,
						  RadioButtonComponent &picker);

  private:
	std::unique_ptr<RadioButtonParameterAttachment> attachment;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RadioButtonAttachment)
};
