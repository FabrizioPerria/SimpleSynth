#include <gtest/gtest.h>
#include <PluginProcessor.h>

namespace audio_plugin_test {
    TEST(AudioPlugin, CanInstantiatePlugin)
    {
        AudioPluginAudioProcessor processor {};
        ASSERT_TRUE(true);
    }
}
