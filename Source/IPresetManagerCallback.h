/*
  ==============================================================================

    IPresetManagerCallback.h
    Created: 18 Apr 2022 8:42:39pm
    Author:  Luca Greggio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace cdrt {
    namespace PresetManager
    {
        namespace Interface
        {
            /**
             This interface exposes methods that a Preset Manager Callback nested class must implement.
             */
            class IPresetManagerCallback
            {
            public:
                //======================================================================
                /** Destructor */
                virtual ~IPresetManagerCallback() {};
                
                //======================================================================
                /** Getters & Setters*/
                virtual const juce::PopupMenu getPresetMenu() = 0;
                
                virtual int getSelectedPresetId() = 0;
                /**
                 Load the prevoius preset contained in the data structure contained in class that
                 implement the IPresetManager interface, the only needed argument is a file
                 representing the currently selected preset.
                */
                virtual int getPreviousPresetId() = 0;
                
                /**
                 Load the next preset contained in the data structure contained in class that
                 implement the IPresetManager interface, the only needed argument is a file
                 representing the currently selected preset.
                */
                virtual int getNextPresetId() = 0;
                
                //======================================================================
                /** Store a preset file juce::File. */
                virtual juce::Result storePreset(const juce::File &destinationFile) = 0;
                
                /** Delete a preset given a juce::File. */
                virtual juce::Result deletePreset(const int id) = 0;
                
                /** Load the preset manager default preset */
                virtual int loadDefaultPreset() = 0;
                
                /** Load a preset given a juce::File. */
                virtual int loadPreset(const int id) = 0;
            }; // calss IPresetManagerCallback
        } // namespace Interface
    } // namespace PresetManager
} // namespace cdrt
