#include "FieldMember.h"
#include "MemberType.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"

namespace UnityEngine::ManagedBridge::Members {
    FieldMember::FieldMember(ManagedPointer ptr) : ManagedMember(ptr, MemberType::field) {
        // nothing yet
    }

    template<typename TValue>
    TValue FieldMember::get(ManagedInstance instance) const {
        return ManagedMember::pull<TValue>(instance);
    }

    template<typename TValue>
    void FieldMember::set(ManagedInstance instance, TValue value) const {
        ManagedMember::push(instance, value);
    }

    template TValue FieldMember::get<typename TValue>(ManagedInstance instance) const {}
}