#include "edge.h"
#include "grayscale.h"
#include "../image.h"

#include <string>
#include <vector>
#include <memory>

void EdgeFilter::Apply(Image& image) const {
    if (args.size() != 1) {
        throw std::invalid_argument{"Invalid number of arguments for -edge."};
    }

    double threshold{};
    try {
        threshold = std::stod(args[0]);
    } catch (...) {
        throw std::invalid_argument{"Invalid argument type for -edge."};
    }

    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();

    GrayscaleFilter{{}}.Apply(image);

    Image result{height, width};

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            for (char c : Pixel::COLORS) {
                double color_value = MAIN_COEFF * Pixel::NormalizeColorValue(image[i][j].GetColor(c));
                for (auto const& adjacent_pixel : image.GetAdjacentPixels(i, j)) {
                    color_value += SIDE_COEFF * Pixel::NormalizeColorValue(adjacent_pixel.GetColor(c));
                }
                result[i][j].SetColor(c, color_value > threshold ? Pixel::MAX_COLOR_VALUE : Pixel::MIN_COLOR_VALUE);
            }
        }
    }

    image = std::move(result);
}
