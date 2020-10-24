#pragma once
#include<iostream>
#include "bitmap.h"
class Histogram
{
	Bitmap* background;
	int rDistribution[256];
	int bDistribution[256];
	int gDistribution[256];

public:
	Histogram(Bitmap &b);

	void normalizeDistributions();

	void calculateHistogram(Bitmap &b);

	void saveHistogram(std::string imageFilePath);

};

