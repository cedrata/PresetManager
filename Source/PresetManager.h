///*
//  ==============================================================================
//
//    PresetManager.h
//    Created: 4 Apr 2022 11:09:49pm
//    Author:  Luca Greggio
//
//  ==============================================================================
//*/
//
#pragma once

#include "IPresetManager.h"
#include "IPresetManagerCallback.h"
namespace cdrt
{
    namespace PresetManager
    {
        namespace Impelementation
        {
            class PresetManager : public Interface::IPresetManager
            {
            public:
                /** Constructor */
                PresetManager(const juce::File &defaultPreset) noexcept;
        
                /** Destructor */
                ~PresetManager() override;
        
                //======================================================================
                // IPresetManager
                /**
                 TODO: Comment
                 */
                const juce::PopupMenu getPresetMenu() noexcept override;
                /**
                 TODO: Comment
                 */
                int getPreviousPresetId() noexcept override;
                
                /**
                 TODO: Comment
                 */
                int getNextPresetId() noexcept override;
                
                const int getSelectedId() noexcept override;
                /**
                 TODO: Comment
                 */
                juce::Result initialize() noexcept override;
        
                /**
                 TODO: Comment
                 */
                void refresh() noexcept override;
              
                /**
                 TODO: Comment
                 */
                juce::Result storePreset(const juce::File &destinationFile, const juce::ValueTree &currentState) noexcept override;
                
                /**
                 TODO: Comment
                 */
                juce::Result deletePreset(const int id) noexcept override;
                
                /**
                 TODO: Comment
                 */
                juce::ValueTree loadDefaultPreset() noexcept override;
                
                /**
                 TODO: Comment
                 */
                juce::ValueTree loadPreset(const int id) noexcept override;

            private:
                //======================================================================
                // Paths
                bool pathsAreBuilt;
                juce::SystemStats::OperatingSystemType osType;
                juce::String separator;
                juce::String prefix;
                juce::String suffix;
                juce::File presetFolder;
                
                // Files
                // Index of active preset inside avaiablePresets.
                int selectedPresetIndex;
                juce::File defaultPreset;
                juce::Array<juce::File> avaiablePresets;
                // juce::Array<juce::File> avaiableSubMenus;
                
                // PopuMenu
                // This index is used to build the popupmenu,
                // precisely when recursiley building the submenus an id must be assigned,
                // this way is possible to know what is the last assigned ID in the popup menu
                // and assign the correct next one.
                int creationIndex;
                juce::PopupMenu presetsPopupMenu;


                //======================================================================
                /**
                 This method will be called from inside the initialize method to check if the default preset is valid or not.
                 It returns true if the default preset file has been validate succesfully, otherwise it will return false.
                 */
                bool validateDefault() noexcept;
                /**
                 This method will be called from inside the initialize method to generate a juce::File variable representing the preset folder.
                 */
                void buildPaths() noexcept;

                /**
                 This method will be called from inside the initialize method to list all the presets contained in the preset folder.
                 */
                /*
                 TODO: Delete this method, can refactor prest listing during buildSubMenuRecursive.
                 When adding a new preset in the buildSubMenuRecursive an id is setted.
                 By adding the preset in the avaiable presets list in this precise moment the index
                 will be the same as the id.
                */
                // void listPresets() noexcept;
                
                /**
                 This method will be called from inside the initialize method to list all the sub menus contained in the preset folder.
                 */
                // void listSubMenus() noexcept; // TODO: Delete this method, is unused.
                
                /**
                 This method will be called from inside the refresh method to build the PopupMenu instance
                 to return with the getPopupMenu method.
                 */
                void buildPopupMenu() noexcept;
                
                /**
                 This method is recursive and called from buildPopupMenu method given a starting point folder.
                 The aim is to generate a sub menu for a PopupMenu with submenus in it.
                 */
                const juce::PopupMenu buildSubMenuRecursive(const juce::File& directoryToSubMenu) noexcept;
                
                /**
                 This method will be called each time the selected preset changes to update the tick inside the presets juce::PopupMenu
                 */
                void togglePopupMenuTicked(const int creationIndex) noexcept;
            }; // class PresetManager
        } // namespace Implementation
    } // namespace PresetManager
} // namespace cdrt
