#include <gtest/gtest.h>
#include "data/EnvelopeData.h"
#include "JuceHeader.h"

TEST(EnvelopeDataTest, TestCanInstantiate)
{
	EnvelopeData EnvelopeData;
	ASSERT_TRUE(true);
}

TEST(EnvelopeDataTest, TestProcessWithoutPrepare)
{
    EnvelopeData envelopeData;
    juce::AudioBuffer<float> buffer(2, 512); // Assuming a buffer with 2 channels and 512 samples

    EXPECT_DEATH( envelopeData.process(buffer), "Assertion failed.*isPrepared");
}