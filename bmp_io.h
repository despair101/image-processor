#pragma once

#include "image.h"

#include <cstdint>

class BitmapIO {
public:
    Image Read(const std::string& path) const;
    void Write(std::string path, const Image& image) const;

private:
    struct BitmapFileHeader {
        uint16_t indetifier;
        uint32_t size;
        uint16_t reserved_1;
        uint16_t reserved_2;
        uint32_t offset;
    } __attribute__((packed));

    struct BitmapInfoHeader {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t color_planes_number;
        uint16_t color_depth;
        uint32_t compression_method;
        uint32_t image_size;
        int32_t horizontal_resolution;
        int32_t vertical_resolution;
        uint32_t pallete_colors_number;
        uint32_t important_colors_number;
    } __attribute__((packed));

    static inline const uint16_t BMP_IDENTIFIER = 0x4D42;
    static inline const uint16_t COLOR_DEPTH = 24;

    void ReadBitmapFileHeader(BitmapFileHeader& bitmap_file_header, std::ifstream& input) const;
    void ReadBitmapInfoHeader(BitmapInfoHeader& bitmap_info_header, std::ifstream& input) const;
    void WriteBitmapFileHeader(int32_t width, int32_t height, std::ofstream& output) const;
    void WriteBitmapInfoHeader(int32_t width, int32_t height, std::ofstream& output) const;
};
