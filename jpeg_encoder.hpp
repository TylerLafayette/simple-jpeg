#include <string>
#include "bitmap_image.hpp"

#ifndef JPEG_ENCODER_H
#define JPEG_ENCODER_H

class JPEGEncoder {
private:
    bitmap_image image;
    unsigned int width;
    unsigned int height;
    unsigned int arraySize;
    unsigned int chunks;
    int coordinateToIndex(int x, int y);
    double calculateY(int r, int g, int b);
    double calculateCb(int r, int g, int b);
    double calculateCr(int r, int g, int b);
    std::vector<int> genChunk(int x, int y);
    std::vector< std::vector<int> > chunkify();
    void dctChunk(std::vector<int> chunk);
    int* pixels;
public:
    JPEGEncoder(char* file);
    void LoadImageIntoYCbCr();
    void RunDCT(int index);
};

#endif  // JPEG_ENCODER_H