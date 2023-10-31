#include "envelopeData.h"

void EnvelopeData::update(const float attack, const float decay, const float sustain, const float release)
{
	envelopeParameters.attack = attack;
	envelopeParameters.decay = decay;
	envelopeParameters.sustain = sustain;
	envelopeParameters.release = release;

	setParameters(envelopeParameters);
}
