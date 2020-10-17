#pragma once
#include<iostream>
#include<fstream>
#include<memory>
#define BMP_HEADER_SIZE 14
#define OFFSET_TO_bfOffBits 10
#define OFFSET_TO_WIDTH 4
#define OFFSET_TO_HEIGHT 8
#define GB 1024*1024*1024

unsigned int get_int(char* data, int offset);

class bitmap
{
	char* bitmap_header;
	char* DIB_header;
	char* pixel_data;
	int width;
	int height;
	int offset_to_pixel_data;
	std::string imageFilePath;

public:
	bitmap();
	
	bitmap(std::string filePath);
	
	

};

