/*
  ==============================================================================

    Constants.h
    Created: 20 Feb 2022 8:39:49am
    Author:  Luca Greggio

  ==============================================================================
*/

#pragma once

namespace cdrt
{
    namespace Constants
    {
        namespace Paths
        {
            const juce::String presetFolderName = "PresetManager";
            
            const juce::String presetExtension = ".xml";
            
            namespace WinPath
            {
                const juce::String separator = "\\";
                const juce::String presetBaseFolder = "C:";
            }
            
            namespace MacPath
            {
                const juce::String separator = "/";
                const juce::String presetBaseFolder = "/Library/Application Support/CedrataDSP";
            }
        }
    }
}
