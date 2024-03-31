#include "negative.h"
#include "../image.h"

void NegativeFilter::Apply(Image& image) const {
    if (!args.empty()) {
        throw std::invalid_argument{"Invalid number of arguments for -neg."};
    }

    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            for (char c : Pixel::COLORS) {
                image[i][j].SetColor(c, Pixel::MAX_COLOR_VALUE - image[i][j].GetColor(c));
            }
        }
    }
}