/*
  ==============================================================================

    PresetManager.cpp
    Created: 4 Apr 2022 11:09:49pm
    Author:  Luca Greggio

  ==============================================================================
*/

#include "PresetManager.h"
#include "Paths.h"

namespace cdrt
{
    // Constructor
    PresetManager::PresetManager() noexcept
        : pathsAreBuilt(false)
    {
        osType = juce::SystemStats::getOperatingSystemType();
    }
    
    void PresetManager::initialize() noexcept
    {
        buildPaths();
        
        listPresets();
    }
    
    //==========================================================================
    void PresetManager::buildPaths() noexcept
    {
        if ((osType & juce::SystemStats::MacOSX) != 0)
        {
            separator = cdrt::Constants::Paths::MacPath::separator;
            prefix = cdrt::Constants::Paths::MacPath::presetBaseFolder
                + separator
                + cdrt::Constants::Paths::presetFolderName;
            suffix = cdrt::Constants::Paths::presetExtension;
        }
        else if ((osType & juce::SystemStats::Windows) != 0)
        {
            separator = cdrt::Constants::Paths::WinPath::separator;
            prefix = cdrt::Constants::Paths::WinPath::presetBaseFolder
                + separator
                + cdrt::Constants::Paths::presetFolderName;
            suffix = cdrt::Constants::Paths::presetExtension;
        }
        
        juce::File *presetFolder = new juce::File(prefix);
        if (!presetFolder->exists())
        {
            // If needed this method returns status if creation was succesfull or not.
            // Right now is not used.
            presetFolder->createDirectory();
        }
    }
    
    void PresetManager::listPresets() noexcept
    {
        // TODO: Find all presets inside the folder.
        //  Find folders and files, remember you want to do a nested dropdown.
        // Remember to use TypeOfFilesToFind. Important see if "presets" attribute is good for nested or must be changed to dynamic.
//        presetFolder.findChildFiles(int whatToLookFor, bool searchRecursively)
    }
}
