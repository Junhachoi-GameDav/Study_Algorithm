// std
#include <iostream>
#include <filesystem>

// opencv
#include <opencv2/opencv.hpp>

int main() {
	
	// init
	namespace fs = std::filesystem;

#pragma region iron
	static const cv::Point3_<uchar> iron[128]
	{
		{ 0,	0,	0 },
		{ 0,	0,	0 },
		{ 0,	0,	36 },
		{ 0,	0,	51 },
		{ 0,	0,	66 },
		{ 0,	0,	81 },
		{ 2,	0,	90 },
		{ 4,	0,	99 },
		{ 7,	0,	106 },
		{ 11,	0,	115 },
		{ 14,	0,	119 },
		{ 20,	0,	123 },
		{ 27,	0,	128 },
		{ 33,	0,	133 },
		{ 41,	0,	137 },
		{ 48,	0,	140 },
		{ 55,	0,	143 },
		{ 61,	0,	146 },
		{ 66,	0,	149 },
		{ 72,	0,	150 },
		{ 78,	0,	151 },
		{ 84,	0,	152 },
		{ 91,	0,	153 },
		{ 97,	0,	155 },
		{ 104,	0,	155 },
		{ 110,	0,	156 },
		{ 115,	0,	157 },
		{ 122,	0,	157 },
		{ 128,	0,	157 },
		{ 134,	0,	157 },
		{ 139,	0,	157 },
		{ 146,	0,	156 },
		{ 152,	0,	155 },
		{ 157,	0,	155 },
		{ 162,	0,	155 },
		{ 167,	0,	154 },
		{ 171,	0,	153 },
		{ 175,	1,	152 },
		{ 178,	1,	151 },
		{ 182,	2,	149 },
		{ 185,	4,	149 },
		{ 188,	5,	147 },
		{ 191,	6,	146 },
		{ 193,	8,	144 },
		{ 195,	11,	142 },
		{ 198,	13,	139 },
		{ 201,	17,	135 },
		{ 203,	20,	132 },
		{ 206,	23,	127 },
		{ 208,	26,	121 },
		{ 210,	29,	116 },
		{ 212,	33,	111 },
		{ 214,	37,	103 },
		{ 217,	41,	97 },
		{ 219,	46,	89 },
		{ 221,	49,	78 },
		{ 223,	53,	66 },
		{ 224,	56,	54 },
		{ 226,	60,	42 },
		{ 228,	64,	30 },
		{ 229,	68,	25 },
		{ 231,	72,	20 },
		{ 232,	76,	16 },
		{ 234,	78,	12 },
		{ 235,	82,	10 },
		{ 236,	86,	8 },
		{ 237,	90,	7 },
		{ 238,	93,	5 },
		{ 239,	96,	4 },
		{ 240,	100,	3 },
		{ 241,	103,	3 },
		{ 241,	106,	2 },
		{ 242,	109,	1 },
		{ 243,	113,	1 },
		{ 244,	116,	0 },
		{ 244,	120,	0 },
		{ 245,	125,	0 },
		{ 246,	129,	0 },
		{ 247,	133,	0 },
		{ 248,	136,	0 },
		{ 248,	139,	0 },
		{ 249,	142,	0 },
		{ 249,	145,	0 },
		{ 250,	149,	0 },
		{ 251,	154,	0 },
		{ 252,	159,	0 },
		{ 253,	163,	0 },
		{ 253,	168,	0 },
		{ 253,	172,	0 },
		{ 254,	176,	0 },
		{ 254,	179,	0 },
		{ 254,	184,	0 },
		{ 254,	187,	0 },
		{ 254,	191,	0 },
		{ 254,	195,	0 },
		{ 254,	199,	0 },
		{ 254,	202,	1 },
		{ 254,	205,	2 },
		{ 254,	208,	5 },
		{ 254,	212,	9 },
		{ 254,	216,	12 },
		{ 255,	219,	15 },
		{ 255,	221,	23 },
		{ 255,	224,	32 },
		{ 255,	227,	39 },
		{ 255,	229,	50 },
		{ 255,	232,	63 },
		{ 255,	235,	75 },
		{ 255,	238,	88 },
		{ 255,	239,	102 },
		{ 255,	241,	116 },
		{ 255,	242,	134 },
		{ 255,	244,	149 },
		{ 255,	245,	164 },
		{ 255,	247,	179 },
		{ 255,	248,	192 },
		{ 255,	249,	203 },
		{ 255,	251,	216 },
		{ 255,	253,	228 },
		{ 255,	254,	239 },
		{ 255,	255,	249 },
		{ 255,	255,	249 },
		{ 255,	255,	249 },
		{ 255,	255,	249 },
		{ 255,	255,	249 },
		{ 255,	255,	249 },
		{ 255,	255,	249 },
		{ 255,	255,	249 }
	};

#pragma endregion

	fs::path file_path = fs::current_path() / "images";
	
	std::vector<fs::path> image_paths;
	for (const auto& image : fs::directory_iterator(file_path))
		image_paths.push_back(image.path());

	
	for (const auto& img_path : image_paths)
	{
		// test
		cv::Mat image = cv::imread(img_path.string(), cv::IMREAD_UNCHANGED);

		//double min_temp = 0.0; // 최소 온도 (예시)
		//double max_temp = 65535.0; // 최대 온도(16비트 데이터의 최대 값)
		//cv::minMaxIdx(image, &min_temp, &max_temp);

		cv::Mat temp_Image;
		image.convertTo(temp_Image, CV_32F);
		temp_Image = temp_Image / 40.0 - 100.0;

		double min_temp;
		double max_temp;
		cv::minMaxLoc(temp_Image, &min_temp, &max_temp);

		//std::numeric_limits<unsigned short>::max();
		cv::Mat normalized_Image;
		//																	alph, beta
		//																	255.0(x - min_temp) / (max_temp - min_temp) = 0 ~ 255
		temp_Image.convertTo(normalized_Image, CV_8U, 255.0 / (max_temp - min_temp), -min_temp * 255.0 / (max_temp - min_temp));
		
		cv::Mat colored_Image;
		cv::applyColorMap(normalized_Image, colored_Image, cv::COLORMAP_INFERNO);

		cv::imshow("Thermal Image1", colored_Image);
		cv::waitKey(0);
	}
	

	return 0;
}