#pragma once

#include "basic.h"
#include "../image.h"

#include <string>
#include <vector>

class GrayscaleFilter : public BasicFilter {
public:
    void Apply(Image& image) const override;
    explicit GrayscaleFilter(const std::vector<std::string> args) : BasicFilter(args) {
    }
    ~GrayscaleFilter() override = default;
    double GetColorCoeff(char c) const;

private:
    static inline const double RED_COEFF = 0.299;
    static inline const double GREEN_COEFF = 0.587;
    static inline const double BLUE_COEFF = 0.114;
};