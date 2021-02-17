/*
Filtr Prewitta z histogramem
Rafa³ Œwiderski
Rok akademicki 2020/2021
wersja 1.0
*/

#include "pch.h"
#include <Windows.h>
#include "prewitt.h"
#include <iostream>

void prewittFilter(char* inputArray, char* outputArray, int width,int start_height,int stop_height)
{
	char kernel[3][3];
	kernel[0][0] = -1; kernel[0][1] = 0; kernel[0][2] = 1;
	kernel[1][0] = -1; kernel[1][1] = 0; kernel[1][2] = 1;
	kernel[2][0] = -1; kernel[2][1] = 0; kernel[2][2] = 1;
	
	char kernely[3][3];
	kernely[0][0] = 1; kernely[0][1] = 1; kernely[0][2] = 1;
	kernely[1][0] = 0; kernely[1][1] = 0; kernely[1][2] = 0;
	kernely[2][0] = -1; kernely[2][1] = -1; kernely[2][2] = -1;

	for (int Y = start_height; Y <= (stop_height - 2); Y++) {
		for (int X = 0; X <= (width - 2); X++) {
			int sumXb = 0;
			int sumYb = 0;
			int sumXg = 0;
			int sumYg = 0;
			int sumXr = 0;
			int sumYr = 0;
			int SUMb = 0;
			int SUMg = 0;
			int SUMr = 0;


			if (Y == 0 || Y >= stop_height - 1) 
			{
				SUMb = 0; SUMg = 0; SUMr = 0;
			}
			else if (X == 0 || X >= width - 1)
			{
				SUMb = 0; SUMg = 0; SUMr = 0;
			}
			else
			{
				for (int I = -1; I <= 1; I++) {
					for (int J = -1; J <= 1; J++) 
					{
						unsigned char pixelBValue = inputArray[3 * (X + I + (Y + J) * width)];
						unsigned char pixelGValue = inputArray[3 * (X + I + (Y + J) * width) + 1];
						unsigned char pixelRValue = inputArray[3 * (X + I + (Y + J) * width) + 2];

						char kernelValue= kernel[I + 1][J + 1];
						char kernelyValue= kernely[I + 1][J + 1];

						sumXb += pixelBValue * kernelValue;
						sumXg += pixelGValue * kernelValue;
						sumXr += pixelRValue * kernelValue;

						sumYb += pixelBValue * kernelyValue;
						sumYg += pixelGValue * kernelyValue;
						sumYr += pixelRValue * kernelyValue;
					}
				}
				SUMb = sqrt((sumXb * sumXb) + (sumYb * sumYb));
				SUMg = sqrt((sumXg * sumXg) + (sumYg * sumYg));
				SUMr = sqrt((sumXr * sumXr) + (sumYr * sumYr));

				if (SUMb > 255) SUMb = 255;
				if (SUMg > 255) SUMg = 255;
				if (SUMr > 255) SUMr = 255;
				if (SUMb < 20) SUMb = 0;
				if (SUMg < 20) SUMg = 0;
				if (SUMr < 20) SUMr = 0;
			}
			outputArray[3 * (X + Y * width)] = SUMb;
			outputArray[3 * (X + Y * width) + 1] = SUMg;
			outputArray[3 * (X + Y * width) + 2] = SUMr;
		}
	}
}