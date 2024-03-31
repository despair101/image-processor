#include "spiral.h"
#include "../image.h"
#include "grayscale.h"

#include <cmath>

const double SPIRAL_COEFF = 400;

void SpiralFilter::Apply(Image& image) const {
    if (!args.empty()) {
        throw std::invalid_argument{"Invalid number of arguments for -spiral."};
    }

    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();
    int32_t height_center = height / 2;
    int32_t width_center = width / 2;

    Image result = image;

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            int32_t delta_i = i - height_center;
            int32_t delta_j = j - width_center;
            double radius = std::sqrt(delta_i * delta_i + delta_j * delta_j);
            double angle = std::atan2(delta_i, delta_j);

            int32_t new_i = static_cast<int32_t>(height_center + radius * std::sin(angle + radius / SPIRAL_COEFF));
            int32_t new_j = static_cast<int32_t>(width_center + radius * std::cos(angle + radius / SPIRAL_COEFF));
            result.GetClosest(new_i, new_j) = image[i][j];
        }
    }

    image = std::move(result);
}