#include <gtest/gtest.h>
#include "data/GainData.h"
#include "JuceHeader.h"

TEST(GainDataTest, TestCanInstantiate)
{
	GainData GainData;
	ASSERT_TRUE(true);
}

TEST(GainDataTest, TestProcessWithoutPrepare)
{
    GainData GainData;
    juce::AudioBuffer<float> buffer(2, 512); // Assuming a buffer with 2 channels and 512 samples

    EXPECT_DEATH( GainData.process(buffer), "Assertion failed.*isPrepared");
}