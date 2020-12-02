#include "StringsHelper.h"

#include <cstring>

namespace Helpers {
    char *stringInstance(const char *str) {
        int len = strlen(str);
        char *newStr = new char[len];
        strcpy(newStr, str);
        return newStr;
    }

    void freeStringInstance(char *ptr) {
        delete[] ptr;
    }
}