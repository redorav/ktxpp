#pragma once

#include <cstdint>
#include <assert.h>

#if (__cpp_constexpr == 201304) || (_MSC_VER > 1900)
#define ktxpp_constexpr constexpr
#else
#define ktxpp_constexpr const
#endif

namespace ktxpp
{
	namespace internal
	{
		static ktxpp_constexpr uint32_t KTX_MAGIC      = 0x20534444;

		// https://www.khronos.org/opengles/sdk/tools/KTX/file_format_spec/
		struct HeaderKTX
		{
			char identifier[12];
			uint32_t endianness;
			uint32_t glType;
			uint32_t glTypeSize;
			uint32_t glFormat;
			uint32_t glInternalFormat;
			uint32_t glBaseInternalFormat; // e.g. GL_RGBA, GL_BGRA, GL_RED
			uint32_t pixelWidth;
			uint32_t pixelHeight;
			uint32_t pixelDepth;
			uint32_t numberOfArrayElements;
			uint32_t numberOfFaces;
			uint32_t numberOfMipmapLevels;
			uint32_t bytesOfKeyValueData;
		};
	}

	// Compressed textures: table 8.14 of spec
	// Uncompressed textures: table 8.12 & 8.13 of spec
	enum GLInternalFormat
	{
		UNKNOWN	                                       = 0,

		// 8 bits per component
		GL_R8                                          = 0x8229,
		GL_RG8                                         = 0x822B,
		GL_RGB8                                        = 0x8051,
		GL_RGBA8                                       = 0x8058,

		GL_R8_SNORM                                    = 0x8F94,
		GL_RG8_SNORM                                   = 0x8F95,
		GL_RGB8_SNORM                                  = 0x8F96,
		GL_RGBA8_SNORM                                 = 0x8F97,

		GL_R8UI                                        = 0x8232,
		GL_RG8UI                                       = 0x8238,
		GL_RGB8UI                                      = 0x8D7D,
		GL_RGBA8UI                                     = 0x8D7C,

		GL_R8I                                         = 0x8231,
		GL_RG8I                                        = 0x8237,
		GL_RGB8I                                       = 0x8D8F,
		GL_RGBA8I                                      = 0x8D8E,

		GL_SR8                                         = 0x8FBD,
		GL_SRG8                                        = 0x8FBE,
		GL_SRGB8                                       = 0x8C41,
		GL_SRGB8_ALPHA8                                = 0x8C43,

		// 16 bits per component
		GL_R16                                         = 0x822A,
		GL_RG16                                        = 0x822C,
		GL_RGB16                                       = 0x8054,
		GL_RGBA16                                      = 0x805B,

		GL_R16_SNORM                                   = 0x8F98,
		GL_RG16_SNORM                                  = 0x8F99,
		GL_RGB16_SNORM                                 = 0x8F9A,
		GL_RGBA16_SNORM                                = 0x8F9B,

		GL_R16UI                                       = 0x8234,
		GL_RG16UI                                      = 0x823A,
		GL_RGB16UI                                     = 0x8D77,
		GL_RGBA16UI                                    = 0x8D76,

		GL_R16I                                        = 0x8233,
		GL_RG16I                                       = 0x8239,
		GL_RGB16I                                      = 0x8D89,
		GL_RGBA16I                                     = 0x8D88,

		GL_R16F                                        = 0x822D,
		GL_RG16F                                       = 0x822F,
		GL_RGB16F                                      = 0x881B,
		GL_RGBA16F                                     = 0x881A,

		// 32 bits per component
		GL_R32UI                                       = 0x8236,
		GL_RG32UI                                      = 0x823C,
		GL_RGB32UI                                     = 0x8D71,
		GL_RGBA32UI                                    = 0x8D70,

		GL_R32I                                        = 0x8235,
		GL_RG32I                                       = 0x823B,
		GL_RGB32I                                      = 0x8D83,
		GL_RGBA32I                                     = 0x8D82,

		GL_R32F                                        = 0x822E,
		GL_RG32F                                       = 0x8230,
		GL_RGB32F                                      = 0x8815,
		GL_RGBA32F                                     = 0x8814,

		// Packed
		GL_R3_G3_B2                                    = 0x2A10,
		GL_RGB4                                        = 0x804F,
		GL_RGB5                                        = 0x8050,
		GL_RGB565                                      = 0x8D62,
		GL_RGB10                                       = 0x8052,
		GL_RGB12                                       = 0x8053,
		GL_RGBA2                                       = 0x8055,
		GL_RGBA4                                       = 0x8056,
		GL_RGBA12                                      = 0x805A,
		GL_RGB5_A1                                     = 0x8057,
		GL_RGB10_A2                                    = 0x8059,
		GL_RGB10_A2UI                                  = 0x906F,
		GL_R11F_G11F_B10F                              = 0x8C3A,
		GL_RGB9_E5                                     = 0x8C3D,
		
		// S3TX/DXT/BC
		GL_COMPRESSED_RGB_S3TC_DXT1                    = 0x83F0,
		GL_COMPRESSED_RGBA_S3TC_DXT1                   = 0x83F1,
		GL_COMPRESSED_RGBA_S3TC_DXT3                   = 0x83F2,
		GL_COMPRESSED_RGBA_S3TC_DXT5                   = 0x83F3,

		GL_COMPRESSED_SRGB_S3TC_DXT1                   = 0x8C4C,
		GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1             = 0x8C4D,
		GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3             = 0x8C4E,
		GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5             = 0x8C4F,

		GL_COMPRESSED_LUMINANCE_LATC1                  = 0x8C70,
		GL_COMPRESSED_LUMINANCE_ALPHA_LATC2            = 0x8C72,
		GL_COMPRESSED_SIGNED_LUMINANCE_LATC1           = 0x8C71,
		GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2     = 0x8C73,
		GL_COMPRESSED_RED_RGTC1                        = 0x8DBB,
		GL_COMPRESSED_RG_RGTC2                         = 0x8DBD,
		GL_COMPRESSED_SIGNED_RED_RGTC1                 = 0x8DBC,
		GL_COMPRESSED_SIGNED_RG_RGTC2                  = 0x8DBE,
		GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT            = 0x8E8E,
		GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT          = 0x8E8F,
		GL_COMPRESSED_RGBA_BPTC_UNORM                  = 0x8E8C,
		GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM            = 0x8E8D,

		// ETC
		GL_ETC1_RGB8_OES                               = 0x8D64,
		GL_COMPRESSED_RGB8_ETC2	                       = 0x9274,
		GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2    = 0x9276,
		GL_COMPRESSED_RGBA8_ETC2_EAC                   = 0x9278,
		GL_COMPRESSED_SRGB8_ETC2                       = 0x9275,
		GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2   = 0x9277,
		GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC            = 0x9279,
		GL_COMPRESSED_R11_EAC                          = 0x9270,
		GL_COMPRESSED_RG11_EAC                         = 0x9272,
		GL_COMPRESSED_SIGNED_R11_EAC                   = 0x9271,
		GL_COMPRESSED_SIGNED_RG11_EAC                  = 0x9273,

		// PVRTC
		GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG             = 0x8C01,
		GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG             = 0x8C00,
		GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG            = 0x8C03,
		GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG            = 0x8C02,
		GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG            = 0x9137,
		GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG            = 0x9138,
		GL_COMPRESSED_SRGB_PVRTC_2BPPV1                = 0x8A54,
		GL_COMPRESSED_SRGB_PVRTC_4BPPV1                = 0x8A55,
		GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1          = 0x8A56,
		GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1          = 0x8A57,
		GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG      = 0x93F0,
		GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG      = 0x93F1,

		// ASTC
		GL_COMPRESSED_RGBA_ASTC_4x4                    = 0x93B0,
		GL_COMPRESSED_RGBA_ASTC_5x4                    = 0x93B1,
		GL_COMPRESSED_RGBA_ASTC_5x5                    = 0x93B2,
		GL_COMPRESSED_RGBA_ASTC_6x5                    = 0x93B3,
		GL_COMPRESSED_RGBA_ASTC_6x6                    = 0x93B4,
		GL_COMPRESSED_RGBA_ASTC_8x5                    = 0x93B5,
		GL_COMPRESSED_RGBA_ASTC_8x6                    = 0x93B6,
		GL_COMPRESSED_RGBA_ASTC_8x8                    = 0x93B7,
		GL_COMPRESSED_RGBA_ASTC_10x5                   = 0x93B8,
		GL_COMPRESSED_RGBA_ASTC_10x6                   = 0x93B9,
		GL_COMPRESSED_RGBA_ASTC_10x8                   = 0x93BA,
		GL_COMPRESSED_RGBA_ASTC_10x10                  = 0x93BB,
		GL_COMPRESSED_RGBA_ASTC_12x10                  = 0x93BC,
		GL_COMPRESSED_RGBA_ASTC_12x12                  = 0x93BD,

		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4            = 0x93D0,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4            = 0x93D1,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5            = 0x93D2,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5            = 0x93D3,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6            = 0x93D4,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5            = 0x93D5,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6            = 0x93D6,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8            = 0x93D7,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5           = 0x93D8,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6           = 0x93D9,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8           = 0x93DA,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10          = 0x93DB,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10          = 0x93DC,
		GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12          = 0x93DD,

		FORCE_UINT                                     = 0xffffffff
	};

	// Table 8.2 of spec
	enum GLType
	{
		GL_BYTE                           = 0x1400,
		GL_UNSIGNED_BYTE                  = 0x1401,
		GL_SHORT                          = 0x1402,
		GL_UNSIGNED_SHORT                 = 0x1403,
		GL_INT                            = 0x1404,
		GL_UNSIGNED_INT                   = 0x1405,
		GL_INT64                          = 0x140E,
		GL_UNSIGNED_INT64                 = 0x140F,
		GL_HALF_FLOAT                     = 0x140B,
		GL_HALF_FLOAT_OES                 = 0x8D61,
		GL_FLOAT                          = 0x1406,
		GL_DOUBLE                         = 0x140A,
		GL_UNSIGNED_BYTE_3_3_2            = 0x8032,
		GL_UNSIGNED_BYTE_2_3_3_REV        = 0x8362,
		GL_UNSIGNED_SHORT_5_6_5           = 0x8363,
		GL_UNSIGNED_SHORT_5_6_5_REV       = 0x8364,
		GL_UNSIGNED_SHORT_4_4_4_4         = 0x8033,
		GL_UNSIGNED_SHORT_4_4_4_4_REV     = 0x8365,
		GL_UNSIGNED_SHORT_5_5_5_1         = 0x8034,
		GL_UNSIGNED_SHORT_1_5_5_5_REV     = 0x8366,
		GL_UNSIGNED_INT_8_8_8_8           = 0x8035,
		GL_UNSIGNED_INT_8_8_8_8_REV       = 0x8367,
		GL_UNSIGNED_INT_10_10_10_2        = 0x8036,
		GL_UNSIGNED_INT_2_10_10_10_REV    = 0x8368,
		GL_UNSIGNED_INT_10F_11F_11F_REV   = 0x8C3B,
		GL_UNSIGNED_INT_5_9_9_9_REV       = 0x8C3E,
		GL_UNSIGNED_INT_24_8              = 0x84FA,
		GL_FLOAT_32_UNSIGNED_INT_24_8_REV = 0x8DAD
	};

	// Table 8.3 of spec
	enum GLFormat
	{
		GL_RED                     = 0x1903,
		GL_GREEN                   = 0x1904,
		GL_BLUE                    = 0x1905,
		GL_ALPHA                   = 0x1906,
		GL_LUMINANCE               = 0x1909,
		GL_SLUMINANCE              = 0x8C46,
		GL_LUMINANCE_ALPHA         = 0x190A,
		GL_SLUMINANCE_ALPHA        = 0x8C44,
		GL_INTENSITY               = 0x8049,
		GL_RG                      = 0x8227,
		GL_RGB                     = 0x1907,
		GL_BGR                     = 0x80E0,
		GL_RGBA                    = 0x1908,
		GL_BGRA                    = 0x80E1,
		GL_RED_INTEGER             = 0x8D94,
		GL_GREEN_INTEGER           = 0x8D95,
		GL_BLUE_INTEGER            = 0x8D96,
		GL_ALPHA_INTEGER           = 0x8D97,
		GL_LUMINANCE_INTEGER       = 0x8D9C,
		GL_LUMINANCE_ALPHA_INTEGER = 0x8D9D,
		GL_RG_INTEGER              = 0x8228,
		GL_RGB_INTEGER             = 0x8D98,
		GL_BGR_INTEGER             = 0x8D9A,
		GL_RGBA_INTEGER            = 0x8D99,
		GL_BGRA_INTEGER            = 0x8D9B,
		GL_COLOR_INDEX             = 0x1900,
		GL_STENCIL_INDEX           = 0x1901,
		GL_DEPTH_COMPONENT         = 0x1902,
		GL_DEPTH_STENCIL           = 0x84F9
	};

	enum VkFormat
	{
		VK_FORMAT_UNDEFINED                                  = 0,
		VK_FORMAT_R4G4_UNORM_PACK8                           = 1,
		VK_FORMAT_R4G4B4A4_UNORM_PACK16                      = 2,
		VK_FORMAT_B4G4R4A4_UNORM_PACK16                      = 3,
		VK_FORMAT_R5G6B5_UNORM_PACK16                        = 4,
		VK_FORMAT_B5G6R5_UNORM_PACK16                        = 5,
		VK_FORMAT_R5G5B5A1_UNORM_PACK16                      = 6,
		VK_FORMAT_B5G5R5A1_UNORM_PACK16                      = 7,
		VK_FORMAT_A1R5G5B5_UNORM_PACK16                      = 8,
		VK_FORMAT_R8_UNORM                                   = 9,
		VK_FORMAT_R8_SNORM                                   = 10,
		VK_FORMAT_R8_USCALED                                 = 11,
		VK_FORMAT_R8_SSCALED                                 = 12,
		VK_FORMAT_R8_UINT                                    = 13,
		VK_FORMAT_R8_SINT                                    = 14,
		VK_FORMAT_R8_SRGB                                    = 15,
		VK_FORMAT_R8G8_UNORM                                 = 16,
		VK_FORMAT_R8G8_SNORM                                 = 17,
		VK_FORMAT_R8G8_USCALED                               = 18,
		VK_FORMAT_R8G8_SSCALED                               = 19,
		VK_FORMAT_R8G8_UINT                                  = 20,
		VK_FORMAT_R8G8_SINT                                  = 21,
		VK_FORMAT_R8G8_SRGB                                  = 22,
		VK_FORMAT_R8G8B8_UNORM                               = 23,
		VK_FORMAT_R8G8B8_SNORM                               = 24,
		VK_FORMAT_R8G8B8_USCALED                             = 25,
		VK_FORMAT_R8G8B8_SSCALED                             = 26,
		VK_FORMAT_R8G8B8_UINT                                = 27,
		VK_FORMAT_R8G8B8_SINT                                = 28,
		VK_FORMAT_R8G8B8_SRGB                                = 29,
		VK_FORMAT_B8G8R8_UNORM                               = 30,
		VK_FORMAT_B8G8R8_SNORM                               = 31,
		VK_FORMAT_B8G8R8_USCALED                             = 32,
		VK_FORMAT_B8G8R8_SSCALED                             = 33,
		VK_FORMAT_B8G8R8_UINT                                = 34,
		VK_FORMAT_B8G8R8_SINT                                = 35,
		VK_FORMAT_B8G8R8_SRGB                                = 36,
		VK_FORMAT_R8G8B8A8_UNORM                             = 37,
		VK_FORMAT_R8G8B8A8_SNORM                             = 38,
		VK_FORMAT_R8G8B8A8_USCALED                           = 39,
		VK_FORMAT_R8G8B8A8_SSCALED                           = 40,
		VK_FORMAT_R8G8B8A8_UINT                              = 41,
		VK_FORMAT_R8G8B8A8_SINT                              = 42,
		VK_FORMAT_R8G8B8A8_SRGB                              = 43,
		VK_FORMAT_B8G8R8A8_UNORM                             = 44,
		VK_FORMAT_B8G8R8A8_SNORM                             = 45,
		VK_FORMAT_B8G8R8A8_USCALED                           = 46,
		VK_FORMAT_B8G8R8A8_SSCALED                           = 47,
		VK_FORMAT_B8G8R8A8_UINT                              = 48,
		VK_FORMAT_B8G8R8A8_SINT                              = 49,
		VK_FORMAT_B8G8R8A8_SRGB                              = 50,
		VK_FORMAT_A8B8G8R8_UNORM_PACK32                      = 51,
		VK_FORMAT_A8B8G8R8_SNORM_PACK32                      = 52,
		VK_FORMAT_A8B8G8R8_USCALED_PACK32                    = 53,
		VK_FORMAT_A8B8G8R8_SSCALED_PACK32                    = 54,
		VK_FORMAT_A8B8G8R8_UINT_PACK32                       = 55,
		VK_FORMAT_A8B8G8R8_SINT_PACK32                       = 56,
		VK_FORMAT_A8B8G8R8_SRGB_PACK32                       = 57,
		VK_FORMAT_A2R10G10B10_UNORM_PACK32                   = 58,
		VK_FORMAT_A2R10G10B10_SNORM_PACK32                   = 59,
		VK_FORMAT_A2R10G10B10_USCALED_PACK32                 = 60,
		VK_FORMAT_A2R10G10B10_SSCALED_PACK32                 = 61,
		VK_FORMAT_A2R10G10B10_UINT_PACK32                    = 62,
		VK_FORMAT_A2R10G10B10_SINT_PACK32                    = 63,
		VK_FORMAT_A2B10G10R10_UNORM_PACK32                   = 64,
		VK_FORMAT_A2B10G10R10_SNORM_PACK32                   = 65,
		VK_FORMAT_A2B10G10R10_USCALED_PACK32                 = 66,
		VK_FORMAT_A2B10G10R10_SSCALED_PACK32                 = 67,
		VK_FORMAT_A2B10G10R10_UINT_PACK32                    = 68,
		VK_FORMAT_A2B10G10R10_SINT_PACK32                    = 69,
		VK_FORMAT_R16_UNORM                                  = 70,
		VK_FORMAT_R16_SNORM                                  = 71,
		VK_FORMAT_R16_USCALED                                = 72,
		VK_FORMAT_R16_SSCALED                                = 73,
		VK_FORMAT_R16_UINT                                   = 74,
		VK_FORMAT_R16_SINT                                   = 75,
		VK_FORMAT_R16_SFLOAT                                 = 76,
		VK_FORMAT_R16G16_UNORM                               = 77,
		VK_FORMAT_R16G16_SNORM                               = 78,
		VK_FORMAT_R16G16_USCALED                             = 79,
		VK_FORMAT_R16G16_SSCALED                             = 80,
		VK_FORMAT_R16G16_UINT                                = 81,
		VK_FORMAT_R16G16_SINT                                = 82,
		VK_FORMAT_R16G16_SFLOAT                              = 83,
		VK_FORMAT_R16G16B16_UNORM                            = 84,
		VK_FORMAT_R16G16B16_SNORM                            = 85,
		VK_FORMAT_R16G16B16_USCALED                          = 86,
		VK_FORMAT_R16G16B16_SSCALED                          = 87,
		VK_FORMAT_R16G16B16_UINT                             = 88,
		VK_FORMAT_R16G16B16_SINT                             = 89,
		VK_FORMAT_R16G16B16_SFLOAT                           = 90,
		VK_FORMAT_R16G16B16A16_UNORM                         = 91,
		VK_FORMAT_R16G16B16A16_SNORM                         = 92,
		VK_FORMAT_R16G16B16A16_USCALED                       = 93,
		VK_FORMAT_R16G16B16A16_SSCALED                       = 94,
		VK_FORMAT_R16G16B16A16_UINT                          = 95,
		VK_FORMAT_R16G16B16A16_SINT                          = 96,
		VK_FORMAT_R16G16B16A16_SFLOAT                        = 97,
		VK_FORMAT_R32_UINT                                   = 98,
		VK_FORMAT_R32_SINT                                   = 99,
		VK_FORMAT_R32_SFLOAT                                 = 100,
		VK_FORMAT_R32G32_UINT                                = 101,
		VK_FORMAT_R32G32_SINT                                = 102,
		VK_FORMAT_R32G32_SFLOAT                              = 103,
		VK_FORMAT_R32G32B32_UINT                             = 104,
		VK_FORMAT_R32G32B32_SINT                             = 105,
		VK_FORMAT_R32G32B32_SFLOAT                           = 106,
		VK_FORMAT_R32G32B32A32_UINT                          = 107,
		VK_FORMAT_R32G32B32A32_SINT                          = 108,
		VK_FORMAT_R32G32B32A32_SFLOAT                        = 109,
		VK_FORMAT_R64_UINT                                   = 110,
		VK_FORMAT_R64_SINT                                   = 111,
		VK_FORMAT_R64_SFLOAT                                 = 112,
		VK_FORMAT_R64G64_UINT                                = 113,
		VK_FORMAT_R64G64_SINT                                = 114,
		VK_FORMAT_R64G64_SFLOAT                              = 115,
		VK_FORMAT_R64G64B64_UINT                             = 116,
		VK_FORMAT_R64G64B64_SINT                             = 117,
		VK_FORMAT_R64G64B64_SFLOAT                           = 118,
		VK_FORMAT_R64G64B64A64_UINT                          = 119,
		VK_FORMAT_R64G64B64A64_SINT                          = 120,
		VK_FORMAT_R64G64B64A64_SFLOAT                        = 121,
		VK_FORMAT_B10G11R11_UFLOAT_PACK32                    = 122,
		VK_FORMAT_E5B9G9R9_UFLOAT_PACK32                     = 123,
		VK_FORMAT_D16_UNORM                                  = 124,
		VK_FORMAT_X8_D24_UNORM_PACK32                        = 125,
		VK_FORMAT_D32_SFLOAT                                 = 126,
		VK_FORMAT_S8_UINT                                    = 127,
		VK_FORMAT_D16_UNORM_S8_UINT                          = 128,
		VK_FORMAT_D24_UNORM_S8_UINT                          = 129,
		VK_FORMAT_D32_SFLOAT_S8_UINT                         = 130,
		VK_FORMAT_BC1_RGB_UNORM_BLOCK                        = 131,
		VK_FORMAT_BC1_RGB_SRGB_BLOCK                         = 132,
		VK_FORMAT_BC1_RGBA_UNORM_BLOCK                       = 133,
		VK_FORMAT_BC1_RGBA_SRGB_BLOCK                        = 134,
		VK_FORMAT_BC2_UNORM_BLOCK                            = 135,
		VK_FORMAT_BC2_SRGB_BLOCK                             = 136,
		VK_FORMAT_BC3_UNORM_BLOCK                            = 137,
		VK_FORMAT_BC3_SRGB_BLOCK                             = 138,
		VK_FORMAT_BC4_UNORM_BLOCK                            = 139,
		VK_FORMAT_BC4_SNORM_BLOCK                            = 140,
		VK_FORMAT_BC5_UNORM_BLOCK                            = 141,
		VK_FORMAT_BC5_SNORM_BLOCK                            = 142,
		VK_FORMAT_BC6H_UFLOAT_BLOCK                          = 143,
		VK_FORMAT_BC6H_SFLOAT_BLOCK                          = 144,
		VK_FORMAT_BC7_UNORM_BLOCK                            = 145,
		VK_FORMAT_BC7_SRGB_BLOCK                             = 146,
		VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK                    = 147,
		VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK                     = 148,
		VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK                  = 149,
		VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK                   = 150,
		VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK                  = 151,
		VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK                   = 152,
		VK_FORMAT_EAC_R11_UNORM_BLOCK                        = 153,
		VK_FORMAT_EAC_R11_SNORM_BLOCK                        = 154,
		VK_FORMAT_EAC_R11G11_UNORM_BLOCK                     = 155,
		VK_FORMAT_EAC_R11G11_SNORM_BLOCK                     = 156,
		VK_FORMAT_ASTC_4x4_UNORM_BLOCK                       = 157,
		VK_FORMAT_ASTC_4x4_SRGB_BLOCK                        = 158,
		VK_FORMAT_ASTC_5x4_UNORM_BLOCK                       = 159,
		VK_FORMAT_ASTC_5x4_SRGB_BLOCK                        = 160,
		VK_FORMAT_ASTC_5x5_UNORM_BLOCK                       = 161,
		VK_FORMAT_ASTC_5x5_SRGB_BLOCK                        = 162,
		VK_FORMAT_ASTC_6x5_UNORM_BLOCK                       = 163,
		VK_FORMAT_ASTC_6x5_SRGB_BLOCK                        = 164,
		VK_FORMAT_ASTC_6x6_UNORM_BLOCK                       = 165,
		VK_FORMAT_ASTC_6x6_SRGB_BLOCK                        = 166,
		VK_FORMAT_ASTC_8x5_UNORM_BLOCK                       = 167,
		VK_FORMAT_ASTC_8x5_SRGB_BLOCK                        = 168,
		VK_FORMAT_ASTC_8x6_UNORM_BLOCK                       = 169,
		VK_FORMAT_ASTC_8x6_SRGB_BLOCK                        = 170,
		VK_FORMAT_ASTC_8x8_UNORM_BLOCK                       = 171,
		VK_FORMAT_ASTC_8x8_SRGB_BLOCK                        = 172,
		VK_FORMAT_ASTC_10x5_UNORM_BLOCK                      = 173,
		VK_FORMAT_ASTC_10x5_SRGB_BLOCK                       = 174,
		VK_FORMAT_ASTC_10x6_UNORM_BLOCK                      = 175,
		VK_FORMAT_ASTC_10x6_SRGB_BLOCK                       = 176,
		VK_FORMAT_ASTC_10x8_UNORM_BLOCK                      = 177,
		VK_FORMAT_ASTC_10x8_SRGB_BLOCK                       = 178,
		VK_FORMAT_ASTC_10x10_UNORM_BLOCK                     = 179,
		VK_FORMAT_ASTC_10x10_SRGB_BLOCK                      = 180,
		VK_FORMAT_ASTC_12x10_UNORM_BLOCK                     = 181,
		VK_FORMAT_ASTC_12x10_SRGB_BLOCK                      = 182,
		VK_FORMAT_ASTC_12x12_UNORM_BLOCK                     = 183,
		VK_FORMAT_ASTC_12x12_SRGB_BLOCK                      = 184,
		VK_FORMAT_G8B8G8R8_422_UNORM                         = 1000156000,
		VK_FORMAT_B8G8R8G8_422_UNORM                         = 1000156001,
		VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM                  = 1000156002,
		VK_FORMAT_G8_B8R8_2PLANE_420_UNORM                   = 1000156003,
		VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM                  = 1000156004,
		VK_FORMAT_G8_B8R8_2PLANE_422_UNORM                   = 1000156005,
		VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM                  = 1000156006,
		VK_FORMAT_R10X6_UNORM_PACK16                         = 1000156007,
		VK_FORMAT_R10X6G10X6_UNORM_2PACK16                   = 1000156008,
		VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16         = 1000156009,
		VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16     = 1000156010,
		VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16     = 1000156011,
		VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = 1000156012,
		VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16  = 1000156013,
		VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = 1000156014,
		VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16  = 1000156015,
		VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = 1000156016,
		VK_FORMAT_R12X4_UNORM_PACK16                         = 1000156017,
		VK_FORMAT_R12X4G12X4_UNORM_2PACK16                   = 1000156018,
		VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16         = 1000156019,
		VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16     = 1000156020,
		VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16     = 1000156021,
		VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = 1000156022,
		VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16  = 1000156023,
		VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = 1000156024,
		VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16  = 1000156025,
		VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = 1000156026,
		VK_FORMAT_G16B16G16R16_422_UNORM                     = 1000156027,
		VK_FORMAT_B16G16R16G16_422_UNORM                     = 1000156028,
		VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM               = 1000156029,
		VK_FORMAT_G16_B16R16_2PLANE_420_UNORM                = 1000156030,
		VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM               = 1000156031,
		VK_FORMAT_G16_B16R16_2PLANE_422_UNORM                = 1000156032,
		VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM               = 1000156033,
		VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG                = 1000054000,
		VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG                = 1000054001,
		VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG                = 1000054002,
		VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG                = 1000054003,
		VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG                 = 1000054004,
		VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG                 = 1000054005,
		VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG                 = 1000054006,
		VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG                 = 1000054007,
		VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK                      = 1000066000,
		VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK                      = 1000066001,
		VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK                      = 1000066002,
		VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK                      = 1000066003,
		VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK                      = 1000066004,
		VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK                      = 1000066005,
		VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK                      = 1000066006,
		VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK                      = 1000066007,
		VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK                     = 1000066008,
		VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK                     = 1000066009,
		VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK                     = 1000066010,
		VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK                    = 1000066011,
		VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK                    = 1000066012,
		VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK                    = 1000066013,
		VK_FORMAT_MAX_ENUM                                   = 0x7FFFFFFF
	};

	enum TextureType
	{
		Texture1D,
		Texture2D,
		Texture3D,
		Cubemap,
	};

	struct Descriptor
	{
		GLInternalFormat glInternalFormat;
		GLFormat         glFormat;
		GLType           glType;
		GLFormat         glBaseInternalFormat; // Base internal format is a subset of GLFormat described in table 8.11 of spec
		VkFormat         vkFormat;

		TextureType type;
		uint32_t width;
		uint32_t height;
		uint32_t depth;
		uint32_t numMips;
		uint32_t arraySize;
		uint32_t rowPitch; // Row pitch for mip 0
		uint32_t depthPitch; // Size of mip 0
		uint32_t bitsPerPixelOrBlock; // If compressed bits per block, else bits per pixel
		uint32_t blockWidth;
		uint32_t blockHeight;
		bool compressed;
		bool srgb;
	};

	inline ktxpp_constexpr bool is_compressed(GLInternalFormat format)
	{
		switch (format)
		{
			// BCn
			case GL_COMPRESSED_RGB_S3TC_DXT1:
			case GL_COMPRESSED_RGBA_S3TC_DXT1:
			case GL_COMPRESSED_RGBA_S3TC_DXT3:
			case GL_COMPRESSED_RGBA_S3TC_DXT5:
			case GL_COMPRESSED_SRGB_S3TC_DXT1:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5:
			case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:

			// ETC
			case GL_ETC1_RGB8_OES:
			case GL_COMPRESSED_RGB8_ETC2:
			case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
			case GL_COMPRESSED_RGBA8_ETC2_EAC:
			case GL_COMPRESSED_SRGB8_ETC2:
			case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
			case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
			case GL_COMPRESSED_R11_EAC:
			case GL_COMPRESSED_RG11_EAC:
			case GL_COMPRESSED_SIGNED_R11_EAC:
			case GL_COMPRESSED_SIGNED_RG11_EAC:

			// PVRTC
			case GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
			case GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG:
			case GL_COMPRESSED_SRGB_PVRTC_2BPPV1:
			case GL_COMPRESSED_SRGB_PVRTC_4BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG:

			// ASTC
			case GL_COMPRESSED_RGBA_ASTC_4x4:
			case GL_COMPRESSED_RGBA_ASTC_5x4:
			case GL_COMPRESSED_RGBA_ASTC_5x5:
			case GL_COMPRESSED_RGBA_ASTC_6x5:
			case GL_COMPRESSED_RGBA_ASTC_6x6:
			case GL_COMPRESSED_RGBA_ASTC_8x5:
			case GL_COMPRESSED_RGBA_ASTC_8x6:
			case GL_COMPRESSED_RGBA_ASTC_8x8:
			case GL_COMPRESSED_RGBA_ASTC_10x5:
			case GL_COMPRESSED_RGBA_ASTC_10x6:
			case GL_COMPRESSED_RGBA_ASTC_10x8:
			case GL_COMPRESSED_RGBA_ASTC_10x10:
			case GL_COMPRESSED_RGBA_ASTC_12x10:
			case GL_COMPRESSED_RGBA_ASTC_12x12:

			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12:
				return true;
			default:
				return false;
		}
	}

	inline ktxpp_constexpr bool is_srgb(GLInternalFormat format)
	{
		switch (format)
		{
			// BCn
			case GL_COMPRESSED_SRGB_S3TC_DXT1:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5:

			// ETC
			case GL_COMPRESSED_SRGB8_ETC2:
			case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
			case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:

			// PVRTC
			case GL_COMPRESSED_SRGB_PVRTC_2BPPV1:
			case GL_COMPRESSED_SRGB_PVRTC_4BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG:

			// ASTC
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12:
				return true;
			default:
				return false;
		}
	}

	ktxpp_constexpr VkFormat get_vkformat_from_glformat(GLInternalFormat glInternalFormat, GLFormat glFormat, GLType glType)
	{
		// Whether signed integer or not
		bool signedByte    = glType == GL_BYTE;
		bool signedShort   = glType == GL_SHORT;
		bool signedInt     = glType == GL_INT;
		bool signedInt64   = glType == GL_INT64;

		bool unsignedByte  = glType == GL_UNSIGNED_BYTE;
		bool unsignedShort = glType == GL_UNSIGNED_SHORT;
		bool unsignedInt   = glType == GL_UNSIGNED_INT;
		bool unsignedInt64 = glType == GL_UNSIGNED_INT64;

		bool halfFloat     = glType == GL_HALF_FLOAT || glType == GL_HALF_FLOAT_OES;

		switch (glInternalFormat)
		{
			// 8 bits per component
			case GL_R8:
			{
				if (signedByte)    return VK_FORMAT_R8_SNORM;
				if (unsignedByte)  return VK_FORMAT_R8_UNORM;
			}
			case GL_RG8:
			{
				if (signedByte)    return VK_FORMAT_R8G8_SNORM;
				if (unsignedByte)  return VK_FORMAT_R8G8_UNORM;
			}
			case GL_RGB8:
			{
				if (signedByte)    return VK_FORMAT_R8G8B8_SNORM;
				if (unsignedByte)  return VK_FORMAT_R8G8B8_UNORM;
			}
			case GL_RGBA8:
			{
				if (signedByte)    return VK_FORMAT_R8G8B8A8_SNORM;
				if (unsignedByte)  return VK_FORMAT_R8G8B8A8_UNORM;
			}

			case GL_R8_SNORM:      return VK_FORMAT_R8_SNORM;
			case GL_RG8_SNORM:     return VK_FORMAT_R8G8_SNORM;
			case GL_RGB8_SNORM:    return VK_FORMAT_R8G8B8_SNORM;
			case GL_RGBA8_SNORM:   return VK_FORMAT_R8G8B8A8_SNORM;
			
			case GL_R8UI:          return VK_FORMAT_R8_UINT;
			case GL_RG8UI:         return VK_FORMAT_R8G8_UINT;
			case GL_RGB8UI:        return VK_FORMAT_R8G8B8_UINT;
			case GL_RGBA8UI:       return VK_FORMAT_R8G8B8A8_UINT;

			case GL_R8I:           return VK_FORMAT_R8_SINT;
			case GL_RG8I:          return VK_FORMAT_R8G8_SINT;
			case GL_RGB8I:         return VK_FORMAT_R8G8B8_SINT;
			case GL_RGBA8I:        return VK_FORMAT_R8G8B8A8_SINT;

			case GL_SR8:           return VK_FORMAT_R8_SRGB;
			case GL_SRG8:          return VK_FORMAT_R8G8_SRGB;
			case GL_SRGB8:         return VK_FORMAT_R8G8B8_SRGB;
			case GL_SRGB8_ALPHA8:  return VK_FORMAT_R8G8B8A8_SRGB;

			// 16 bits per component
			case GL_R16:
			{
				if (signedShort)   return VK_FORMAT_R16_SNORM;
				if (unsignedShort) return VK_FORMAT_R16_UNORM;
				if (halfFloat)     return VK_FORMAT_R16_SFLOAT;
			}
			case GL_RG16:
			{
				if (signedShort)   return VK_FORMAT_R16G16_SNORM;
				if (unsignedShort) return VK_FORMAT_R16G16_UNORM;
				if (halfFloat)     return VK_FORMAT_R16G16_SFLOAT;
			}
			case GL_RGB16:
			{
				if (signedShort)   return VK_FORMAT_R16G16B16_SNORM;
				if (unsignedShort) return VK_FORMAT_R16G16B16_UNORM;
				if (halfFloat)     return VK_FORMAT_R16G16B16_SFLOAT;
			}
			case GL_RGBA16:
			{
				if (signedShort)   return VK_FORMAT_R16G16B16A16_SNORM;
				if (unsignedShort) return VK_FORMAT_R16G16B16A16_UNORM;
				if (halfFloat)     return VK_FORMAT_R16G16B16A16_SFLOAT;
			}

			case GL_R16_SNORM:      return VK_FORMAT_R16_SNORM;
			case GL_RG16_SNORM:     return VK_FORMAT_R16G16_SNORM;
			case GL_RGB16_SNORM:    return VK_FORMAT_R16G16B16_SNORM;
			case GL_RGBA16_SNORM:   return VK_FORMAT_R16G16B16A16_SNORM;

			case GL_R16UI:          return VK_FORMAT_R16_UINT;
			case GL_RG16UI:         return VK_FORMAT_R16G16_UINT;
			case GL_RGB16UI:        return VK_FORMAT_R16G16B16_UINT;
			case GL_RGBA16UI:       return VK_FORMAT_R16G16B16A16_UINT;

			case GL_R16I:           return VK_FORMAT_R16_SINT;
			case GL_RG16I:          return VK_FORMAT_R16G16_SINT;
			case GL_RGB16I:         return VK_FORMAT_R16G16B16_SINT;
			case GL_RGBA16I:        return VK_FORMAT_R16G16B16A16_SINT;

			case GL_R16F:           return VK_FORMAT_R16_SFLOAT;
			case GL_RG16F:          return VK_FORMAT_R16G16_SFLOAT;
			case GL_RGB16F:         return VK_FORMAT_R16G16B16_SFLOAT;
			case GL_RGBA16F:        return VK_FORMAT_R16G16B16A16_SFLOAT;

			// 32 bits per component
			case GL_R32UI:          return VK_FORMAT_R32_UINT;
			case GL_RG32UI:         return VK_FORMAT_R32G32_UINT;
			case GL_RGB32UI:        return VK_FORMAT_R32G32B32_UINT;
			case GL_RGBA32UI:       return VK_FORMAT_R32G32B32A32_UINT;

			case GL_R32I:           return VK_FORMAT_R32_SINT;
			case GL_RG32I:          return VK_FORMAT_R32G32_SINT;
			case GL_RGB32I:         return VK_FORMAT_R32G32B32_SINT;
			case GL_RGBA32I:        return VK_FORMAT_R32G32B32A32_SINT;

			case GL_R32F:           return VK_FORMAT_R32_SFLOAT;
			case GL_RG32F:          return VK_FORMAT_R32G32_SFLOAT;
			case GL_RGB32F:         return VK_FORMAT_R32G32B32_SFLOAT;
			case GL_RGBA32F:        return VK_FORMAT_R32G32B32A32_SFLOAT;

			// Packed
			case GL_RGB565:         return VK_FORMAT_R5G6B5_UNORM_PACK16;
			case GL_RGBA4:          return VK_FORMAT_R4G4B4A4_UNORM_PACK16;
			case GL_RGB5_A1:        return VK_FORMAT_R5G5B5A1_UNORM_PACK16;
			case GL_RGB10_A2:       return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
			case GL_RGB10_A2UI:     return VK_FORMAT_A2R10G10B10_UINT_PACK32;
			case GL_R11F_G11F_B10F: return VK_FORMAT_B10G11R11_UFLOAT_PACK32;
			case GL_RGB9_E5:        return VK_FORMAT_E5B9G9R9_UFLOAT_PACK32;

			// S3TX/DXT/BC
			case GL_COMPRESSED_RGB_S3TC_DXT1:           return VK_FORMAT_BC1_RGB_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_S3TC_DXT1:          return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_S3TC_DXT3:          return VK_FORMAT_BC2_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_S3TC_DXT5:          return VK_FORMAT_BC3_UNORM_BLOCK;

			case GL_COMPRESSED_SRGB_S3TC_DXT1:          return VK_FORMAT_BC1_RGB_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1:    return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3:    return VK_FORMAT_BC2_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5:    return VK_FORMAT_BC3_SRGB_BLOCK;

			case GL_COMPRESSED_LUMINANCE_LATC1:              return VK_FORMAT_BC4_UNORM_BLOCK;
			case GL_COMPRESSED_LUMINANCE_ALPHA_LATC2:        return VK_FORMAT_BC5_UNORM_BLOCK;
			case GL_COMPRESSED_SIGNED_LUMINANCE_LATC1:       return VK_FORMAT_BC4_SNORM_BLOCK;
			case GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2: return VK_FORMAT_BC5_SNORM_BLOCK;

			case GL_COMPRESSED_RED_RGTC1:                    return VK_FORMAT_BC4_UNORM_BLOCK;
			case GL_COMPRESSED_RG_RGTC2:                     return VK_FORMAT_BC5_UNORM_BLOCK;
			case GL_COMPRESSED_SIGNED_RED_RGTC1:             return VK_FORMAT_BC4_SNORM_BLOCK;
			case GL_COMPRESSED_SIGNED_RG_RGTC2:              return VK_FORMAT_BC5_SNORM_BLOCK;

			case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT:   return VK_FORMAT_BC6H_SFLOAT_BLOCK;
			case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT: return VK_FORMAT_BC6H_UFLOAT_BLOCK;
			case GL_COMPRESSED_RGBA_BPTC_UNORM:         return VK_FORMAT_BC7_UNORM_BLOCK;
			case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:   return VK_FORMAT_BC7_SRGB_BLOCK;

			// ETC
			case GL_ETC1_RGB8_OES:                             return VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK;
			case GL_COMPRESSED_RGB8_ETC2:                      return VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK;
			case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:  return VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA8_ETC2_EAC:                 return VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK;
			case GL_COMPRESSED_SRGB8_ETC2:                     return VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2: return VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:          return VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK;
			case GL_COMPRESSED_R11_EAC:                        return VK_FORMAT_EAC_R11_UNORM_BLOCK;
			case GL_COMPRESSED_RG11_EAC:                       return VK_FORMAT_EAC_R11G11_UNORM_BLOCK;
			case GL_COMPRESSED_SIGNED_R11_EAC:                 return VK_FORMAT_EAC_R11_SNORM_BLOCK;
			case GL_COMPRESSED_SIGNED_RG11_EAC:                return VK_FORMAT_EAC_R11G11_SNORM_BLOCK;

			// PVRTC
			case GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
				return VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG;

			case GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
				return VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG;

			case GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG: return VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG;
			case GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG: return VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG;

			case GL_COMPRESSED_SRGB_PVRTC_2BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1:
				return VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG;

			case GL_COMPRESSED_SRGB_PVRTC_4BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1:
				return VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG;

			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG: return VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG;
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG: return VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG;

			// ASTC
			case GL_COMPRESSED_RGBA_ASTC_4x4:           return VK_FORMAT_ASTC_4x4_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_5x4:           return VK_FORMAT_ASTC_5x4_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_5x5:           return VK_FORMAT_ASTC_5x5_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_6x5:           return VK_FORMAT_ASTC_6x5_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_6x6:           return VK_FORMAT_ASTC_6x6_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_8x5:           return VK_FORMAT_ASTC_8x5_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_8x6:           return VK_FORMAT_ASTC_8x6_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_8x8:           return VK_FORMAT_ASTC_8x8_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_10x5:          return VK_FORMAT_ASTC_10x5_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_10x6:          return VK_FORMAT_ASTC_10x6_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_10x8:          return VK_FORMAT_ASTC_10x8_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_10x10:         return VK_FORMAT_ASTC_10x10_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_12x10:         return VK_FORMAT_ASTC_12x10_UNORM_BLOCK;
			case GL_COMPRESSED_RGBA_ASTC_12x12:         return VK_FORMAT_ASTC_12x12_UNORM_BLOCK;

			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4:   return VK_FORMAT_ASTC_4x4_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4:   return VK_FORMAT_ASTC_5x4_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5:   return VK_FORMAT_ASTC_5x5_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5:   return VK_FORMAT_ASTC_6x5_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6:   return VK_FORMAT_ASTC_6x6_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5:   return VK_FORMAT_ASTC_8x5_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6:   return VK_FORMAT_ASTC_8x6_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8:   return VK_FORMAT_ASTC_8x8_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5:  return VK_FORMAT_ASTC_10x5_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6:  return VK_FORMAT_ASTC_10x6_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8:  return VK_FORMAT_ASTC_10x8_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10: return VK_FORMAT_ASTC_10x10_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10: return VK_FORMAT_ASTC_12x10_SRGB_BLOCK;
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12: return VK_FORMAT_ASTC_12x12_SRGB_BLOCK;

			default: return VK_FORMAT_UNDEFINED;
		}

		return VK_FORMAT_UNDEFINED;
	}

	using namespace internal;

	inline ktxpp_constexpr uint32_t get_bits_per_pixel_or_block(GLInternalFormat format)
	{
		switch (format)
		{
			case GL_R8:
			case GL_R8_SNORM:
			case GL_R8UI:
			case GL_R8I:
			case GL_SR8:
			case GL_R3_G3_B2:
				return 8;
			case GL_RG8:
			case GL_RG8_SNORM:
			case GL_RG8UI:
			case GL_RG8I:
			case GL_SRG8:
			case GL_R16:
			case GL_R16_SNORM:
			case GL_R16UI:
			case GL_R16I:
			case GL_R16F:
			case GL_RGB565:
			case GL_RGB5_A1:
			case GL_RGBA4:
				return 16;
			case GL_RGB8:
			case GL_RGB8_SNORM:
			case GL_RGB8UI:
			case GL_RGB8I:
			case GL_SRGB8:
				return 24;
			case GL_RGBA8:
			case GL_RGBA8_SNORM:
			case GL_RGBA8UI:
			case GL_RGBA8I:
			case GL_SRGB8_ALPHA8:
			case GL_RG16:
			case GL_RG16_SNORM:
			case GL_RG16UI:
			case GL_RG16I:
			case GL_RG16F:
			case GL_RGB10_A2:
			case GL_RGB10_A2UI:
			case GL_R11F_G11F_B10F:
			case GL_RGB9_E5:
				return 32;
			case GL_RGB16:
			case GL_RGB16_SNORM:
			case GL_RGB16UI:
			case GL_RGB16I:
			case GL_RGB16F:
				return 48;
			case GL_RGBA16:
			case GL_RGBA16_SNORM:
			case GL_RGBA16UI:
			case GL_RGBA16I:
			case GL_RGBA16F:
			case GL_RG32UI:
			case GL_RG32I:
			case GL_RG32F:
			case GL_COMPRESSED_RGB_S3TC_DXT1:
			case GL_COMPRESSED_RGBA_S3TC_DXT1:
			case GL_ETC1_RGB8_OES:
			case GL_COMPRESSED_R11_EAC:
			case GL_COMPRESSED_SIGNED_R11_EAC:
			case GL_COMPRESSED_RGB8_ETC2:
			case GL_COMPRESSED_SRGB8_ETC2:
			case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
			case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
			case GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
			case GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG:
			case GL_COMPRESSED_SRGB_PVRTC_2BPPV1:
			case GL_COMPRESSED_SRGB_PVRTC_4BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG:
				return 64;
			case GL_RGB32UI:
			case GL_RGB32I:
			case GL_RGB32F:
				return 96;
			case GL_RGBA32UI:
			case GL_RGBA32I:
			case GL_RGBA32F:
			case GL_COMPRESSED_RGBA_S3TC_DXT3:
			case GL_COMPRESSED_RGBA_S3TC_DXT5:
			case GL_COMPRESSED_SRGB_S3TC_DXT1:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5:
			case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:
			case GL_COMPRESSED_RG11_EAC:
			case GL_COMPRESSED_SIGNED_RG11_EAC:
			case GL_COMPRESSED_RGBA8_ETC2_EAC:
			case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
				return 128;
			default:
				return 32; // Most formats are 32 bits per pixel
				break;
		}
	}

	inline ktxpp_constexpr void get_block_size(GLInternalFormat glInternalFormat, uint32_t& blockWidth, uint32_t& blockHeight)
	{
		switch (glInternalFormat)
		{
			// BCn
			case GL_COMPRESSED_RGB_S3TC_DXT1:
			case GL_COMPRESSED_RGBA_S3TC_DXT1:
			case GL_COMPRESSED_RGBA_S3TC_DXT3:
			case GL_COMPRESSED_RGBA_S3TC_DXT5:

			case GL_COMPRESSED_SRGB_S3TC_DXT1:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3:
			case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5:

			case GL_COMPRESSED_LUMINANCE_LATC1:
			case GL_COMPRESSED_LUMINANCE_ALPHA_LATC2:
			case GL_COMPRESSED_SIGNED_LUMINANCE_LATC1:
			case GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2:
			case GL_COMPRESSED_RED_RGTC1:
			case GL_COMPRESSED_RG_RGTC2:
			case GL_COMPRESSED_SIGNED_RED_RGTC1:
			case GL_COMPRESSED_SIGNED_RG_RGTC2:

			case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT:
			case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:
			case GL_COMPRESSED_RGBA_BPTC_UNORM:
			case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:
			
			// ASTC
			case GL_COMPRESSED_RGBA_ASTC_4x4:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4:

			// ETC
			case GL_ETC1_RGB8_OES:
			case GL_COMPRESSED_RGB8_ETC2:
			case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
			case GL_COMPRESSED_RGBA8_ETC2_EAC:
			case GL_COMPRESSED_SRGB8_ETC2:
			case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
			case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
			case GL_COMPRESSED_R11_EAC:
			case GL_COMPRESSED_RG11_EAC:
			case GL_COMPRESSED_SIGNED_R11_EAC:
			case GL_COMPRESSED_SIGNED_RG11_EAC:

			// PVRTC
			case GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
			case GL_COMPRESSED_SRGB_PVRTC_4BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1:
			case GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG:
				blockWidth = 4; blockHeight = 4;
				break;
			case GL_COMPRESSED_RGBA_ASTC_5x4:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4:
				blockWidth = 5; blockHeight = 4;
				break;
			case GL_COMPRESSED_RGBA_ASTC_5x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5:
				blockWidth = 5; blockHeight = 5;
				break;
			case GL_COMPRESSED_RGBA_ASTC_6x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5:
				blockWidth = 6; blockHeight = 5;
				break;
			case GL_COMPRESSED_RGBA_ASTC_6x6:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6:
				blockWidth = 6; blockHeight = 6;
				break;
			case GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
			case GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
			case GL_COMPRESSED_SRGB_PVRTC_2BPPV1:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1:
			case GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG:
			case GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG:
				blockWidth = 8; blockHeight = 4;
				break;
			case GL_COMPRESSED_RGBA_ASTC_8x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5:
				blockWidth = 8; blockHeight = 5;
				break;
			case GL_COMPRESSED_RGBA_ASTC_8x6:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6:
				blockWidth = 8; blockHeight = 6;
				break;
			case GL_COMPRESSED_RGBA_ASTC_8x8:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8:
				blockWidth = 8; blockHeight = 8;
				break;
			case GL_COMPRESSED_RGBA_ASTC_10x5:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5:
				blockWidth = 10; blockHeight = 5;
				break;
			case GL_COMPRESSED_RGBA_ASTC_10x6:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6:
				blockWidth = 10; blockHeight = 6;
				break;
			case GL_COMPRESSED_RGBA_ASTC_10x8:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8:
				blockWidth = 10; blockHeight = 8;
				break;
			case GL_COMPRESSED_RGBA_ASTC_10x10:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10:
				blockWidth = 10; blockHeight = 10;
				break;
			case GL_COMPRESSED_RGBA_ASTC_12x10:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10:
				blockWidth = 12; blockHeight = 10;
				break;
			case GL_COMPRESSED_RGBA_ASTC_12x12:
			case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12:
				blockWidth = 12; blockHeight = 12;
				break;
			default:
				blockWidth = 1; blockHeight = 1;
				break;
		}

		return;
	}

	inline unsigned char* decode_header(unsigned char* sourceData, Descriptor& desc)
	{
		const HeaderKTX& header = *reinterpret_cast<const HeaderKTX*>(sourceData); // First 12 bytes are the magic KTX sequence

		bool isKTXFile = (header.identifier[0] == '«') &&
		                 (header.identifier[1] == 'K') &&
		                 (header.identifier[2] == 'T') &&
		                 (header.identifier[3] == 'X') &&
		                 (header.identifier[4] == ' ') &&
		                 (header.identifier[5] == '1') &&
		                 (header.identifier[6] == '1') &&
		                 (header.identifier[7] == '»') &&
		                 (header.identifier[8] == '\r') &&
		                 (header.identifier[9] == '\n') &&
		                 (header.identifier[10] == '\x1A') &&
		                 (header.identifier[11] == '\n');

		if(!isKTXFile)
		{
			return nullptr;
		}

		bool isHeaderLittleEndian = header.endianness == 0x04030201;

		// For compressed formats, glFormat and glType must be set to zero
		bool isCompressed         = header.glFormat == 0 || header.glType == 0;

		desc.width                = header.pixelWidth  > 0 ? header.pixelWidth  : 1;
		desc.height               = header.pixelHeight > 0 ? header.pixelHeight : 1;
		desc.depth                = header.pixelDepth  > 0 ? header.pixelDepth  : 1;
		desc.numMips              = header.numberOfMipmapLevels > 0 ? header.numberOfMipmapLevels : 1;
		desc.compressed           = isCompressed;
		desc.arraySize            = header.numberOfArrayElements > 0 ? header.numberOfArrayElements : 1;
		
		// If numberOfMipmapLevels equals 0, it indicates that a full mipmap pyramid should be generated from level 0 at load time
		desc.numMips              = header.numberOfMipmapLevels;
		desc.glInternalFormat     = (GLInternalFormat)header.glInternalFormat;
		desc.glType               = (GLType)header.glType;
		desc.glFormat             = (GLFormat)header.glFormat;
		desc.glBaseInternalFormat = (GLFormat)header.glBaseInternalFormat;
		desc.srgb                 = is_srgb(desc.glInternalFormat);
		desc.bitsPerPixelOrBlock  = get_bits_per_pixel_or_block(desc.glInternalFormat);
		get_block_size(desc.glInternalFormat, desc.blockWidth, desc.blockHeight);

		// For non cubemaps this should be 1.
		if(header.numberOfFaces > 1)
		{
			desc.type = Cubemap;
		}
		else if(header.pixelDepth > 1)
		{
			desc.type = Texture3D;
		}
		else if (header.pixelHeight > 1)
		{
			desc.type = Texture2D;
		}
		else
		{
			desc.type = Texture1D;
		}

		desc.vkFormat = get_vkformat_from_glformat(desc.glInternalFormat, desc.glFormat, desc.glType);

		desc.rowPitch   = desc.width * desc.bitsPerPixelOrBlock / (8 * desc.blockWidth);
		desc.depthPitch = desc.rowPitch * desc.height / desc.blockHeight;
		
		// Depth pitch should match dataSize
		// uint32_t dataSize = *((uint32_t*)(sourceData + sizeof(HeaderKTX) + header.bytesOfKeyValueData));

		uint32_t offset = sizeof(HeaderKTX) + header.bytesOfKeyValueData + sizeof(uint32_t);

		return sourceData + offset;
	}

	inline void encode_header
	(
		const GLInternalFormat glInternalFormat, GLType glType, GLFormat glFormat, GLFormat glBaseInternalFormat,
		const uint32_t width, const uint32_t height, const uint32_t depth,
		const TextureType type, const uint32_t mipCount, const uint32_t arraySize,
		HeaderKTX& header
	)
	{
		header.identifier[0] = '«';
		header.identifier[1] = 'K';
		header.identifier[2] = 'T';
		header.identifier[3] = 'X';
		header.identifier[4] = ' ';
		header.identifier[5] = '1';
		header.identifier[6] = '1';
		header.identifier[7] = '»';
		header.identifier[8] = '\r';
		header.identifier[9] = '\n';
		header.identifier[10] = '\x1A';
		header.identifier[11] = '\n';

		header.endianness = 0x04030201;

		bool isCompressed = is_compressed(glInternalFormat);

		header.glType = glType;
		header.glTypeSize = isCompressed ? 0 : 4;
		header.glFormat = glFormat;
		header.glInternalFormat = glInternalFormat;
		header.glBaseInternalFormat = glBaseInternalFormat;

		header.pixelWidth = width;
		header.pixelHeight = height;
		header.pixelDepth = depth;
		header.numberOfMipmapLevels = mipCount;
		header.numberOfFaces = type == Cubemap ? 6 : 1;
		header.numberOfArrayElements = type != Cubemap ? arraySize : 0;
	}
}