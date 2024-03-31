#pragma once

#include <iostream>

void PrintInfo() {
    std::cout << "USAGE:" << std::endl;
    std::cout << "image_processor {input file} {output file} [-{filter 1} [filter param 1] [filter param 2] ...] "
                 "[-{filter 2} ...] ..."
              << std::endl;
    std::cout << "FILTERS:" << std::endl;
    std::cout << "-crop {width} {height} : crops the image to the given width and height (top-left part is used)"
              << std::endl;
    std::cout << "-gs                    : converts the image to grayscale" << std::endl;
    std::cout << "-neg                   : converts the image to negative" << std::endl;
    std::cout << "-sharp                 : increases image sharpness" << std::endl;
    std::cout << "-edge {threshold}      : detects image edges" << std::endl;
    std::cout << "-spiral                : converts the image to spiral" << std::endl;
    std::cout << "-blur {sigma}          : blurs the image" << std::endl;
}