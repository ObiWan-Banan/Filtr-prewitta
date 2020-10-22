#include "bitmap.h"
#include<vector>

long GetFileSize(std::string filename)
{
	struct stat stat_buff;
	int rc = stat(filename.c_str(), &stat_buff);
	return rc == 0 ? stat_buff.st_size : -1;
}

unsigned int get_int(char* data, int offset)
{
	int value;
	std::memcpy(&value, &data[offset], sizeof(int));
	return value;
}

Bitmap::Bitmap()
{
	bitmap_header = nullptr;
	DIB_header = nullptr;
	pixel_data = nullptr;
	width = 0;
	height = 0;
	offset_to_pixel_data = 0;
	filesize = 0;
	padding = 0;
	
}

Bitmap::Bitmap(std::string filePath)
{
	
	std::ifstream file(filePath,std::ios::binary);
	filesize = GetFileSize(filePath);

	bitmap_header = new char[BMP_HEADER_SIZE];
	file.read(bitmap_header, BMP_HEADER_SIZE);

	offset_to_pixel_data = get_int(bitmap_header, OFFSET_TO_bfOffBits);

	DIB_header = new char[offset_to_pixel_data - BMP_HEADER_SIZE];
	file.read(DIB_header, (offset_to_pixel_data - BMP_HEADER_SIZE));

	width = get_int(DIB_header, OFFSET_TO_WIDTH);
	height = get_int(DIB_header, OFFSET_TO_HEIGHT);
	padding = (width * 3) % 4;
	if (padding) padding = 4 - padding;

	pixel_data = new  char[filesize - offset_to_pixel_data];
	char* temp = new char[padding];
	
	for (int i = 0; i < height; i++)
	{
		file.read(&pixel_data[i * width * 3], width * 3 * sizeof(char));
		
		file.read(temp, padding * sizeof(char));
	}
	
	//file.read(pixel_data, filesize-offset_to_pixel_data);

}

void Bitmap::castPixelCharArrayToUnsignedCharArray()
{
	for (int i = 0; i < filesize - offset_to_pixel_data; i++)
	{
		pixel_data[i] = (unsigned char)pixel_data[i];
	}
}

int Bitmap::getWidth() { return width; }

int Bitmap::getHeight() { return height; }

char* Bitmap::getPixels() { return pixel_data; }

int Bitmap::getOffsetToPixels() { return offset_to_pixel_data; }

long Bitmap::getFilesize() { return filesize; }

void Bitmap::saveToFile(std::string filePath)
{
	std::string imageFilePath = filePath.substr(0, filePath.find('.')) + "NOWY.BMP";
	std::ofstream file(imageFilePath,std::ios::binary);

	file.write(bitmap_header,BMP_HEADER_SIZE);
	file.write(DIB_header, (offset_to_pixel_data - BMP_HEADER_SIZE));
	//file.write(pixel_data, filesize - offset_to_pixel_data);
	char* temp = new char[padding];
	temp[0] = 0;
	temp[1] = 0;
	temp[2] = 0;

	for (int i = 0; i < height; i++)
	{
		file.write(&pixel_data[i*width *3], width * 3 * sizeof(char));
		file.write(temp, padding * sizeof(char));
	}
}

void Bitmap::makeMagic()
{
	/*for (int i = 0; i < filesize - offset_to_pixel_data; i++)
	{
		pixel_data[i] = (unsigned char)pixel_data[i];
	}*/
	unsigned char* temp = new unsigned char[filesize - offset_to_pixel_data];
	for (int i = 0; i < filesize - offset_to_pixel_data; i++)
	{
		temp[i] = pixel_data[i];
	}
	 char kernel[3][3];
	 kernel[0][0] = -1; kernel[0][1] = 0; kernel[0][2] = 1;
	 kernel[1][0] = -1; kernel[1][1] = 0; kernel[1][2] = 1;
	 kernel[2][0] = -1; kernel[2][1] = 0; kernel[2][2] = 1;

	 char kernely[3][3];
	kernely[0][0] = 1; kernely[0][1] = 1; kernely[0][2] = 1;
	kernely[1][0] = 0; kernely[1][1] = 0; kernely[1][2] = 0; 
	kernely[2][0] = -1; kernely[2][1] = -1; kernely[2][2] = -1;

	for (int Y = 0; Y <= (height - 1); Y++) {
		for (int X = 0; X <= (width - 1); X++) {
			int sumXb = 0;
			int sumYb = 0;
			int sumXg = 0;
			int sumYg = 0;
			int sumXr = 0;
			int sumYr = 0;
			int SUMb = 0;
			int SUMg = 0;
			int SUMr = 0;

			
			if (Y == 0 || Y == height - 1) {
				SUMb = 0; SUMg = 0; SUMr = 0;
			}
			else if (X == 0 || X == width - 1) {
				SUMb = 0; SUMg = 0; SUMr = 0;	
			}
			else
			{
				for (int I = -1; I <= 1; I++) {
					for (int J = -1; J <= 1; J++) {
						sumXb = sumXb + pixel_data[3*(X+I+(Y+J)*width)] * kernel[I + 1][J + 1];
						sumXg = sumXg + pixel_data[3*(X + I + (Y + J) * width)+1] * kernel[I + 1][J + 1];
						sumXr = sumXr + pixel_data[3*(X + I + (Y + J) * width)+2] * kernel[I + 1][J + 1];
					}
				}
				for (int I = -1; I <= 1; I++) {
					for (int J = -1; J <= 1; J++) {
						sumYb = sumYb + pixel_data[3*(X + I + (Y + J) * width)] * kernely[I + 1][J + 1];
						sumYg = sumYg + pixel_data[3*(X + I + (Y + J) * width)+1] * kernely[I + 1][J + 1];
						sumYr = sumYr + pixel_data[3*(X + I + (Y + J) * width)+2] * kernely[I + 1][J + 1];
					}
				}

				SUMb = sqrt((sumXb * sumXb) + (sumYb * sumYb));					
				SUMg = sqrt((sumXg * sumXg) + (sumYg * sumYg));		
				SUMr = sqrt((sumXr * sumXr) + (sumYr * sumYr));
			}
			if (SUMb > 255) SUMb = 255;
			if (SUMg > 255) SUMg = 255;
			if (SUMr > 255) SUMr = 255;
			if (SUMb < 0) SUMb = 0;
			if (SUMg < 0) SUMg = 0;
			if (SUMr < 0) SUMr = 0;

			temp[3*(X + Y * width)] = SUMb;
			temp[3*(X + Y * width)+1] = SUMg;
			temp[3*(X + Y * width)+2] = SUMr;
		}
	}
	for (int i = 0; i < filesize - offset_to_pixel_data; i++)
	{
		pixel_data[i] = temp[i];
	}
	}

void Bitmap::grayscale()
{
	int r, g, b;
	unsigned char gray;
	/*for (int i = 0; i < filesize - offset_to_pixel_data; i++)
	{
		pixel_data[i] = (unsigned char)pixel_data[i];
	}*/
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			r = (int)pixel_data[(i * width + j) * 3 + 2];
			g = (int)pixel_data[(i * width + j) * 3 + 1];
			b = (int)pixel_data[(i * width + j) * 3 ];

			r = r * 0.299;
			g = g * 0.587;
			b = b * 0.144;

			gray =(unsigned char) (r + g + b);

			pixel_data[(i * width + j) * 3] = gray;
			pixel_data[(i * width + j) * 3+1] = gray;
			pixel_data[(i * width + j) * 3+2] = gray;
		}
	}
}

void Bitmap::calculateHistogram()
{
	int r[256];
	int g[256];
	int b[256];
	for (int i = 0; i < filesize - offset_to_pixel_data; i++)
	{
		pixel_data[i] = (unsigned char)pixel_data[i];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int rValue = (int)pixel_data[(i * width + j) * 3+2];
			int gValue = (int)pixel_data[(i * width + j) * 3 + 1];
			int bValue = (int)pixel_data[(i * width + j) * 3];

			if (rValue > 255) rValue = 255;
			if (rValue < 0) rValue = 0;
			if (gValue > 255) rValue = 255;
			if (gValue < 0) rValue = 0;
			if (bValue > 255) rValue = 255;
			if (bValue < 0) rValue = 0;
			

			b[bValue]++;
			g[gValue]++;
			r[rValue]++;
		}
	}
}
	

