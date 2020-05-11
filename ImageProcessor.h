#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <cstdint>
#include "CImg.h"

class ImageProcessor
{
	// Image height in pixels
	uint32_t nRows;
	// Image width in pixels
	uint32_t nCols;	
	CImg<int32_t> image;
	
	
public:
	
	ImageProcessor();
	virtual ~ImageProcessor();
	
	// get/set pixel
	int32_t& operator()(uint32_t x, uint32_t y);
	
	// get size in pixels
	uint64_t getSize();
	
	// draw image to screen
	void draw();
	
	// remove image from screen
	void clear();
	
	// perform high-pass filtering on the image
	void highPassFilter();
};


#endif /* IMAGE_PROCESSOR_H */
