#include "crop.h"
#include "../image.h"

#include <vector>

void CropFilter::Apply(Image& image) const {
    if (args.size() != 2) {
        throw std::invalid_argument{"Invalid number of arguments for -crop."};
    }

    int32_t height = image.GetHeight();
    int32_t width = image.GetWidth();

    try {
        height = std::min(height, std::stoi(args[0]));
        width = std::min(width, std::stoi(args[1]));
    } catch (...) {
        throw std::invalid_argument{"Invalid argument type for -crop."};
    }

    auto matrix = image.GetMatrix();

    matrix.erase(matrix.begin() + static_cast<uint32_t>(height), matrix.end());
    for (auto& row : matrix) {
        row.erase(row.begin() + static_cast<uint32_t>(width), row.end());
    }

    image = Image{height, width, matrix};
}