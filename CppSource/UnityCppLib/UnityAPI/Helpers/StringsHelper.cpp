#include "StringsHelper.h"

#include <cstring>

namespace Helpers {
    string_m stringInstance(string_c str) {
        int len = strlen(str);
        string_m newStr = new char[len];
        strcpy(newStr, str);
        return newStr;
    }

    void freeStringInstance(string_m ptr) {
        delete[] ptr;
    }
}