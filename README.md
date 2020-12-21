# unity-cpp-project

Just a POC demonstrating how we could have all Unity API in Cpp, even without their consent.

There is a [NativeEntryPoint](Assets/UnityCpp/NativeEntryPoint.cs) class in the managed code (Unity C#).

In the [InitializeNative](CppSource/UnityCppLib/UnityAPI/UnityAPIExtern.cpp) method we do little tests.

Kisses everybody.

### How to setup (WIP project, use at your own risk)

Just add a git package to your unity project using this [repository](https://github.com/andersonlucasg3/unity-cpp-project-package.git).
After that, access the menu `Assets -> UnityCpp` and see the options available.
Documentation about the items in that menu will be added here in the future.

### Notes
If you a going to test this locally in your machine, before starting the Unity Editor, build the Cpp code with CMake.
As Unity does not unloads the native libraries after it has been loaded, we need to close and open the Editor every time the binary changes.
Meaning that we have to close the Editor everytime we want to rebuild the Cpp code.
There may be a way to fix that, but that's a problem for another time.

### Next steps

- [X] Reload the binary when it has been rebuilt;
- [X] Integrate the Cpp build with the Editor;
- [ ] Have more of Unity's API available;
- [ ] Test it in a real game scenario;

### Updates
- C++ build/clean integrated to Unity Assets menu with hotkeys;
- Now methods are supported;
- Updated the Managed API to allow loading type information from .Net API so we can instantiate any managed symbol from the C++.
- Now the Cpp assembly is loaded when the game starts playing and unloaded when the game stops playing.
  So the problem with the rebuild of the native library is solved allowing to better integrate the native code.
