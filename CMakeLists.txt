set(CMAKE_CXX_STANDARD 17)

add_executable(
    image_processor
    image_processor.cpp
    pixel.cpp
    image.cpp
    bmp_io.cpp
    parser.cpp
    filters/grayscale.cpp
    filters/crop.cpp
    filters/negative.cpp
    filters/sharp.cpp
    filters/edge.cpp
    filters/spiral.cpp
    filters/blur.cpp
)
