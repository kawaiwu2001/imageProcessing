#ifndef PROCESSING_H
#define PROCESSING_H
#include "bmp.h"
#include <vector>
using namespace std;

BMP* nearest_neighbor(BMP* p, double sx, double sy);
BMP* bilinear(BMP* p, double sx, double sy);
BMP* gaussian_smoothing(BMP* p, double sigma);
BMP* histogram_equalization(BMP* p);
BMP* sharpening_sobel(BMP* p, double k1, double k2);
BMP* impulsive_noise_salt(BMP* p, double rate);
BMP* impulsive_noise_random(BMP* p, double rate);
BMP* median_filtering(BMP* p, int filter);
void square_sampling(BYTE* s, BMP* p, int radius, int center_x, int center_y);

#endif // PROCESSING_H
