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
    namespace PresetManager
    {
        namespace Interface
        {
                
            /**
             This interface exposes methods that a Preset Manager must implement.
             */
            class IPresetManager
            {
            public:
                //======================================================================
                /** Destructor */
                virtual ~IPresetManager() {};
                
                //======================================================================
                /** Getters & Setters */
                virtual const juce::PopupMenu getPresetMenu() = 0;
                
                virtual const int getSelectedId() = 0;
        
                //======================================================================
                /**
                 Initialize the preset manager. Supposing that the base preset folder actually extist,
                 the needed files/folders will be added in here.
                 Other than that all currently stored preset will be stored i a data structure.
                 */
                virtual juce::Result initialize() = 0;
        
                /**
                 Refresh preset list. Not always necessary but here if needed.
                 */
                virtual void refresh() = 0;
        
                /**
                 Store a preset preset in the specified path.
                 */
                virtual juce::Result storePreset(const juce::File &destinationFile, const juce::ValueTree &currentState) = 0;

                /**
                 Delete a preset given his path.
                 */
                virtual juce::Result deletePreset(const int id) = 0;

                /**
                 Load a preset given a key, a string, containing the preset name or other informations.
                 */
                virtual juce::ValueTree loadPreset(const int id) = 0;
        
                /**
                 Load the previous preset contained in the data structure contained inside the
                 class that implement this interface
                 */
                virtual juce::ValueTree loadPreviousPreset() = 0;
        
                /**
                 Load the next preset contained in the data structure contained inside the
                 class that implement this interface
                 */
                virtual juce::ValueTree loadNextPreset() = 0;
            }; // class IPresetManager
        } // namespace Interface
    } // namespace PresetManager
} // namespace cdrt
