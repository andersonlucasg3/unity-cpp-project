#include <dlfcn.h>
#include <cstdint>
#include <string>

using namespace std;

#define METHOD_EXPORT __declspec(dllexport)

extern "C" {
    METHOD_EXPORT intptr_t *LoadLibrary(const char *assemblyName) {
        void *ptr = dlopen(assemblyName, RTLD_NOW);
        return (intptr_t *)ptr;
    }

    METHOD_EXPORT const char *GetError() {
        char *error = dlerror();
        if (error) {
            size_t strLen = sizeof(char) * strlen(error);
            char *retError = (char *) malloc(strLen);
            strcpy(retError, (const char *) error);
            return static_cast<const char *>(retError);
        }
        return nullptr;
    }

    METHOD_EXPORT bool FreeLibrary(intptr_t *assemblyName) {
        int result = dlclose(assemblyName);
        return result == 0;
    }

    METHOD_EXPORT intptr_t *GetProcAddress(intptr_t *assembly, const char *symbolName) {
        void *ptr = dlsym(assembly, symbolName);
        return (intptr_t *)ptr;
    }
}
