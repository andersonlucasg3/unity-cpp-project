#include "PropertyMember.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"

namespace UnityEngine::ManagedBridge::Members {
    const PropertyMember PropertyMember::null = PropertyMember();

    PropertyMember::PropertyMember() : ManagedMember(ManagedPointer::null, MemberType::property) {
        // nothing yet
    }

    PropertyMember::PropertyMember(ManagedPointer ptr) : ManagedMember(ptr, MemberType::property) {
        // nothing yet
    }

    template<typename TValue>
    TValue PropertyMember::get(ManagedInstance instance) const {
        return ManagedMember::pull<TValue>(instance);
    }

    template<typename TValue>
    void PropertyMember::set(ManagedInstance instance, TValue value) const {
        ManagedMember::push(instance, value);
    }
}