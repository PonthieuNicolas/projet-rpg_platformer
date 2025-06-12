#include "pch.h"
#include "Status.h"

Status::Status(const std::string& value) : value(value) {}

void Status::SetValue(const std::string& v) {
    value = v;
}

std::string Status::GetValue() const {
    return value;
}

std::string Status::GetComponentName() const {
    return "Status";
}
