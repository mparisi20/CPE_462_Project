#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <cstdint>
#include <cstdio>
#include <vector>
#include <string>
#include "CImg.h"

using std::vector;
using std::string;

class ImageProcessor
{
	vector<CImg<int32_t>&> images;
	
	
public:
	
	ImageProcessor();
	virtual ~ImageProcessor();
	
	// load image from file at filename in raw format (e.g. .512, .256, etc) and 
	// provide width and height
	void loadImage(string filename, uint32_t width, uint32_t height, string name);
	
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
	
	
	void negative();
	
};


#endif /* IMAGE_PROCESSOR_H */
