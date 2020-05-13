#include "ImageProcessor.h"
#include <thread>
#include <iostream>
#include <cstdio>

using std::cerr;
using namespace cimg_library;

ImageProcessor::ImageProcessor()
{
	
}

void ImageProcessor::loadImage(string filename, uint32_t width, uint32_t height, string title)
{
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		cerr << "Could not open file " << filename << "\n";
		return;
	}
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);
	if (size != uint64_t(width)*height) {
		cerr << filename << " is not the indicated size\n";
		return;
	}
	
	CImgData *imgData = new CImgData(fp, width, height, title);

	images.insert(make_pair<string, CImgData*>(imgData->getTitle(), imgData));
	thread th(&waitToUnload, imgData);
}

ImageProcessor::~ImageProcessor()
{
	//TODO
}

// High-pass Filter the selected image
void ImageProcessor::highPassFilter(string imageName)
{
	
}

void ImageProcessor::negative(string imageNameIn, string imageNameOut)
{
	if (images.find(imageNameIn) == images.end()) {
		cerr << "An image named " << imageNameIn << " is not currently loaded" << endl;
	} else {
		CImgData *imgIn = images[imageNameIn];
		CImgData *imgOut = new CImgData(imgIn->getWidth(), imgIn->getHeight, imageNameOut);
		CImgData(uint32_t width, uint32_t height, string title)
		for (uint32_t y = 0; y < height; y++) {
			for (uint32_t x = 0; x < width; x++) {
				= 255 - (*images[imageNameIn])(x, y, 0, 0);
			}
		}
	  
	}
}

void ImageProcessor::negative(string imageName)
{
	
	img(x, y, 0, 0, img.width() * img.height(), 0);
	
}
