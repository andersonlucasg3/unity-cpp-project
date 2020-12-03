#if defined(__APPLE__) || defined(__MACH__)

#define __MACOS 1
#define METHOD_EXPORT

#include <dlfcn.h>

#else

#define METHOD_EXPORT __declspec(dllexport)

#include <Windows.h>

#endif

#include <cstdint>
#include <string>

using namespace std;

extern "C" {
    METHOD_EXPORT intptr_t *__LoadLibrary(const char *assemblyName) {
#if __MACOS
        void *ptr = dlopen(assemblyName, RTLD_NOW);
#else
        void *ptr = LoadLibrary(TEXT(assemblyName));
#endif
        return (intptr_t *)ptr;
    }

    METHOD_EXPORT const char *__GetError() {
#if __MACOS
        char *error = dlerror();
#else
        char *error = (char *)to_string(GetLastError()).c_str();
#endif
        if (error) {
            size_t strLen = sizeof(char) * strlen(error);
            char *retError = (char *) malloc(strLen);
            strcpy(retError, (const char *) error);
            return static_cast<const char *>(retError);
        }
        return nullptr;
    }

    METHOD_EXPORT bool __FreeLibrary(intptr_t *assemblyHandle) {
#if __MACOS
        int result = dlclose(assemblyHandle);
#else
        int result = FreeLibrary(reinterpret_cast<HMODULE>(assemblyHandle)) ? 0 : 1;
#endif
        return result == 0;
    }

    METHOD_EXPORT intptr_t *__GetProcAddress(intptr_t *assemblyHandle, const char *symbolName) {
#if __MACOS
        void *ptr = dlsym(assemblyHandle, symbolName);
#else
        void *ptr = (void *)GetProcAddress(reinterpret_cast<HMODULE>(assemblyHandle), TEXT(symbolName));
#endif
        return (intptr_t *)ptr;
    }
}