# unity-cpp-project

Just a POC demonstrating how we could have all Unity API in Cpp even without their consent.

There is a NativeInitializer class in the managed code (Unity C#).

There is a [method](CppSource/UnityCppLib/UnityAPI/UnityAPIExtern.cpp) called `NativeInitialized` in that does the tests.

Kisses everybody.

### Notes
If you a going to test this locally in your machine, before starting the Unity Editor, build the Cpp code with CMake.
As Unity does not unloads the native libraries after it has been loaded, we need to close and open the Editor every time the binary changes.
Meaning that we have to close the Editor everytime we want to rebuild the Cpp code.
There may be a way to fix that, but that's a problem for another time.
