#include "blur.h"
#include "../image.h"

#include <cmath>
#include <vector>

const int32_t SIGMA_COEFF = 3;

void BlurFilter::Apply(Image &image) const {
    if (args.size() != 1) {
        throw std::invalid_argument{"Invalid number of arguments for -blur."};
    }

    double sigma{};
    try {
        sigma = std::stod(args[0]);
    } catch (...) {
        throw std::invalid_argument{"Invalid argument type for -blur."};
    };

    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();

    Image result{height, width};

    int32_t max_delta = static_cast<int32_t>(std::round(sigma * SIGMA_COEFF));
    double denom = 2 * sigma * sigma;

    for (char c : Pixel::COLORS) {
        std::vector tmp(height, std::vector<double>(width));
        for (int32_t i = 0; i < height; ++i) {
            for (int32_t j = 0; j < width; ++j) {
                for (int32_t dj = -max_delta; dj <= max_delta; ++dj) {
                    tmp[i][j] +=
                        Pixel::NormalizeColorValue(image.GetClosest(i, j + dj).GetColor(c)) * exp(-(dj * dj / denom));
                }
            }
        }
        for (int32_t i = 0; i < height; ++i) {
            for (int32_t j = 0; j < width; ++j) {
                double color_value = 0;
                for (int32_t di = -max_delta; di <= max_delta; ++di) {
                    color_value += tmp[std::max(0, std::min(i + di, height - 1))][j] * exp(-(di * di / denom));
                }
                color_value /= (M_PI * denom);
                result[i][j].SetColor(c, Pixel::NormalizeColorValue(color_value));
            }
        }
    }

    image = std::move(result);
}