/*
  ==============================================================================

    PresetManager.h
    Created: 4 Apr 2022 11:09:49pm
    Author:  Luca Greggio

  ==============================================================================
*/

#pragma once

#include "IPresetManager.h"

namespace cdrt
{
    class PresetManager : public IPresetManager
    {
    public:
        /** Construcotr */
        PresetManager() noexcept;
        
        /** Destructor */
        ~PresetManager() override;
        
        //======================================================================
        // IPresetManager
        const juce::Array<juce::File>& getPresets() noexcept override;
        
        void initialize() noexcept override;
        
        void refresh() noexcept override;
        
        void store(juce::String id) noexcept  override;
        
        void load(juce::String id) noexcept override;
        
        void loadPrevious() noexcept override;
        
        void loadNext() noexcept override;
    private:
        //======================================================================
        juce::SystemStats::OperatingSystemType osType;
        juce::String separator;
        juce::String prefix;
        juce::String suffix;
        juce::File presetFolder;
        juce::Array<juce::File> presets;
        
        bool pathsAreBuilt;
        
        //======================================================================
        /** This method will be called from inside the initialize method to generate a juce::File variable representing the preset folder. */
        void buildPaths() noexcept;
        
        /** This method will be called from inside the initialize method to list all the presets contained in the preset folder.*/
        void listPresets() noexcept;
    };
} // namespace cdrt
