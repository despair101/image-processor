#include "sharp.h"
#include "../image.h"

#include <string>
#include <vector>

void SharpFilter::Apply(Image& image) const {
    if (!args.empty()) {
        throw std::invalid_argument{"Invalid number of arguments for -sharp."};
    }

    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();

    Image result{height, width};

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            for (char c : Pixel::COLORS) {
                double color_value = MAIN_COEFF * Pixel::NormalizeColorValue(image[i][j].GetColor(c));
                for (auto const& adjacent_pixel : image.GetAdjacentPixels(i, j)) {
                    color_value += SIDE_COEFF * Pixel::NormalizeColorValue(adjacent_pixel.GetColor(c));
                }
                result[i][j].SetColor(c, Pixel::NormalizeColorValue(color_value));
            }
        }
    }

    image = std::move(result);
}
