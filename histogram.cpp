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
	int yyy = b.getHeight();
	int xxx = b.getWidth();
	for (int i = 0; i < yyy; i++)
	{
		for (int j = 0; j < xxx; j++)
		{
			int rValue = (int)temp_pixel_data[3*(i * b.getWidth() + j)  + 2];
			int gValue = (int)temp_pixel_data[3*(i * b.getWidth() + j)  + 1];
			int bValue = (int)temp_pixel_data[3*(i * b.getWidth() + j) ];

			bDistribution[bValue]++;
			gDistribution[gValue]++;
			rDistribution[rValue]++;
		}
	}
}

void Histogram::saveHistogram(std::string FilePath)
{
	std::size_t found = FilePath.find_last_of("/\\");
	std::string filepath = FilePath.substr(0, found) + "/preHistogram.bmp";
	std::ofstream file(filepath, std::ios::binary);

	file.write(this->background->getBitmap_header(), BMP_HEADER_SIZE);
	file.write(this->background->getDIB_header(), background->getOffsetToPixels() - BMP_HEADER_SIZE);
	//TO DO MODIFY BACKGROUND PIXEL TABLE AND SAVE IT TO FILE
	int histogramWidth = 256;
	background->castPixelCharArrayToUnsignedCharArray();
	char* temp = background->getPixels();
	for (int i = 0; i < histogramWidth; i++) 
	{
		int rColumnHeight = rDistribution[i];
		for (int j = 0; j < rColumnHeight; j++)
		{
			temp[3 * (i * background->getWidth() + j) + 2] = 255;
		}
		int bColumnHeight = bDistribution[i];
		for (int j = 0; j < bColumnHeight; j++)
		{
			temp[3 * (i * background->getWidth() + j) ] = 255;
		}
		int gColumnHeight = gDistribution[i];
		for (int j = 0; j < bColumnHeight; j++)
		{
			temp[3 * (i * background->getWidth() + j)+1] = 255;
		}
	}
	background->setPixels(temp);
	file.write(background->getPixels(), background->getFilesize()-background->getOffsetToPixels());
}
