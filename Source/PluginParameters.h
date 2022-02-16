/*
  ==============================================================================

    PluginParameters.h
    Created: 16 Feb 2022 9:45:13pm
    Author:  Luca Greggio

  ==============================================================================
*/

#pragma once

namespace cdrt
{
    namespace PluginsParameters
    {
        const juce::String id = "preset manager parameters";
        
        namespace param1
        {
            const juce::String id = "param1";
            const juce::String name = "Parmeter 1";
            const float max = 1.0;
            const float min = 0.0;
            const float initial = 0.5;
        }
        
        namespace param2
        {
            const juce::String id = "param2";
            const juce::String name = "Parameter 2";
            const float max = 1.0;
            const float min = 0.0;
            const float initial = 0.7;
        };
        
        namespace saveButton
        {
            const juce::String id = "save_button";
            const juce::String name = "Save";
            const bool initial = false;
        }
    
    }
}
