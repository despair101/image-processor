#pragma once

#include "basic.h"
#include "../image.h"

#include <vector>
#include <string>

class NegativeFilter : public BasicFilter {
public:
    void Apply(Image& image) const override;
    explicit NegativeFilter(const std::vector<std::string> args) : BasicFilter(args) {
    }
    ~NegativeFilter() override = default;
};