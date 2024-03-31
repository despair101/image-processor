#include "image.h"

#include <iostream>

Image::Image(int32_t height, int32_t width)
    : height_(height), width_(width), matrix_(height, std::vector<Pixel>(width)) {
}

Image::Image(int32_t height, int32_t width, const std::vector<std::vector<Pixel>>& matrix)
    : height_(height), width_(width), matrix_(matrix) {
}

int32_t Image::GetHeight() const {
    return height_;
}

int32_t Image::GetWidth() const {
    return width_;
}

std::vector<Pixel>& Image::operator[](int32_t i) {
    return matrix_[i];
}

const std::vector<Pixel>& Image::operator[](int32_t i) const {
    return matrix_[i];
}

Pixel& Image::GetClosest(int32_t i, int32_t j) {
    return matrix_[std::max(0, std::min(i, height_ - 1))][std::max(0, std::min(j, width_ - 1))];
}

const Pixel& Image::GetClosest(int32_t i, int32_t j) const {
    return matrix_[std::max(0, std::min(i, height_ - 1))][std::max(0, std::min(j, width_ - 1))];
}

std::array<Pixel, 4> Image::GetAdjacentPixels(int32_t i, int32_t j) const {
    return {GetClosest(i - 1, j), GetClosest(i + 1, j), GetClosest(i, j - 1), GetClosest(i, j + 1)};
}

const std::vector<std::vector<Pixel>>& Image::GetMatrix() const {
    return matrix_;
}
