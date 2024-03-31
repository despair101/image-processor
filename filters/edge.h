#pragma once

#include "basic.h"
#include "../image.h"

#include <string>
#include <vector>

class EdgeFilter : public BasicFilter {
public:
    void Apply(Image& image) const override;
    explicit EdgeFilter(const std::vector<std::string> args) : BasicFilter(args) {
    }
    ~EdgeFilter() override = default;

private:
    static inline const double MAIN_COEFF = 4;
    static inline const double SIDE_COEFF = -1;
};