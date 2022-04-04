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
            const juce::String presetFolderName = "CedrtaDSP";
            
            namespace WinPath
            {
                const juce::String presetBaseFolder = "C:" + Paths::presetFolder;
            }
            
            namespace MacPath
            {
                const juce::String presetBaseFolder = "/Library/Application Support/" + Paths::presetFolder;
            }
        }
    }
}
