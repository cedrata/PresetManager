/*
  ==============================================================================

    IPresetManager.h
    Created: 4 Apr 2022 11:09:28pm
    Author:  Luca Greggio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace cdrt
{
    /**
     This interface exposes methods that a Preset Manager must implement.
     */
    class IPresetManager
    {
    public:
        //======================================================================
        /**
         Destructor
         */
        virtual ~IPresetManager() = default;
        
        //======================================================================
        /** Getters & Setters */
        virtual juce::Array<juce::File>& getPresets() = 0;
        
        //======================================================================
        /**
         Initialize the preset manager. Supposing that the base preset folder actually extist,
         the needed files/folders will be added in here.
         Other than that all currently stored preset will be stored i a data structure.
         */
        virtual void initialize() = 0;
        
        /**
         Refresh preset list. To use whenever a change inside the preset folder is committed.
         */
        virtual void refresh() = 0;
        
        /**
         Store a preset with a key, a string, containing the preset name or other informations.
         */
        virtual void store(juce::String id) = 0;
        
        /**
         Load a preset given a key, a string, containing the preset name or other informations.
         */
        // TODO: Chnge return type, return an xml document to load inside
        // the PluginEditor
        virtual void load(juce::String id) = 0;
        
        /**
         Load the previous preset contained in the data structure contained inside the
         class that implement this interface
         */
        virtual void loadPrevious() = 0;
        
        /**
         Load the next preset contained in the data structure contained inside the
         class that implement this interface
         */
        virtual void loadNext() = 0;
    };
} // namespace cdrt
