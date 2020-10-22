#include "histogram.h"

Histogram::Histogram(Bitmap bitmap)
{
	background = &bitmap;
	rDistribution = new int[256];
	gDistribution = new int[256];
	bDistribution = new int[256];
	for (int i = 0; i < 256; i++)
	{
		rDistribution[i] = 0;
		bDistribution[i] = 0;
		gDistribution[i] = 0;
	}
}

void Histogram::calculateHistogram(Bitmap b)
{
	char* temp_pixel_data = b.getPixels();
	for (int i = 0; i < b.getHeight(); i++)
	{
		for (int j = 0; j < b.getWidth(); j++)
		{
			int rValue = (int)temp_pixel_data[(i * b.getWidth() + j) * 3 + 2];
			int gValue = (int)temp_pixel_data[(i * b.getWidth() + j) * 3 + 1];
			int bValue = (int)temp_pixel_data[(i * b.getWidth() + j) * 3];

			bDistribution[bValue]++;
			gDistribution[gValue]++;
			rDistribution[rValue]++;
		}
	}
}

void Histogram::saveHistogram()
{
}
