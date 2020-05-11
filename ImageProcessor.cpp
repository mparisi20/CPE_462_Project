#include "ImageProcessor.h"
#include <thread>

// Thread
void display_wait(CImgDisplay *disp)
{
	if (disp) {
		while (!disp->is_closed)
			disp.wait();
		delete disp;
	} else {
		cerr << "Error in display_wait: disp is a nullptr\n" << endl;
	}
}

ImageProcessor::ImageProcessor()
{
	
}

ImageProcessor::loadImage(string filename, uint32_t width, uint32_t height, string title)
{
	
	
	
	
	thread th(&display_wait, );
	
	CImgDisplay disp_in(image_disp,"Image_In",0);
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
