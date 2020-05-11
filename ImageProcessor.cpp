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
	
	
}

void ImageProcessor::negative()
{
	
	img(x, y, 0, 0, img.width() * img.height(), 0);
	
}
