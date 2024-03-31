#pragma once

#include "basic.h"
#include "../image.h"

#include <string>
#include <vector>

class SharpFilter : public BasicFilter {
public:
    void Apply(Image& image) const override;
    explicit SharpFilter(const std::vector<std::string> args) : BasicFilter(args) {
    }
    ~SharpFilter() override = default;

private:
    static inline const double MAIN_COEFF = 5;
    static inline const double SIDE_COEFF = -1;
};