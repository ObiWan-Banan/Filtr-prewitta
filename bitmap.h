#pragma once
#include<iostream>
#include<fstream>
#include<memory>
#include <QtCore\qstring.h>
#define BMP_HEADER_SIZE 14
#define OFFSET_TO_bfOffBits 10
#define OFFSET_TO_WIDTH 4
#define OFFSET_TO_HEIGHT 8

static std::string imageFilePath;
static int numberOfThreads;

long GetFileSize(std::string filename);

unsigned int get_int(char* data, int offset);


class Bitmap
{

	char* bitmap_header;
	char* DIB_header;
	char* pixel_data;
	int width;
	int height;
	int offset_to_pixel_data;
	int padding;
	long filesize;
	

public:
	
	Bitmap();
	
	Bitmap(std::string filePath);

	void castPixelCharArrayToUnsignedCharArray();

	int getWidth();

	int getHeight();

	char* getPixels();

	int getOffsetToPixels();

	long getFilesize();

	void saveToFile(std::string filePath);

	void makeMagic();

	void grayscale();

	void calculateHistogram();
	

};

