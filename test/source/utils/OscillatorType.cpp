#include <gtest/gtest.h>
#include "utils/OscillatorType.h"

TEST(OscillatorTypeTest, TestToArray) {
    juce::Array<OscillatorType::Value> array = OscillatorType::toArray();
    // Check that the array contains all OscillatorType values.
    // This will depend on the implementation of OscillatorType::firstValue and OscillatorType::lastValue.
    for (int i = (int) OscillatorType::firstValue; i <= (int) OscillatorType::lastValue; ++i) {
        EXPECT_TRUE(array.contains(static_cast<OscillatorType::Value>(i)));
    }
}

TEST(OscillatorTypeTest, TestToStringArray) {
    juce::StringArray stringArray = OscillatorType::toStringArray();
    // Check that the string array contains all OscillatorType values.
    // This will depend on the implementation of OscillatorType::firstValue and OscillatorType::lastValue.
    for (int i = (int) OscillatorType::firstValue; i <= (int) OscillatorType::lastValue; ++i) {
        EXPECT_TRUE(stringArray.contains(OscillatorType::toString(static_cast<OscillatorType::Value>(i))));
    }
}

TEST(OscillatorTypeTest, TestToString) {
    EXPECT_EQ(OscillatorType::toString(OscillatorType::SINE), "Sine");
    EXPECT_EQ(OscillatorType::toString(OscillatorType::SAW), "Saw");
    EXPECT_EQ(OscillatorType::toString(OscillatorType::SQUARE), "Square");
    EXPECT_EQ(OscillatorType::toString(OscillatorType::TRIANGLE), "Triangle");
}

TEST(OscillatorTypeTest, TestFromInt) {
    EXPECT_EQ(OscillatorType::fromInt(0), OscillatorType::SINE);
    EXPECT_EQ(OscillatorType::fromInt(1), OscillatorType::SQUARE);
    EXPECT_EQ(OscillatorType::fromInt(2), OscillatorType::TRIANGLE);
    EXPECT_EQ(OscillatorType::fromInt(3), OscillatorType::SAW);
}

TEST(OscillatorTypeTest, TestFromIntOutOfBounds) {
    EXPECT_DEATH(OscillatorType::fromInt(-1), "Assertion failed.*isIntValid");
    EXPECT_DEATH(OscillatorType::fromInt(4), "Assertion failed.*isIntValid");
}

TEST(OscillatorTypeTest, TestGetSVG) {
    EXPECT_EQ(OscillatorType::getSVG(OscillatorType::SINE).svg, BinaryData::sine_svg);
    EXPECT_EQ(OscillatorType::getSVG(OscillatorType::SAW).svg, BinaryData::sawtooth_svg);
    EXPECT_EQ(OscillatorType::getSVG(OscillatorType::SQUARE).svg, BinaryData::square_svg);
    EXPECT_EQ(OscillatorType::getSVG(OscillatorType::TRIANGLE).svg, BinaryData::triangle_svg);
}

TEST(OscillatorTypeTest, TestGetSVGSize) {
    EXPECT_EQ(OscillatorType::getSVG(OscillatorType::SINE).size, BinaryData::sine_svgSize);
    EXPECT_EQ(OscillatorType::getSVG(OscillatorType::SAW).size, BinaryData::sawtooth_svgSize);
    EXPECT_EQ(OscillatorType::getSVG(OscillatorType::SQUARE).size, BinaryData::square_svgSize);
    EXPECT_EQ(OscillatorType::getSVG(OscillatorType::TRIANGLE).size, BinaryData::triangle_svgSize);
}
