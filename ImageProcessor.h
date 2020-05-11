#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <cstdint>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include "CImg.h"

using std::map;
using std::string;
using std::unordered_map;


class ImageProcessor
{
private:
	class CImgData
	{
	public:
		CImg<int32_t> image;
		CImgDisplay disp;
	}
	
	unordered_map<string, CImgData> images;

public:
	
	ImageProcessor();
	virtual ~ImageProcessor();
	
	// load image from file at filename in raw format (e.g. .512, .256, etc) 
	// and display it on screen
	void loadImage(string filename, uint32_t width, uint32_t height, string title);
	
	// get size of a currently loaded image in pixels
	uint64_t getSize(string title);
	
	// remove image from screen
	void clear();
	
	// save every image on screen to files in raw format
	void save();
	
	// perform high-pass filtering on the image
	void highPassFilter();
	
	// lowpass filtering
	void lowPassFilter();
	
	// negative
	void negative();
	
};


#endif /* IMAGE_PROCESSOR_H */
