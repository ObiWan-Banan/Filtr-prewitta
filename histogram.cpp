#include "histogram.h"
#include<vector>

Histogram::Histogram(Bitmap &bitmap)
{
	background = &bitmap;

	for (int i = 0; i < 256; i++)
	{
		rDistribution[i] = 0;
		bDistribution[i] = 0;
		gDistribution[i] = 0;
	}
}

void Histogram::normalizeDistributions()
{
	int rMax = 0;
	int gMax = 0;
	int bMax = 0;
	int desiredMaximum = 300;
	for (int i = 0; i < 256; i++)
	{
		if (rDistribution[i] > rMax) rMax = rDistribution[i];
		if (gDistribution[i] > gMax) gMax = gDistribution[i];
		if (bDistribution[i] > bMax) bMax = bDistribution[i];
	}
	for (int j = 0; j < 256; j++)
	{
		rDistribution[j] = (rDistribution[j] * desiredMaximum) / rMax;
		gDistribution[j] = (gDistribution[j] * desiredMaximum) / gMax;
		bDistribution[j] = (bDistribution[j] * desiredMaximum) / bMax;
	}
}

void Histogram::calculateHistogram(Bitmap &b)
{
	

	
	int height = b.getHeight();
	int width = b.getWidth();
	char* temp_pixel_data = b.getPixels();
	
	//for (int y = 0; y <height; y++)
	//{
	//	for (int x = 0; x < width; x++)
	//	{/*
	//		int rValue = (int)*(temp_pixel_data + x + y * width + 2);
	//		int gValue = (int)*(temp_pixel_data + x + y *width + 1);
	//		int bValue = (int)*(temp_pixel_data + x + y *width);*/

	//		int rValue = (int)temp_pixel_data[3 * (y * width + x) + 2];
	//		int gValue = (int)temp_pixel_data[3 * (y * width + x) + 1];
	//		int bValue = (int)temp_pixel_data[3 * (y * width + x)];

	//		

	//		bDistribution[bValue]++;
	//		gDistribution[gValue]++;
	//		rDistribution[rValue]++;
	//	}
	//}
	std::vector<double> redDistribution(256);
	std::vector<double> greenDistribution(256);
	std::vector<double> blueDistribution(256);
	for (int i = 0; i < 3 * height * width; i += 3)
	{
		blueDistribution[temp_pixel_data[i]]++;
		greenDistribution[temp_pixel_data[i+1]]++;
		redDistribution[temp_pixel_data[i+2]]++;
	}
	normalizeDistributions();

}

void Histogram::saveHistogram(std::string FilePath)
{
	std::size_t found = FilePath.find_last_of("/\\");
	std::string filepath = FilePath.substr(0, found) + "/preHistogram.bmp";
	std::ofstream file(filepath, std::ios::binary);

	file.write(this->background->getBitmap_header(), BMP_HEADER_SIZE);
	file.write(this->background->getDIB_header(), background->getOffsetToPixels() - BMP_HEADER_SIZE);
	//TO DO MODIFY BACKGROUND PIXEL TABLE AND SAVE IT TO FILE
	int histogramWidth = background->getWidth();
	background->castPixelCharArrayToUnsignedCharArray();
	char* temp = background->getPixels();
	for (int i = 0; i < background->getFilesize()- background->getOffsetToPixels(); i++)
	{
		temp[i] = (unsigned char)temp;
	}
	for (int i = 0; i < histogramWidth; i++) 
	{
		
		int rColumnHeight = rDistribution[i];
		for (int j = 0; j < rColumnHeight; j++)
		{
			temp[3 * (j * histogramWidth +i) + 2] = 255;
		}
		/*int bColumnHeight = bDistribution[i];
		for (int j = 0; j < bColumnHeight; j++)
		{
			temp[3 * (j * background->getWidth() + i) ] = 255;
		}
		int gColumnHeight = gDistribution[i];
		for (int j = 0; j < bColumnHeight; j++)
		{
			temp[3 * (j * background->getWidth() + i)+1] = 255;
		}*/
	}
	file.write(temp, background->getFilesize()-background->getOffsetToPixels());
}
