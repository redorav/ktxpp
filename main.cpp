#include "ktxpp.h"

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

int main()
{
	std::vector<std::string> paths;
	
	//paths.push_back("test/test_rgba8u.ktx");
	//paths.push_back("test/test_rgb8u.ktx");
	//paths.push_back("test/test_rg8u.ktx");
	//paths.push_back("test/test_r8u.ktx");

	//paths.push_back("test/test_rgba16ui.ktx");

	// Packed
	paths.push_back("test/test_rg11b10f.ktx");

	// BCn
	paths.push_back("test/test_BC1.ktx");
	paths.push_back("test/test_BC2.ktx");
	paths.push_back("test/test_BC3.ktx");

	// PVRTC
	paths.push_back("test/test_PVRTC1_2.ktx");
	paths.push_back("test/test_PVRTC1_2_RGB.ktx");
	paths.push_back("test/test_PVRTC1_4.ktx");
	paths.push_back("test/test_PVRTC1_4_RGB.ktx");
	paths.push_back("test/test_PVRTC2_2.ktx");
	paths.push_back("test/test_PVRTC2_4.ktx");
	paths.push_back("test/test_RGBE9995.ktx");

	// ETC
	paths.push_back("test/test_ETC1.ktx");
	paths.push_back("test/test_ETC2_RGB.ktx");
	paths.push_back("test/test_ETC2_RGBA.ktx");
	paths.push_back("test/test_ETC2_RGBA_A1.ktx");

	// ASTC
	paths.push_back("test/test_ASTC_4x4.ktx");
	paths.push_back("test/test_ASTC_5x4.ktx");
	paths.push_back("test/test_ASTC_5x5.ktx");
	paths.push_back("test/test_ASTC_6x5.ktx");
	paths.push_back("test/test_ASTC_6x6.ktx");
	paths.push_back("test/test_ASTC_8x5.ktx");
	paths.push_back("test/test_ASTC_8x6.ktx");
	paths.push_back("test/test_ASTC_8x8.ktx");
	paths.push_back("test/test_ASTC_10x5.ktx");
	paths.push_back("test/test_ASTC_10x6.ktx");
	paths.push_back("test/test_ASTC_10x8.ktx");
	paths.push_back("test/test_ASTC_10x10.ktx");
	paths.push_back("test/test_ASTC_12x10.ktx");
	paths.push_back("test/test_ASTC_12x12.ktx");

	for (uint32_t i = 0; i < paths.size(); ++i)
	{
		const std::string& path = paths[i];

		FILE* fh = fopen(path.c_str(), "rb");

		if(fh)
		{
			int size;
			fseek(fh, 0, SEEK_END);
			size = ftell(fh);
			rewind(fh);

			unsigned char* test = new unsigned char[size];

			fread(test, sizeof(*test), size, fh);

			ktxpp::Descriptor desc;

			int dSize = sizeof(ktxpp::Descriptor);

			unsigned char* decodedImage = ktxpp::decode_header(test, desc);

			fclose(fh);
		}
	}
}