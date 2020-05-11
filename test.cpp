// test.cpp
#include <string>
#include "ImageProcessor.h"

using std::string;

int main(void)
{
	ImageProcessor proc;
	proc.loadImage("lenna.512", 512, 512, "Image1");
	
	// This overload modifies Image 1 by computing the negative of the image
	proc.negative("Image1");
	
	// This overload creates a new image for the result
	// of the operation, and it does not modify Image1
	proc.negative("Image1", "Image2"); 
	
	return 0;
}
