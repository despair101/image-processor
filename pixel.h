#pragma once

#include <algorithm>
#include <cmath>
#include <array>

class Pixel {
public:
    Pixel() = default;
    Pixel(uint8_t r, uint8_t g, uint8_t b);

    static uint8_t NormalizeColorValue(double value) {
        return static_cast<uint8_t>(std::max<int32_t>(
            Pixel::MIN_COLOR_VALUE,
            std::min<int32_t>(Pixel::MAX_COLOR_VALUE, static_cast<int32_t>(std::round(value * MAX_COLOR_VALUE)))));
    }
    static double NormalizeColorValue(uint8_t value) {
        return static_cast<double>(value) / MAX_COLOR_VALUE;
    }
    void SetColor(char name, uint8_t color_value);
    uint8_t GetColor(char name) const;

    static const uint8_t MIN_COLOR_VALUE = 0;
    static const uint8_t MAX_COLOR_VALUE = UINT8_MAX;
    static constexpr std::array<char, 3> COLORS{'r', 'g', 'b'};

private:
    uint8_t b_;
    uint8_t g_;
    uint8_t r_;
};