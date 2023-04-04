# Auto Move NG

 User Requires [Original AutoMove Mod](https://www.nexusmods.com/skyrimspecialedition/mods/42845)
 
 This dll was built from reverse engineering the original mod dll. No source code was given to me. This mod does not distribute anything that was not my work. You still require the script files and esp from the original mod for this dll to be at all useful.
 
 ## Install
 
  - Install the [Original AutoMove Mod](https://www.nexusmods.com/skyrimspecialedition/mods/42845)
  - Install this mod, make sure this mod overwrites `AutoMove.dll`.
 
 
 ## Build
 
 ### Requirements
 
  - Visual Studio 2022
  - Mod Organizer 2 as your mod manager
  - cmake
  - vcpkg
  - A python 3 install for scripts
  
 ### Commands
 
 Set environment variable `MO_SSE_INSTANCE` to the folder path of your Skyrim Special Edition Mod Organizer instance. You will see mods, profiles, overwrite etc in the folder if its the right one. It will expect a mod with the same name as `PROJECT_PLUGIN_NAME` (in this case, "AutoMove NG") in mod organizer to copy fresh binary builds into. Ensure this mod along with the SKSE/Plugins folder is created.
 
 You might need to update the vcpkg baselines, so run `py scripts/update-baselines.py` before the build if you encounter issues.
 
 Build with:
 
 ```
 cmake --preset vs2022-windows
 cmake --build build --config (Debug|Release)
 ```

 If you want to release a build on nexus or something, run `cmake --install build` which will run `scripts/mkrelease.py` to auto zip a build installable by ModOrganizer or vortex.
