#pragma once

#include "../image.h"

#include <vector>
#include <string>

class BasicFilter {
public:
    virtual void Apply(Image& image) const = 0;
    explicit BasicFilter(const std::vector<std::string>& args) : args(args) {
    }
    virtual ~BasicFilter() = default;

protected:
    std::vector<std::string> args;
};