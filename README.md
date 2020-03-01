# ExpoGame2020

TO GET WORKING

1. Rename ConsoleApp1 folder to ConsoleApplication1
2. Go to ExpoGame2020-master -> open "ConsoleApplication1" (visual studio file).
2.1. Properties -> Configuration Manager - > set to debug -> x86 -> Win32
3. Once file is open, go to Project -> Properties
4. From here: C/C++ - >General -> set Additional Include Directories to $(SolutionDir)/external/sfml/include
5. Go to Linker -> General -> Additional Library Directories. Set to $(SolutionDir)/external/sfml/lib
6. Click Apply then okay
7. Try to compile the program, if it works GREAT! If not continue.
8. Go back to Linker -> Input -> set to
sfml-graphics-d.lib
sfml-window-d.lib
sfml-system-d.lib
freetype.lib
opengl32.lib
winmm.lib
9. go to C/C++ -> Preprocessor -> Delete all options and set to
WIN32
_DEBUG
_CONSOLE
%(PreprocessorDefinitions)
SFML_DYNAMIC
10. Go to Linker -> System -> ensure subSystem is set to Console (/SUBSYSTEM:CONSOLE)
11.Attempt to compile again
12. If it still doesn't work contact me.


If Problems occur with a file made by us ->>> Solution Explorer -> show all files -> right click on select file(would have red on it) -> 
  include in project -> repeat for all selfmade files not included (.h // .cpp)
