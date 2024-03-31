#include "pixel.h"

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b) : b_(b), g_(g), r_(r) {
}

uint8_t Pixel::GetColor(char name) const {
    if (name == 'r') {
        return r_;
    }
    if (name == 'g') {
        return g_;
    }
    if (name == 'b') {
        return b_;
    }
    throw std::invalid_argument{"Invalid color name."};
}

void Pixel::SetColor(char name, uint8_t color_value) {
    if (name == 'r') {
        r_ = color_value;
    } else if (name == 'g') {
        g_ = color_value;
    } else if (name == 'b') {
        b_ = color_value;
    } else {
        throw std::invalid_argument{"Invalid color name."};
    }
}