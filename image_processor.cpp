#include "pixel.h"
#include "image.h"
#include "bmp_io.h"
#include "filters/all.h"
#include "parser.h"
#include "help.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    try {
        if (argc == 1) {
            PrintInfo();
            return 0;
        }
        if (argc == 2) {
            throw std::invalid_argument{"Invalid number of arguments."};
        }

        const std::string input_file{argv[1]};
        const std::string output_file{argv[2]};

        BitmapIO bitmap_io;
        Image image = bitmap_io.Read(input_file);

        FilterParser parser;
        for (const auto& filter : parser.Parse(argc, argv)) {
            filter->Apply(image);
        }

        bitmap_io.Write(output_file, image);
    } catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
