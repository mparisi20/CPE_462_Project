#include <cstdint>

template<typename T>
class Image
{
	int32_t nRows;	// Image height in pixels
	int32_t nCols;	// Image width in pixels
	T *data; // Bitmap
	
	
public:
	
	Image();
	virtual ~Image();
	
	
};
