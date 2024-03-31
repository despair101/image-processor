#include "image.h"
#include "pixel.h"
#include "bmp_io.h"

#include <fstream>

void BitmapIO::ReadBitmapFileHeader(BitmapFileHeader& bitmap_file_header, std::ifstream& input) const {
    input.read(reinterpret_cast<char*>(&bitmap_file_header), sizeof(bitmap_file_header));
}

void BitmapIO::ReadBitmapInfoHeader(BitmapInfoHeader& bitmap_info_header, std::ifstream& input) const {
    input.read(reinterpret_cast<char*>(&bitmap_info_header), sizeof(bitmap_info_header));
}

void BitmapIO::WriteBitmapFileHeader(int32_t height, int32_t width, std::ofstream& output) const {
    uint32_t row_size = static_cast<uint32_t>(width * sizeof(Pixel));
    uint32_t padded_row_size = (row_size + 3) / 4 * 4;

    BitmapFileHeader bitmap_file_header{
        .indetifier = BMP_IDENTIFIER,
        .size = static_cast<uint32_t>(height * padded_row_size + sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader)),
        .reserved_1 = 0,
        .reserved_2 = 0,
        .offset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader)};

    output.write(reinterpret_cast<char*>(&bitmap_file_header), sizeof(bitmap_file_header));
}

void BitmapIO::WriteBitmapInfoHeader(int32_t height, int32_t width, std::ofstream& output) const {
    uint32_t row_size = static_cast<uint32_t>(width * sizeof(Pixel));
    uint32_t padded_row_size = (row_size + 3) / 4 * 4;

    BitmapInfoHeader bitmap_info_header{.header_size = sizeof(BitmapInfoHeader),
                                        .width = static_cast<int32_t>(width),
                                        .height = static_cast<int32_t>(height),
                                        .color_planes_number = 1,
                                        .color_depth = COLOR_DEPTH,
                                        .compression_method = 0,
                                        .image_size = static_cast<uint32_t>(height * padded_row_size),
                                        .horizontal_resolution = 0,
                                        .vertical_resolution = 0,
                                        .pallete_colors_number = 0,
                                        .important_colors_number = 0};

    output.write(reinterpret_cast<char*>(&bitmap_info_header), sizeof(bitmap_info_header));
}

Image BitmapIO::Read(const std::string& path) const {
    std::ifstream input(path, std::ios::binary);

    if (!input.is_open()) {
        throw std::runtime_error{"Can't open input BMP file."};
    }

    try {
        BitmapFileHeader bitmap_file_header;
        ReadBitmapFileHeader(bitmap_file_header, input);

        if (bitmap_file_header.indetifier != BMP_IDENTIFIER) {
            throw std::invalid_argument{"Input file is not a BMP."};
        }

        BitmapInfoHeader bitmap_info_header;
        ReadBitmapInfoHeader(bitmap_info_header, input);

        int32_t height = std::abs(bitmap_info_header.height);
        int32_t width = std::abs(bitmap_info_header.width);

        Image image{height, width};
        uint32_t row_size = static_cast<uint32_t>(width * sizeof(Pixel));
        uint32_t padded_row_size = (row_size + 3) / 4 * 4;

        char buf[4]{};
        for (int32_t i = 0; i < height; ++i) {
            input.read(reinterpret_cast<char*>(image[height - 1 - i].data()), row_size);
            input.read(buf, padded_row_size - row_size);
        }

        input.close();

        return image;
    } catch (const std::invalid_argument& e) {
        throw e;
    } catch (...) {
        throw std::runtime_error{"Can't read input BMP file."};
    }
}

void BitmapIO::Write(std::string path, const Image& image) const {
    std::ofstream output(path);

    if (!output.is_open()) {
        throw std::runtime_error{"Can't open output BMP file."};
    }

    try {
        int32_t height = image.GetHeight();
        int32_t width = image.GetWidth();

        WriteBitmapFileHeader(height, width, output);
        WriteBitmapInfoHeader(height, width, output);

        uint32_t row_size = static_cast<uint32_t>(width * sizeof(Pixel));
        uint32_t padded_row_size = (row_size + 3) / 4 * 4;

        char buf[4]{};
        for (int32_t i = 0; i < height; ++i) {
            output.write(reinterpret_cast<const char*>(image[height - 1 - i].data()), row_size);
            output.write(buf, padded_row_size - row_size);
        }

        output.close();
    } catch (...) {
        throw std::runtime_error{"Can't write output BMP file."};
    }
}