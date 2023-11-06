#include <gtest/gtest.h>
#include "data/ReverbData.h"
#include "JuceHeader.h"

TEST(ReverbDataTest, TestCanInstantiate)
{
	ReverbData ReverbData;
	ASSERT_TRUE(true);
}

TEST(ReverbDataTest, TestProcessWithoutPrepare)
{
    ReverbData ReverbData;
    juce::AudioBuffer<float> buffer(2, 512); // Assuming a buffer with 2 channels and 512 samples

    EXPECT_DEATH( ReverbData.process(buffer), "Assertion failed.*isPrepared");
}