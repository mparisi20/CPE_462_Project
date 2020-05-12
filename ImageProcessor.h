#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <cstdint>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include "CImg.h"

using std::string;
using std::unordered_map;


class ImageProcessor
{
private:
	class CImgData
	{
	public:
		CImgData(CImg<int32_t> *img, CImgDisplay *disp) : image(img), display(disp) { }
		
		CImgData(FILE *fp, uint32_t width, uint32_t height, string title)
		{
			CImg<int> *img = new CImg<int>(width, height, 1, 1, 0);
			
			for (uint32_t y = 0; y < height; y++) {
				for (uint32_t x = 0; x < width; x++) {
					int c;
					if ((c = fgetc(fp)) != EOF) {
						(*img)(x, y, 0, 0) = c;
					} else {
						cerr << "Error reading file for image " << title << endl;
						return;
					}
				}
			}
			
			CImgDisplay *disp = new CImgDisplay((*img), title.c_str(), 0);
			image = img;
			display = disp;			
		}
		
		~CImgData() {
			delete image;
			delete display;
		}
		
		string getTitle() {
			return display->title();
		}
		
		bool isClosed() {
			return display->is_closed;
		}
		
		void wait() {
			display->wait();
		}
		
		CImg<int32_t> *image;
		CImgDisplay *display;
	}
	
	// mapping of title to image/display
	unordered_map<string, CImgData*> images;

public:
	
	ImageProcessor();
	virtual ~ImageProcessor();
	
	// load image from file at filename in raw format (e.g. .512, .256, etc) 
	// and display it on screen
	void loadImage(string filename, uint32_t width, uint32_t height, string title);
	
	void waitToUnload(CImgData* imgData)
	{
		while (!imgData.isClosed)
			imgData.wait();
		// Window has been closed, so remove the image from the map
		images.erase(imgData.getTitle());
		delete imgData;
	}
	
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
