#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define Nex_DEBUG 


#ifdef Nex_DEBUG
#define Nex_PRINT printf
#else
#define Nex_PRINT(...) do {} while (0)
#endif

#ifndef PACKED
#define PACKED_BEGIN __pragma(pack(push, 1))
#define PACKED
#define PACKED_END __pragma(pack(pop))
#endif

#include <stdio.h>
#include <stdlib.h>
#include < stdint.h>


/*BITMAPFILEHEADER的第1个属性是bfType(2字节)，这里恒定等于0x4D42。由于内存
中的数据排列高位在左，低位在右，所以内存中从左往右看就显示成(42 4D)，所以在
winhex中头两个 字节显示为(42 4D)就是这样形成的，以后的数据都是这个特点，不再
作重复说明。

BITMAPFILEHEADER的第2个属性是bfSize(4字节)，表示整个bmp文件的大小。

BITMAPFILEHEADER的第3个、第4个属性分别是bfReserved1、bfReserved2(各2字节)，这
里是2个保留属性，都为0，这里等于&H0000、0x0000。

BITMAPFILEHEADER的第5个属性是bfOffBits(4字节)，表示DIB数据区在bmp文件中的位置
偏移量，比如等于0x00000076=118，表示数据区从文件开始往后数的118字节开始。

 BITMAPFILEHEADER结构体这里就讲完了，大家会发现BITMAPFILEHEADER只占了bmp文件
 开始的14字节长度，但需要 特别说明的是：我们在编程时，经常是以二进制的形式打
 开一个bmp文件，然后将其开头的14个字节读入自己定义的BITMAPFILEHEADER 结构体中
 ，如果按上述定义结构体的方式，需要注意，这个自己定义的结构体在内存中由于字节
对齐，会占用16字节的空间，因而直接读入16字节，按字节顺序 赋值给结构体，出来的
数据是错误的，这样的话，可以先将这14字节的数据读入到一个缓冲器中，然后从缓冲
器中按字节对结构体进行赋值。详细程序见后附录。 鉴于此中原因，在vb中定义一个
BITMAPFILEHEADER结构体变量，其长度占了16个字节，原因就是第1个属性本来应该只
分配2个字节，但实际被 分配了4个字节，多出来2个字节，所以如果想保存一张bmp图片，
写入BITMAPFILEHEADER结构体时一定要注意这一点。*/

PACKED_BEGIN
typedef struct  tagBITMAPFILEHEADER {
	uint16_t bfType;//固定为0x4d42; 
	uint32_t bfSize; //文件大小
	uint16_t bfReserved1; //保留字，不考虑
	uint16_t bfReserved2; //保留字，同上
	uint32_t bfOffBits; //实际位图数据的偏移字节数，即前三个部分长度之和
} BITMAPFILEHEADER;
PACKED_END

/*
BITMAPINFOHEADER的第1个属性是biSize(4字节)，表示BITMAPINFOHEADER结构体的长度，最常见的长度是40字节。

BITMAPINFOHEADER的第2个属性是biWidth(4字节)，表示bmp图片的宽度

BITMAPINFOHEADER的第3个属性是biHeight(4字节)，表示bmp图片的高度

BITMAPINFOHEADER的第4个属性是biPlanes(2字节)，表示bmp图片的平面属，显然显示器只有一个平面，所以恒等于1，这里等于0x0001。

BITMAPINFOHEADER的第5个属性是biBitCount(2字节)，表示bmp图片的颜色位数，即1位图（单色或二值图像），8位图，16位图，24位图、32位图等等。

BITMAPINFOHEADER的第6个属性是biCompression(4字节)，表示图片的压缩属性，bmp图片是不压缩的，等于0，所以这里为0x00000000。

BITMAPINFOHEADER的第7个属性是biSizeImage(4字节)，表示bmp图片数据区的大小，当上一个数值biCompression等于0时，这里的值可以省略不填，所以这里等于0x00000000。

BITMAPINFOHEADER的第8个属性是biXPelsPerMeter(4字节)，表示图片X轴每米多少像素，可省略，这里等于0x00000EC3=3779像素/米。

BITMAPINFOHEADER的第9个属性是biYPelsPerMeter(4字节)，表示图片Y轴每米多少像素，可省略，这里等于0x00000EC3=3779像素/米。

BITMAPINFOHEADER的第10个属性是biClrUsed(4字节)，表示使用了多少个颜色索引表，一般biBitCount属性小于16才会用到，等于0时表示有2^biBitCount个颜色索引表，所以这里仍等于0x00000000。

BITMAPINFOHEADER的第11个属性是biClrImportant(4字节)，表示有多少个重要的颜色，等于0时表示所有颜色都很重要，所以这里等于0x00000000。
*/
PACKED_BEGIN
typedef struct tagBITMAPINFOHEADER {
	//public:
	uint32_t biSize; //指定此结构体的长度，为40
	int biWidth; //位图宽
	int biHeight; //位图高
	uint16_t biPlanes; //平面数，为1
	uint16_t biBitCount; //采用颜色位数，可以是1，2，4，8，16，24，新的可以是32
	uint32_t biCompression; //压缩方式，可以是0，1，2，其中0表示不压缩
	uint32_t biSizeImage; //实际位图数据占用的字节数
	int biXPelsPerMeter; //X方向分辨率
	int biYPelsPerMeter; //Y方向分辨率
	uint32_t biClrUsed; //使用的颜色数，如果为0，则表示默认值(2^颜色位数)
	uint32_t biClrImportant; //重要颜色数，如果为0，则表示所有颜色都是重要的
} BITMAPINFOHEADER;
PACKED_END

//调色板Palette，当然，这里是对那些需要调色板的位图文件而言的。24位和32位是不需要调色板的。
//（调色板结构体个数等于使用的颜色数，即是多少色图就有多少个，4位图16色，就有16个RGBQUAD结构体。）
PACKED_BEGIN
typedef struct tagRGBQUAD {
	//public:
	uint8_t rgbBlue; //该颜色的蓝色分量
	uint8_t rgbGreen; //该颜色的绿色分量
	uint8_t rgbRed; //该颜色的红色分量
	uint8_t rgbReserved; //保留值
} RGBQUAD;
PACKED_END
/*这里举个4位图也就是16色图的例子：一 个RGBQUAD结构体只占用4字节空间，
从左到右每个字节依次表示(蓝色，绿色，红色，未使用)。举例的这个图片我
数了数总共有16个RGBQUAD结 构体，由于该图片是4位图，2 ^ 4正好等于16，
所以它把16种颜色全部都枚举出来了，这些颜色就是一个颜色索引表。颜色索引
表编号从0开始，总共16个 颜色，所以编号为0 - 15。从winhex中可以看到按照顺序，这16个RGBQUAD结构体依次为：

编号：(蓝，绿，红，空)

0号：(00，00，00，00)

1号：(00，00，80，00)

2号：(00，80，00，00)

3号：(00，80，80，00)

4号：(80，00，00，00)

5号：(80，00，80，00)

6号：(80，80，00，00)

7号：(80，80，80，00)

8号：(C0，C0，C0，00)

9号：(00，00，FF，00)

10号：(00，FF，00，00)

11号：(00，FF，FF，00)

12号：(FF，00，00，00)

13号：(FF，00，FF，00)

14号：(FF，FF，00，00)

15号：(FF，FF，FF，00)

到这里，正好满足DIB数据区的偏移量，所以后面的字节就是图片内容了。这里需要
提醒的是所有的DIB数据扫描行是上下颠倒的，也就是说一幅图片先绘制底部的像素，
再绘制顶部的像素，所以这些DIB数据所表示的像素点就是从图片的左下角开始，一直表示到图片的右上角。*/

PACKED_BEGIN
typedef struct tagHEXIMAGEDATA {
	//public:
	char* imagehexdata;
	uint16_t imagedatasize;
} HEXIMAGEDATA;
PACKED_END

/** 将XML文件中的BMP位图数据流转成十六进制数据
 *
 * @param[in]  src			从XML中解析出来的原始BMP位图流数据
 * @param[out] data         转换后的十六进制数据(一个字节一组数据)
 */
	void GetHexData(const char* src, HEXIMAGEDATA* data);

/** 得到bmp位图文件头信息
 *
 * @param[out] bmpFileHeader   位图文件头
 */
void Get_bmpFileHeader(BITMAPFILEHEADER* bmpFileHeader);

/** 得到bmp位图信息头信息
 *
 * @param[out] bmpInfo   位图信息头
 */
void Get_bmpInfo(BITMAPINFOHEADER* bmpInfo);

/** 得到bmp位图，会在本地磁盘中生成一个bmp位图文件
 *
 * @param[in] filename   要生成的bmp位图文件名 例如 "E:/1.bmp" or "1.bmp"
 */
unsigned int GetImageFile(char *filename);
