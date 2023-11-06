#include "attachments/RadioButtonAttachment.h"

template<typename Attachment, typename Control>
std::unique_ptr<Attachment> makeAttachment(const AudioProcessorValueTreeState &stateToUse, const String &parameterID,
										   Control &control)
{
	if (auto *parameter = stateToUse.getParameter(parameterID))
		return std::make_unique<Attachment>(*parameter, control, stateToUse.undoManager);

	assert(false);
	return nullptr;
}

RadioButtonAttachment::RadioButtonAttachment(juce::AudioProcessorValueTreeState &stateToUse,
											 const juce::String &parameterID, RadioButtonComponent &picker)
	: attachment(makeAttachment<RadioButtonParameterAttachment>(stateToUse, parameterID, picker))
{
}

RadioButtonParameterAttachment::RadioButtonParameterAttachment(juce::RangedAudioParameter &parameter,
															   RadioButtonComponent &pickerToControl,
															   juce::UndoManager *undoManager)
	: attachment(
		  parameter, [this](float v) { valueChanged(v); }, undoManager),
	  picker(pickerToControl)
{
	picker.addListener(this);
	attachment.sendInitialUpdate();
}

RadioButtonParameterAttachment::~RadioButtonParameterAttachment()
{
	picker.removeListener(this);
}

void RadioButtonParameterAttachment::valueChanged(float newValue)
{
	picker.setSelected(static_cast<int>(newValue));
}

void RadioButtonParameterAttachment::buttonClicked(juce::Button *button)
{
	auto index = picker.getIndex(button->getName());
	attachment.setValueAsPartOfGesture(static_cast<float>(index));
}
