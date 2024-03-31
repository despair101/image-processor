#pragma once

#include "pixel.h"

#include <cstddef>
#include <vector>
#include <array>

class Image {
public:
    Image() = default;
    Image(int32_t height, int32_t width);
    Image(int32_t height, int32_t width, const std::vector<std::vector<Pixel>>& matrix);

    int32_t GetHeight() const;
    int32_t GetWidth() const;
    std::vector<Pixel>& operator[](int32_t i);
    const std::vector<Pixel>& operator[](int32_t i) const;
    Pixel& GetClosest(int32_t i, int32_t j);
    const Pixel& GetClosest(int32_t i, int32_t j) const;
    std::array<Pixel, 4> GetAdjacentPixels(int32_t i, int32_t j) const;
    const std::vector<std::vector<Pixel>>& GetMatrix() const;

private:
    int32_t height_;
    int32_t width_;
    std::vector<std::vector<Pixel>> matrix_;
};