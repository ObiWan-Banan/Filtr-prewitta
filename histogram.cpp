#include "histogram.h"

Histogram::Histogram(Bitmap bitmap)
{
	background = bitmap;
	for (int i = 0; i < 256; i++)
	{
		rDistribution[i] = 0;
		bDistribution[i] = 0;
		gDistribution[i] = 0;
	}
}

void Histogram::calculateHistogram()
{
	char* temp_pixel_data = background.getPixels();
	for (int i = 0; i < background.getHeight(); i++)
	{
		for (int j = 0; j < background.getWidth(); j++)
		{
			int rValue = (int)temp_pixel_data[(i * background.getWidth() + j) * 3 + 2];
			int rValue = (int)temp_pixel_data[(i * background.getWidth() + j) * 3 + 2];
			int gValue = (int)temp_pixel_data[(i * background.getWidth() + j) * 3 + 1];
			int bValue = (int)temp_pixel_data[(i * background.getWidth() + j) * 3];

			if (rValue > 255) rValue = 255;
			if (rValue < 0) rValue = 0;
			if (gValue > 255) rValue = 255;
			if (gValue < 0) rValue = 0;
			if (bValue > 255) rValue = 255;
			if (bValue < 0) rValue = 0;


			bDistribution[bValue]++;
			gDistribution[gValue]++;
			rDistribution[rValue]++;
		}
	}
}

void Histogram::saveHistogram()
{
}
