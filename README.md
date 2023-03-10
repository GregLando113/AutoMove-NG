# Auto Move NG

 User Requires ![Original AutoMove Mod](https://www.nexusmods.com/skyrimspecialedition/mods/42845)
 
 This dll was built from reverse engineering the original mod dll. No source code was given to me. This mod does not distribute anything that was not my work. You still require the script files and esp from the original mod for this dll to be at all useful.
 
 ## Install
 
  - Install the ![Original AutoMove Mod](https://www.nexusmods.com/skyrimspecialedition/mods/42845)
  - Install this mod, make sure this mod overwrites `AutoMove.dll`.
 
 
 ## Build
 
 ### Requirements
 
  - Visual Studio 2022
  - cmake
  - vcpkg
  
 ### Commands
 
 Set environment variable `AUTOMOVE_OUTPUT_ROOT` to where you want the mod to install to, either your skyrim data dir or your ModOrganizer mod folder for the project.
 
 ```
 cmake --preset vs2022-windows
 cmake --build build --config (Debug|Release)
 ```