#include "ImageProcessor.h"

ImageProcessor::ImageProcessor()
{
	//TODO
}

ImageProcessor::~ImageProcessor()
{
	//TODO
}

uint32_t ImageProcessor::getSize()
{
	return nRows * nCols;
}

// High-pass Filter
void ImageProcessor::highPassFilter()
{

	int m = 0, n = 0, o = 0, p = 0, q = 0;
	for (int j = 0; j < height; j++) {
		for (int k = 0; k < width; k++) {
			m = image_in[j][k] * 5;
			if (j + 1 < height) {
				n = image_in[j + 1][k] * (-1);
			}
			if (j - 1 > 0) {
				o = image_in[j - 1][k] * (-1);
			}
			if (k + 1 < width) {
				p = image_in[j][k + 1] * (-1);
			}
			if (k - 1 > 0) {
				q = image_in[j][k - 1] * (-1);
			}
			m = m + n + o + p + q;
			if (m > 255) {
				m = 255;
			}
			else if (m < 0) {
				m = 0;
			}
			image_out[j][k] = m;
		}
	}
	====== =

	//test

	
}
