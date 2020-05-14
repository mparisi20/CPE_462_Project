// CPE 462 Project
// by David Li and Max Parisi
// I pledge my honor that I have abided by the Stevens Honor System.
	// -David Li, Max Parisi

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cinttypes>
#include <random>
#include <iostream>

#include "CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[])
{
	FILE  *in, *out;
	int   j, k, width, height;
	int ** image_in, ** image_out;
	float sum1, sum2;
	float new_T, old_T, delta_T;
	long count1, count2;

	// Supported processes
	enum ImageProcess { 
		negative, 
		histogram_equalization, 
		laplacian, 
		threshold,
		high_pass_filter,
		low_pass_filter,
		speckle,
		white_noise
	};


	if(argc != 6) { 
		printf(".\\proc.exe <infile> <outfile> <width> <height> <process>\n");
		printf("Supported processes: \n"
				"0\tnegative\n"
				"1\thistogram_equalization\n"
				"2\tlaplacian\n"
				"3\tthreshold\n"
				"4\thigh_pass_filter\n"
				"5\tlow_pass_filter\n"
				"6\tspeckle\n"
				"7\twhite_noise\n");
		return 1;
	}

	width = atoi(argv[3]);
	height = atoi(argv[4]);

	image_in = (int**) calloc(height, sizeof(int*));
	if(!image_in)
	{
		printf("Error: Can't allocate memmory!\n");
		return(1);
	}

	image_out = (int**) calloc(height, sizeof(int*));
	if(!image_out)
	{
		printf("Error: Can't allocate memmory!\n");
		return(1);
	}

	for (j=0; j<height; j++)
	{
		image_in[j] = (int *) calloc(width, sizeof(int));
		if(!image_in[j])
		{
			printf("Error: Can't allocate memmory!\n");
			return(1);
		}

		image_out[j] = (int *) calloc(width, sizeof(int));
		if(!image_out[j])
		{
			printf("Error: Can't allocate memmory!\n");
			return(1);
		}

	}

	if((in=fopen(argv[1],"rb"))==NULL)
	{
		printf("ERROR: Can't open in_file!\n");
		return(1);
	}

	if((out=fopen(argv[2],"wb"))==NULL)
	{
		printf("ERROR: Can't open out_file!\n");
		return(1);
	}

	for (j=0; j<height; j++)
		for (k=0; k<width; k++)
	    	{
			if((image_in[j][k]=getc(in))==EOF)
			{
				printf("ERROR: Can't read from in_file!\n");
				return(1);
		      }
	    	}
      if(fclose(in)==EOF)
	{
		printf("ERROR: Can't close in_file!\n");
		return(1);
	}

	/* display image_in */
	CImg<int> image_disp(width, height,1,1,0);
	/* CImg<type> image_name(width,height,temporal_frame_number,color_plane_number,initial_value) */

	for (j=0; j<height; j++)
		for (k=0; k<width; k++)
	   	{
			image_disp(k,j,0,0) = image_in[j][k];
		}
	CImgDisplay disp_in(image_disp,"Image_In",0);
	/* CImgDisplay display_name(image_displayed, "window title", normalization_factor) */


/********************************************************************/
/* Image Processing begins                                          */
/********************************************************************/

	ImageProcess process = (ImageProcess) atoi(argv[5]);

	if (process == negative) {
		for (j=0; j<height; j++)
			for (k=0; k<width; k++)
				image_out[j][k]=255-image_in[j][k];
	} else if (process == histogram_equalization) {
		int L = 256; // number of intensity levels
		// Generate histogram of input image and the pixel
		// intensity transform
		int *in_histogram = (int *) calloc(L, sizeof(int));
		int *transform = (int *) calloc(L, sizeof(int));
		if (!in_histogram || !transform) {
			printf("calloc failed to allocate histograms\n");
			return 1;
		}
		for (j = 0; j < height; j++) {
			for (k = 0; k < width; k++) {
				int val = image_in[j][k]; // each pixel value will be between 0 and 255
				in_histogram[val]++;
			}
		}
		// compute the equalized histogram transform
		int N = width*height; // total pixels. Needed to convert each histogram bin into a probability
		int sum_inputs;
		for (int i = 0; i < L; i++) {
			sum_inputs = 0;
			for (int j = 0; j <= i; j++) {
				sum_inputs += in_histogram[j];
			}
			transform[i] = round((double) sum_inputs / N * (L - 1));
		}

		// use the transform to produce image_out
		for (j = 0; j < height; j++) {
			for (k = 0; k < width; k++) {
				image_out[j][k] = transform[image_in[j][k]];
			}
		}
	} else if (process == laplacian) {
		/* 3x3 Laplacian composite mask, stored in row-major order:
			|  0 -1  0 |
			| -1  5 -1 |
			|  0 -1  0 |
		*/
		//int mask[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1};
		int mask[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };
		for (j = 0; j < height; j++) {
			for (k = 0; k < width; k++) {
				if (j == 0 || k == 0 || j == height-1 || k == width-1) {
					// cannot apply 3x3 mask to outer outline, so just copy
					// the pixel from image_in instead
					image_out[j][k] = image_in[j][k];
				} else {
					
					// apply the 3x3 composite Laplacian mask from the Lecture 7 slides
					image_out[j][k] = image_in[j-1][k-1] * mask[0] + image_in[j-1][k] * mask[1] +
									  image_in[j-1][k+1] * mask[2] + image_in[j][k-1] * mask[3] +
									  image_in[j][k] * mask[4] + image_in[j][k+1] * mask[5] +
									  image_in[j+1][k-1] * mask[6] +image_in[j+1][k] * mask[7] +
  									  image_in[j+1][k+1] * mask[8];
				}
			}
		}
	} else if (process == threshold) {
		static const int a = 5;
		static const int initial_T = 128;

		uint64_t ndark = 0, nlight = 0;
		uint64_t dark_sum = 0, light_sum = 0;
		int prev_threshold;
		int threshold = initial_T;
		int pixel;
		do {
			// printf("threshold == %d\n", threshold);
			prev_threshold = threshold;
			for (int j = 0; j < height; j++) {
				for (int k = 0; k < width; k++) {
					pixel = image_in[j][k];
					if (pixel > threshold) {
						light_sum += pixel;
						nlight++;
					}
					else {
						dark_sum += pixel;
						ndark++;
					}
				}
			}
			// compute averages
			double light_avg = (double) light_sum / nlight;
			double dark_avg = (double) dark_sum / ndark;
			threshold = 0.5 * (light_avg + dark_avg);
		} while (abs(threshold - prev_threshold) >= a);
		printf("threshold == %d\n", threshold);
		// Generate the output image
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < width; k++) {
				pixel = image_in[j][k];
				if (pixel >= threshold)
					image_out[j][k] = 255;
				else
					image_out[j][k] = 0;
			}
		}		
	} else if (process == high_pass_filter) {
		int m = 0, n = 0, o = 0, p = 0, q = 0;
		//start implementing the mask
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < width; k++) {
				//center
				m = image_in[j][k] * 5;

				//implement all four edges
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
				//correct for over/under boundaries
				if (m > 255) {
					m = 255;
				}
				else if (m < 0) {
					m = 0;
				}
				image_out[j][k] = m;
			}
		}
	} else if (process == low_pass_filter) {
		int m = 0, n = 0, o = 0, p = 0, q = 0;
		//start implementing the mask
		for (j = 0; j < height; j++) {
			for (k = 0; k < width; k++) {
				//center
				m = image_in[j][k] * -3;

				//edges
				if (j + 1 < height) {
					n = image_in[j + 1][k] * (1);
				}
				if (j - 1 > 0) {
					o = image_in[j - 1][k] * (1);
				}
				if (k + 1 < width) {
					p = image_in[j][k + 1] * (1);
				}
				if (k - 1 > 0) {
					q = image_in[j][k - 1] * (1);
				}
				m = m + n + o + p + q;
				//correct for over/under boundaries
				if (m > 255) {
					m = 255;
				}
				else if (m < 0) {
					m = 0;
				}
				image_out[j][k] = m;
			}
		}
	} else if (process == speckle) {
		// Create normal distribution with mean 1 and stddev 0
		std::random_device rd{};
		std::mt19937 gen{rd()};

		// Model speckle as multiplicative noise
		std::normal_distribution<double> d{1.75, 0};
		for (j = 0; j < height; j++) {
			for (k = 0; k < width; k++) {
				int new_value = std::round(image_in[j][k] * d(gen));
				// debug
				//std::cout << new_value << std::endl;
				image_out[j][k] = new_value;
			}
		}
	} else if (process == white_noise) {
		// Create normal distribution with mean 1 and stddev 0
		std::random_device rd{};
		std::mt19937 gen{rd()};

		// Model white noise as additive noise
		std::normal_distribution<double> d{0, 40};
		for (j = 0; j < height; j++) {
			for (k = 0; k < width; k++) {
				int new_value = std::round(image_in[j][k] + d(gen));
				// debug
				//std::cout << new_value << std::endl;
				image_out[j][k] = new_value;
			}
		}
	} else {
		printf("ERROR: invalid image process operation %d\n", (int) process);
		printf("Performing no process...\n");
		for (j = 0; j < height; j++)
			for (k = 0; k < width; k++)
				image_out[j][k] = image_in[j][k];
	}

/********************************************************************/
/* Image Processing ends                                          */
/********************************************************************/

	/* display image_out */
	for (j=0; j<height; j++)
		for (k=0; k<width; k++)
	   	{
			image_disp(k,j,0,0) = image_out[j][k];
		}
	CImgDisplay disp_out(image_disp,"Image_Out",0);


	/* save image_out into out_file in RAW format */
	for (j=0; j<height; j++)
		for (k=0; k<width; k++)
	    {
	            if((putc(image_out[j][k],out))==EOF)
	            {
		        	printf("ERROR: Can't write to out_file!\n");
				    return(1);
	            }
		}

    if(fclose(out)==EOF)
	{
		printf("ERROR: Can't close out_file!\n");
		return(1);
	}

	/* closing */
	while (!disp_in.is_closed)
		disp_in.wait();
	while (!disp_out.is_closed)
		disp_out.wait();

	for (j=0; j<height; j++)
	{
		free(image_in[j]);
		free(image_out[j]);
	}
	free(image_in);
	free(image_out);

    return 0;
}



