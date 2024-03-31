#pragma once

#include "basic.h"
#include "../image.h"

#include <vector>
#include <string>

class SpiralFilter : public BasicFilter {
public:
    void Apply(Image& image) const override;
    explicit SpiralFilter(const std::vector<std::string> args) : BasicFilter(args) {
    }
    ~SpiralFilter() override = default;
};