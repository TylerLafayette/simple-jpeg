#include <cstdio>
#include <cstdlib>
#include "bitmap_image.hpp"
#include "jpeg_encoder.hpp"

int main(int argc, char *argv[]) {
    // Initialize the JPEGEncoder with our first argument
    JPEGEncoder encoder (argv[1]);
    // Load the image into an array of YCrCb color values
    encoder.LoadImageIntoYCbCr();
    // Run the discrete cosine transform
    encoder.RunDCT();

    return 0;
}