#pragma once

#include "JuceHeader.h"
#include "ui/RadioButtonComponent.h"

template<typename Attachment, typename Control>
std::unique_ptr<Attachment> makeAttachment(const AudioProcessorValueTreeState &stateToUse, const String &parameterID,
										   Control &control)
{
	if (auto *parameter = stateToUse.getParameter(parameterID))
		return std::make_unique<Attachment>(*parameter, control, stateToUse.undoManager);

	jassertfalse;
	return nullptr;
}

class RadioButtonParameterAttachment : juce::Button::Listener
{
  public:
	RadioButtonParameterAttachment(juce::RangedAudioParameter &parameter, RadioButtonComponent &pickerToControl,
								   juce::UndoManager *undoManager = nullptr)
		: attachment(
			  parameter, [this](float v) { valueChanged(v); }, undoManager),
		  picker(pickerToControl)
	{
		picker.addListener(this);
		attachment.sendInitialUpdate();
	}

	~RadioButtonParameterAttachment() override
	{
		picker.removeListener(this);
	}

	void valueChanged(float newValue)
	{
		picker.setSelected(static_cast<int>(newValue));
	}

	void buttonClicked(juce::Button *button) override
	{
		auto index = picker.getIndex(button->getName());
		attachment.setValueAsPartOfGesture(static_cast<float>(index));
	}

  private:
	juce::ParameterAttachment attachment;
	RadioButtonComponent &picker;
};

class RadioButtonAttachment

{
  public:
	RadioButtonAttachment(juce::AudioProcessorValueTreeState &stateToUse, const juce::String &parameterID,
						  RadioButtonComponent &picker)
		: attachment(makeAttachment<RadioButtonParameterAttachment>(stateToUse, parameterID, picker))
	{
	}

  private:
	std::unique_ptr<RadioButtonParameterAttachment> attachment;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RadioButtonAttachment)
};
