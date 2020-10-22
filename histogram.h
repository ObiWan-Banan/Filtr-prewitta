#pragma once
#include<iostream>
#include "bitmap.h"
class Histogram
{
	Bitmap* background;
	int* rDistribution;
	int* bDistribution;
	int* gDistribution;

public:
	Histogram(Bitmap b);

	void calculateHistogram(Bitmap b);

	void saveHistogram(std::string imageFilePath);
};

