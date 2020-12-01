# unity-cpp-project

Just a POC demonstrating how we could have all Unity API in Cpp, even without their consent.

There is a [NativeEntryPoint](Assets/UnityCpp/NativeEntryPoint.cs) class in the managed code (Unity C#).

In the [NativeInitialized](CppSource/UnityCppLib/UnityAPI/UnityAPIExtern.cpp) method we do little tests.

Kisses everybody.

### Notes
If you a going to test this locally in your machine, before starting the Unity Editor, build the Cpp code with CMake.
As Unity does not unloads the native libraries after it has been loaded, we need to close and open the Editor every time the binary changes.
Meaning that we have to close the Editor everytime we want to rebuild the Cpp code.
There may be a way to fix that, but that's a problem for another time.

### Next steps

- [ ] Have more of Unity's API available;
- [ ] Test it in a real game scenario;
- [ ] Integrate the Cpp build with the Editor;
- [X] Reload the binary when it has been rebuilt;

### Updates
- Now the Cpp assembly is loaded when the game starts playing and unloaded when the game stops playing.
  So the problem with the rebuild of the native library is solved allowing to better integrate the native code.
