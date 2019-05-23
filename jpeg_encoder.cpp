#include <string>
#include "bitmap_image.hpp"
#include "jpeg_encoder.hpp"

// 8x8 pixels, with a Y, Cb, Cr value for each
#define CHUNK_SIZE (8 * 8 * 3)

JPEGEncoder::JPEGEncoder(char* file) {
    this->image = bitmap_image(file);

    if (!this->image) {
        printf("Error - Failed to open file: %s\n", file);
        return;
    }

    this->height = this->image.height();
    this->width = this->image.width();
    this->chunks = 0;
}

int JPEGEncoder::coordinateToIndex(int x, int y) {
    return ((y * this->width) + x)*3;
}



double JPEGEncoder::calculateY(int r, int g, int b) {
    return (0.257 * r) + (0.504 * g) + (0.098 * b) + 16;
}

double JPEGEncoder::calculateCb(int r, int g, int b) {
    return ((-0.148) * r) - (0.291 * g) + (0.439 * b) + 128;
}

double JPEGEncoder::calculateCr(int r, int g, int b) {
    return (0.439 * r) - (0.368 * g) - (0.071 * b) + 128;
}

std::vector<int> JPEGEncoder::genChunk(int x, int y) {
    std::vector<int> output;
    for(size_t i = 0; i < 8; i++) {
        for(size_t j = 0; j < 8; j++) {
            int localIndex = ((i * 8) + j)*3;
            int remoteIndex = this->coordinateToIndex(x + i, y + j);
            output.push_back(this->pixels[remoteIndex + 0]);
            output.push_back(this->pixels[remoteIndex + 1]);
            output.push_back(this->pixels[remoteIndex + 2]);
        }
    }

    return output;
}

std::vector< std::vector<int> > JPEGEncoder::chunkify() {
    // Create a vector of CHUNK_SIZE chunks
    std::vector< std::vector<int> > vector;

    // Iterate through every 8 pixels in our width
    for(size_t x = 0; x < this->width - 8; x += 8) {
        // Iterate through every 8 pixels in our height
        for(size_t y = 0; y < this->height - 8; y += 8) {
            this->chunks++;
            vector.push_back(genChunk(x, y));
        }
    }

    return vector;
}

void JPEGEncoder::dctChunk(std::vector<int> chunk) {

}

void JPEGEncoder::LoadImageIntoYCbCr() {
    // Initialize an array with a spot for each pixel's R, G, and B value
    this->arraySize = this->height * this->width * 3;
    int pixels[this->arraySize];

    bitmap_image::rgb_t color;
    for(size_t x = 0; x < this->width; x++) {
        for(size_t y = 0; y < this->height; y++) {
            this->image.get_pixel(x, y, color);
            // Get the index of the first value of this pixel in our array
            int index = this->coordinateToIndex(x, y);
            int r = (int) color.red;
            int g = (int) color.green;
            int b = (int) color.blue;

            // Convert RGB to YCbCr
            pixels[index + 0] = ((int) (this->calculateY(r, g, b) / 10)) * 10;
            pixels[index + 1] = this->calculateCb(r, g, b);
            pixels[index + 2] = this->calculateCr(r, g, b);
        }
    }

    // Save the pixels array in the class
    this->pixels = pixels;
}

void JPEGEncoder::RunDCT(int index) {
    std::vector< std::vector<int> > chunks = this->chunkify();
    for(size_t i = 0; i < this->chunks; i++) this->dctChunk(chunks[i]);
}