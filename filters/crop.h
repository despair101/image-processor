#pragma once

#include "basic.h"
#include "../image.h"

class CropFilter : public BasicFilter {
public:
    void Apply(Image& image) const override;
    explicit CropFilter(const std::vector<std::string> args) : BasicFilter(args) {
    }
    ~CropFilter() override = default;
};