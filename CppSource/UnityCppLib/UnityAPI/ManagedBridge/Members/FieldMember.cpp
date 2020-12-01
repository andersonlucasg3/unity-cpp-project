#include "FieldMember.h"
#include "MemberType.h"
#include "UnityAPI/ManagedBridge/ManagedInstance.h"

namespace UnityEngine::ManagedBridge::Members {
    const FieldMember FieldMember::null = FieldMember();

    FieldMember::FieldMember() : ManagedMember(ManagedPointer::null, MemberType::property) {
        // nothing yet
    }

    FieldMember::FieldMember(ManagedPointer ptr) : ManagedMember(ptr, MemberType::field) {
        // nothing yet
    }
}