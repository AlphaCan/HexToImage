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


/*BITMAPFILEHEADER�ĵ�1��������bfType(2�ֽ�)������㶨����0x4D42�������ڴ�
�е��������и�λ���󣬵�λ���ң������ڴ��д������ҿ�����ʾ��(42 4D)��������
winhex��ͷ���� �ֽ���ʾΪ(42 4D)���������γɵģ��Ժ�����ݶ�������ص㣬����
���ظ�˵����

BITMAPFILEHEADER�ĵ�2��������bfSize(4�ֽ�)����ʾ����bmp�ļ��Ĵ�С��

BITMAPFILEHEADER�ĵ�3������4�����Էֱ���bfReserved1��bfReserved2(��2�ֽ�)����
����2���������ԣ���Ϊ0���������&H0000��0x0000��

BITMAPFILEHEADER�ĵ�5��������bfOffBits(4�ֽ�)����ʾDIB��������bmp�ļ��е�λ��
ƫ�������������0x00000076=118����ʾ���������ļ���ʼ��������118�ֽڿ�ʼ��

 BITMAPFILEHEADER�ṹ������ͽ����ˣ���һᷢ��BITMAPFILEHEADERֻռ��bmp�ļ�
 ��ʼ��14�ֽڳ��ȣ�����Ҫ �ر�˵�����ǣ������ڱ��ʱ���������Զ����Ƶ���ʽ��
 ��һ��bmp�ļ���Ȼ���俪ͷ��14���ֽڶ����Լ������BITMAPFILEHEADER �ṹ����
 ���������������ṹ��ķ�ʽ����Ҫע�⣬����Լ�����Ľṹ�����ڴ��������ֽ�
���룬��ռ��16�ֽڵĿռ䣬���ֱ�Ӷ���16�ֽڣ����ֽ�˳�� ��ֵ���ṹ�壬������
�����Ǵ���ģ������Ļ��������Ƚ���14�ֽڵ����ݶ��뵽һ���������У�Ȼ��ӻ���
���а��ֽڶԽṹ����и�ֵ����ϸ�������¼�� ���ڴ���ԭ����vb�ж���һ��
BITMAPFILEHEADER�ṹ��������䳤��ռ��16���ֽڣ�ԭ����ǵ�1�����Ա���Ӧ��ֻ
����2���ֽڣ���ʵ�ʱ� ������4���ֽڣ������2���ֽڣ���������뱣��һ��bmpͼƬ��
д��BITMAPFILEHEADER�ṹ��ʱһ��Ҫע����һ�㡣*/

PACKED_BEGIN
typedef struct  tagBITMAPFILEHEADER {
	uint16_t bfType;//�̶�Ϊ0x4d42; 
	uint32_t bfSize; //�ļ���С
	uint16_t bfReserved1; //�����֣�������
	uint16_t bfReserved2; //�����֣�ͬ��
	uint32_t bfOffBits; //ʵ��λͼ���ݵ�ƫ���ֽ�������ǰ�������ֳ���֮��
} BITMAPFILEHEADER;
PACKED_END

/*
BITMAPINFOHEADER�ĵ�1��������biSize(4�ֽ�)����ʾBITMAPINFOHEADER�ṹ��ĳ��ȣ�����ĳ�����40�ֽڡ�

BITMAPINFOHEADER�ĵ�2��������biWidth(4�ֽ�)����ʾbmpͼƬ�Ŀ��

BITMAPINFOHEADER�ĵ�3��������biHeight(4�ֽ�)����ʾbmpͼƬ�ĸ߶�

BITMAPINFOHEADER�ĵ�4��������biPlanes(2�ֽ�)����ʾbmpͼƬ��ƽ��������Ȼ��ʾ��ֻ��һ��ƽ�棬���Ժ����1���������0x0001��

BITMAPINFOHEADER�ĵ�5��������biBitCount(2�ֽ�)����ʾbmpͼƬ����ɫλ������1λͼ����ɫ���ֵͼ�񣩣�8λͼ��16λͼ��24λͼ��32λͼ�ȵȡ�

BITMAPINFOHEADER�ĵ�6��������biCompression(4�ֽ�)����ʾͼƬ��ѹ�����ԣ�bmpͼƬ�ǲ�ѹ���ģ�����0����������Ϊ0x00000000��

BITMAPINFOHEADER�ĵ�7��������biSizeImage(4�ֽ�)����ʾbmpͼƬ�������Ĵ�С������һ����ֵbiCompression����0ʱ�������ֵ����ʡ�Բ�������������0x00000000��

BITMAPINFOHEADER�ĵ�8��������biXPelsPerMeter(4�ֽ�)����ʾͼƬX��ÿ�׶������أ���ʡ�ԣ��������0x00000EC3=3779����/�ס�

BITMAPINFOHEADER�ĵ�9��������biYPelsPerMeter(4�ֽ�)����ʾͼƬY��ÿ�׶������أ���ʡ�ԣ��������0x00000EC3=3779����/�ס�

BITMAPINFOHEADER�ĵ�10��������biClrUsed(4�ֽ�)����ʾʹ���˶��ٸ���ɫ������һ��biBitCount����С��16�Ż��õ�������0ʱ��ʾ��2^biBitCount����ɫ���������������Ե���0x00000000��

BITMAPINFOHEADER�ĵ�11��������biClrImportant(4�ֽ�)����ʾ�ж��ٸ���Ҫ����ɫ������0ʱ��ʾ������ɫ������Ҫ�������������0x00000000��
*/
PACKED_BEGIN
typedef struct tagBITMAPINFOHEADER {
	//public:
	uint32_t biSize; //ָ���˽ṹ��ĳ��ȣ�Ϊ40
	int biWidth; //λͼ��
	int biHeight; //λͼ��
	uint16_t biPlanes; //ƽ������Ϊ1
	uint16_t biBitCount; //������ɫλ����������1��2��4��8��16��24���µĿ�����32
	uint32_t biCompression; //ѹ����ʽ��������0��1��2������0��ʾ��ѹ��
	uint32_t biSizeImage; //ʵ��λͼ����ռ�õ��ֽ���
	int biXPelsPerMeter; //X����ֱ���
	int biYPelsPerMeter; //Y����ֱ���
	uint32_t biClrUsed; //ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��)
	uint32_t biClrImportant; //��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ��
} BITMAPINFOHEADER;
PACKED_END

//��ɫ��Palette����Ȼ�������Ƕ���Щ��Ҫ��ɫ���λͼ�ļ����Եġ�24λ��32λ�ǲ���Ҫ��ɫ��ġ�
//����ɫ��ṹ���������ʹ�õ���ɫ�������Ƕ���ɫͼ���ж��ٸ���4λͼ16ɫ������16��RGBQUAD�ṹ�塣��
PACKED_BEGIN
typedef struct tagRGBQUAD {
	//public:
	uint8_t rgbBlue; //����ɫ����ɫ����
	uint8_t rgbGreen; //����ɫ����ɫ����
	uint8_t rgbRed; //����ɫ�ĺ�ɫ����
	uint8_t rgbReserved; //����ֵ
} RGBQUAD;
PACKED_END
/*����ٸ�4λͼҲ����16ɫͼ�����ӣ�һ ��RGBQUAD�ṹ��ֻռ��4�ֽڿռ䣬
������ÿ���ֽ����α�ʾ(��ɫ����ɫ����ɫ��δʹ��)�����������ͼƬ��
�������ܹ���16��RGBQUAD�� ���壬���ڸ�ͼƬ��4λͼ��2 ^ 4���õ���16��
��������16����ɫȫ����ö�ٳ����ˣ���Щ��ɫ����һ����ɫ��������ɫ����
���Ŵ�0��ʼ���ܹ�16�� ��ɫ�����Ա��Ϊ0 - 15����winhex�п��Կ�������˳����16��RGBQUAD�ṹ������Ϊ��

��ţ�(�����̣��죬��)

0�ţ�(00��00��00��00)

1�ţ�(00��00��80��00)

2�ţ�(00��80��00��00)

3�ţ�(00��80��80��00)

4�ţ�(80��00��00��00)

5�ţ�(80��00��80��00)

6�ţ�(80��80��00��00)

7�ţ�(80��80��80��00)

8�ţ�(C0��C0��C0��00)

9�ţ�(00��00��FF��00)

10�ţ�(00��FF��00��00)

11�ţ�(00��FF��FF��00)

12�ţ�(FF��00��00��00)

13�ţ�(FF��00��FF��00)

14�ţ�(FF��FF��00��00)

15�ţ�(FF��FF��FF��00)

�������������DIB��������ƫ���������Ժ�����ֽھ���ͼƬ�����ˡ�������Ҫ
���ѵ������е�DIB����ɨ���������µߵ��ģ�Ҳ����˵һ��ͼƬ�Ȼ��Ƶײ������أ�
�ٻ��ƶ��������أ�������ЩDIB��������ʾ�����ص���Ǵ�ͼƬ�����½ǿ�ʼ��һֱ��ʾ��ͼƬ�����Ͻǡ�*/

PACKED_BEGIN
typedef struct tagHEXIMAGEDATA {
	//public:
	char* imagehexdata;
	uint16_t imagedatasize;
} HEXIMAGEDATA;
PACKED_END

/** ��XML�ļ��е�BMPλͼ������ת��ʮ����������
 *
 * @param[in]  src			��XML�н���������ԭʼBMPλͼ������
 * @param[out] data         ת�����ʮ����������(һ���ֽ�һ������)
 */
	void GetHexData(const char* src, HEXIMAGEDATA* data);

/** �õ�bmpλͼ�ļ�ͷ��Ϣ
 *
 * @param[out] bmpFileHeader   λͼ�ļ�ͷ
 */
void Get_bmpFileHeader(BITMAPFILEHEADER* bmpFileHeader);

/** �õ�bmpλͼ��Ϣͷ��Ϣ
 *
 * @param[out] bmpInfo   λͼ��Ϣͷ
 */
void Get_bmpInfo(BITMAPINFOHEADER* bmpInfo);

/** �õ�bmpλͼ�����ڱ��ش���������һ��bmpλͼ�ļ�
 *
 * @param[in] filename   Ҫ���ɵ�bmpλͼ�ļ��� ���� "E:/1.bmp" or "1.bmp"
 */
unsigned int GetImageFile(char *filename);
