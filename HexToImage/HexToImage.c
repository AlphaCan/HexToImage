#include "HexToImage.h"

const char* Image = "424DE6000000000000007600000028000000100000000E\
0000000100040000000000700000000000000000000000000000000000000000000\
00000008000008000000080800080000000800080008080000080808000C0C0C000\
0000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFF00FFF\
FFFFFFFFFF0F70FFFFFFFFFFFF07F0FFFFFFFFFFFFF00FFFFFFFFF7777F0FFFFFFF\
FFF7667F0FFFFFFFFFF766700FFFFFFFFFF7667FFFFFFFFFFFF7667FFFFFFFFFFFF\
7667FFFFFFFFFFFF7667FFFFFFFFFFFF7967FFFFFFFFFFFF7777FFFFFFFFFFFFFFFFFFFFFFFFFFF";

/** 将XML文件中的BMP位图数据流转成十六进制数据
 *
 * @param[in]  src			从XML中解析出来的原始BMP位图流数据
 * @param[out] data         转换后的十六进制数据(一个字节一组数据)
 */
void GetHexData(const char* src, HEXIMAGEDATA* data)
{
	char temp[4096] = { 0 };
	uint16_t count = 0;
	char chartemp = ' ';
	char temp2[4096] = { 0 };
	while (*src)
	{

		chartemp = *src;
		sscanf(&chartemp, "%hhx", &temp[count]);
//		Nex_PRINT("%#x\n",temp[count]);
		src++;
		count++;
	}

	for (int i = 0; i < count; i += 2)
	{
		temp2[data->imagedatasize] = temp[i] * 16 + temp[i + 1];

//		Nex_PRINT("%#x\n", temp2[data->imagedatasize] & 0xff);
		data->imagedatasize++;
	}
	data->imagehexdata = temp2;
	
}

/** 得到bmp位图文件头信息
 *
 * @param[out] bmpFileHeader   位图文件头
 */
void Get_bmpFileHeader(BITMAPFILEHEADER* bmpFileHeader)
{
	HEXIMAGEDATA heximagedata = { 0 };//必须初始化，避免空指针
	GetHexData(Image, &heximagedata);
	bmpFileHeader = (BITMAPFILEHEADER*)heximagedata.imagehexdata;
	Nex_PRINT("位图文件头主要是对位图文件的一些描述:BMPFileHeader\n\n");
	Nex_PRINT("文件标识符 = 0X%X\n", bmpFileHeader->bfType);
	Nex_PRINT("BMP 文件大小 = %d 字节\n", bmpFileHeader->bfSize);
	Nex_PRINT("保留值1 = %d \n", bmpFileHeader->bfReserved1);
	Nex_PRINT("保留值2 = %d \n", bmpFileHeader->bfReserved2);
	Nex_PRINT("文件头的最后到图像数据位开始的偏移量 = %d 字节\n", bmpFileHeader->bfOffBits);

}

/** 得到bmp位图信息头信息
 *
 * @param[out] bmpInfo   位图信息头
 */
void Get_bmpInfo(BITMAPINFOHEADER* bmpInfo)
{
	HEXIMAGEDATA heximagedata = { 0 };//必须初始化，避免空指针
	GetHexData(Image, &heximagedata);
	bmpInfo = (BITMAPINFOHEADER*)&(heximagedata.imagehexdata[14]);
	Nex_PRINT("\n\n位图信息头主要是对位图图像方面信息的描述:BMPInfo\n\n");
	Nex_PRINT("信息头的大小 = %d 字节\n", bmpInfo->biSize);
	Nex_PRINT("位图的高度 = %d \n", bmpInfo->biHeight);
	Nex_PRINT("位图的宽度 = %d \n", bmpInfo->biWidth);
	Nex_PRINT("图像的位面数(位面数是调色板的数量,默认为1个调色板) = %d \n", bmpInfo->biPlanes);
	Nex_PRINT("每个像素的位数 = %d 位\n", bmpInfo->biBitCount);
	Nex_PRINT("压缩类型 = %d \n", bmpInfo->biCompression);
	Nex_PRINT("图像的大小 = %d 字节\n", bmpInfo->biSizeImage);
	Nex_PRINT("水平分辨率 = %d \n", bmpInfo->biXPelsPerMeter);
	Nex_PRINT("垂直分辨率 = %d \n", bmpInfo->biYPelsPerMeter);
	Nex_PRINT("使用的色彩数 = %d \n", bmpInfo->biClrUsed);
	Nex_PRINT("重要的色彩数 = %d \n", bmpInfo->biClrImportant);

	Nex_PRINT("\n\n\n压缩说明：有0（不压缩），1（RLE 8，8位RLE压缩），2（RLE 4，4位RLE压缩，3（Bitfields，位域存放）");
}


/** 得到bmp位图，会在本地磁盘中生成一个bmp位图文件
 *
 * @param[in] filename   要生成的bmp位图文件名 例如 "E:/1.bmp" or "1.bmp"
 */
unsigned int GetImageFile(char *filename)
{
	FILE* fp;
	HEXIMAGEDATA heximagedata = {0};//必须初始化，避免空指针
	GetHexData(Image, &heximagedata);
	if ((fp = fopen(filename, "wb")) == NULL)
	{
		Nex_PRINT("Cannot create bmp bitmap !\n");
		return 0;
	}

	unsigned int write_state = fwrite(heximagedata.imagehexdata, heximagedata.imagedatasize, 1, fp);
	fclose(fp);
	return write_state;
}


int main()
{
	HEXIMAGEDATA heximagedata = {0};
	BITMAPFILEHEADER bitmapfileheader;
	GetHexData(Image, &heximagedata);
	Get_bmpFileHeader(&bitmapfileheader);

	BITMAPINFOHEADER bitmapinfoheader;
	Get_bmpInfo(&bitmapinfoheader);
	GetImageFile("E:/1.bmp");
	
	return 0;
}