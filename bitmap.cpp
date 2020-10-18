#include "bitmap.h"

unsigned int get_int(char* data, int offset)
{
	int value;
	std::memcpy(&value, &data[offset], sizeof(int));
	return value;
}

long GetFileSize(std::string filename)
{
	struct stat stat_buff;
	int rc = stat(filename.c_str(), &stat_buff);
	return rc == 0 ? stat_buff.st_size : -1;
}

bitmap::bitmap()
{
	bitmap_header = nullptr;
	DIB_header = nullptr;
	pixel_data = nullptr;
	width = 0;
	height = 0;
	offset_to_pixel_data = 0;
	filesize = 0;
	
}

bitmap::bitmap(std::string filePath)
{
	
	std::ifstream file(filePath);
	filesize = GetFileSize(filePath);

	bitmap_header = new char[BMP_HEADER_SIZE];
	file.read(bitmap_header, BMP_HEADER_SIZE);

	offset_to_pixel_data = get_int(bitmap_header, OFFSET_TO_bfOffBits);

	DIB_header = new char[offset_to_pixel_data - BMP_HEADER_SIZE];
	file.read(DIB_header, (offset_to_pixel_data - BMP_HEADER_SIZE));

	width = get_int(DIB_header, OFFSET_TO_WIDTH);
	height = get_int(DIB_header, OFFSET_TO_HEIGHT);

	pixel_data = new char[filesize];
	file.read(pixel_data, filesize);

}

void bitmap::saveToFile(std::string filePath)
{
	std::string imageFilePath = filePath.substr(0, filePath.find('.')) + "NOWY.BMP";
	std::ofstream file(imageFilePath);

	file.write(bitmap_header,BMP_HEADER_SIZE);
	file.write(DIB_header, (offset_to_pixel_data - BMP_HEADER_SIZE));
	file.write(pixel_data, filesize);


}
