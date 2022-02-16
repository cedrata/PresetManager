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
            const std::string id = "param1";
            const std::string name = "Parmeter 1";
            const float max = 1.0;
            const float min = 0.0;
            const float initial = 0.5;
        }
        
        namespace param2
        {
            const std::string id = "param2";
            const std::string name = "Parameter 2";
            const float max = 1.0;
            const float min = 0.0;
            const float initial = 0.7;
        };
        
        namespace saveButton
        {
            const std::string id = "save_button";
            const std::string name = "Save";
            const bool initial = false;
        }
    
    }
}
