#ifndef IMAGE
#define IMAGE

#include <fstream>
#include <iostream>
#include <vector>
#include <string>



void write_ppm(
	const std::string & filename,
	const std::vector<unsigned char> & data,
	const int width,
	const int height,
	const int num_channels)
{
	std::ofstream file;
	file.open(filename);
	if(num_channels == 3)
	{
		file << "P3" << std::endl;
		file << width << " " << height << std::endl;
		for(int h = 0; h < height; h++)
		{
			for(int w = 0; w < width; w++)
			{
				int ptr = 3 * (width * h + w);
				file << std::to_string(data[ptr+2]) << " " << std::to_string(data[ptr]) << " " << std::to_string(data[ptr+1]) << " ";
			}
			file << std::endl;
		}
	}
	else
	{
		file << "P2" << std::endl;
		file << width << " " << height << std::endl;
		for(int h = 0; h < height; h++)
		{
			for(int w = 0; w < width; w++)
			{
				int ptr = width * h + w;
				file << std::to_string(data[ptr]) << " ";
			}
			file << std::endl;
		}
	}
	file.close();
}

#endif