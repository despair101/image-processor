#pragma once

#include "basic.h"
#include "../image.h"

#include <vector>
#include <string>

class BlurFilter : public BasicFilter {
public:
    void Apply(Image& image) const override;
    explicit BlurFilter(const std::vector<std::string> args) : BasicFilter(args) {
    }
    ~BlurFilter() override = default;
};