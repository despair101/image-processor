#include "grayscale.h"
#include "../image.h"

void GrayscaleFilter::Apply(Image& image) const {
    if (!args.empty()) {
        throw std::invalid_argument{"Invalid number of arguments for -gs."};
    }

    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            double color_value = 0;
            for (char c : Pixel::COLORS) {
                color_value += Pixel::NormalizeColorValue(image[i][j].GetColor(c)) * GetColorCoeff(c);
            }
            uint8_t normalized_color_value = Pixel::NormalizeColorValue(color_value);
            image[i][j] = Pixel{normalized_color_value, normalized_color_value, normalized_color_value};
        }
    }
}

double GrayscaleFilter::GetColorCoeff(char c) const {
    if (c == 'r') {
        return RED_COEFF;
    }
    if (c == 'g') {
        return GREEN_COEFF;
    }
    if (c == 'b') {
        return BLUE_COEFF;
    }
    throw std::invalid_argument{"Invalid color name."};
}