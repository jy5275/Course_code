#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<iomanip>
//#include "windef.h"
using namespace std;
char useless[1000];
struct _BITMAPFILEHEADER {		//文件头:【14 Bytes】
	WORD bfType;	// 位图文件的类型，必须为“BM”,2B
	DWORD bfSize;	// 【位图文件大小】，字节为单位,4B
	WORD bfReserved1;	// 位图文件保留字，必须为0
	WORD bfReserved2;	// 位图文件保留字，必须为0
	DWORD bfOffBits;	// 位图数据的起始位置，以相对于位图文件头的偏移量表示，字节为单位
};
struct _BITMAPINFOHEADER {	//位图信息头【40 Byte】
	DWORD biSize;	// 本结构所占用字节数
	LONG biWidth;	// 【位图宽度】，以像素为单位【Modify】0x200 = 512
	LONG biHeight;	// 【位图高度】，以像素为单位【Modify】0x1E4 = 484
	WORD biPlanes;	// 目标设备的平面数，必须为1

	WORD biBitCount;// 每像素所需位数，必须是1(2色),4(16色),8(256色)或24(真彩色)之一
	DWORD biCompression; // 压缩类型，0(不压缩),1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一
	DWORD biSizeImage;	// 位图大小，字节为单位
	LONG biXPelsPerMeter;	// 水平分辨率，每米像素数【Modify】
	LONG biYPelsPerMeter;	// 垂直分辨率，每米像素数【Modify】
	DWORD biClrUsed;		// 实际使用的颜色表中的颜色数
	DWORD biClrImportant;	// 位图显示过程中重要的颜色数
};
struct image {
	char *str = NULL;
}srcImgData[2000][2000], destImgData[2000][2000];
int main(int argc, char *argv[]) {
	
	if (argc != 3) {
		cout << "Please input arguments as \"./rotatebmp [srcFileName] [destFileName]\"" << endl;
		_exit(0);
	}
	char *srcfile = argv[1], *destfile = argv[2];
	//const char *srcfile = "24.bmp", *destfile = "24out.bmp";
	int size, width, height, hres, vres, off, remoff = 0;
	short bit, bytes;

	FILE *psrcFile = fopen(srcfile, "rb");
	FILE *pdestFile = fopen(destfile, "wb+");

	fread(useless, sizeof(WORD), 1, psrcFile);
	fwrite(useless, sizeof(WORD), 1, pdestFile);

	remoff -= sizeof(WORD);

	fread(&size, sizeof(DWORD), 1, psrcFile);
	fwrite(&size, sizeof(DWORD), 1, pdestFile);
	remoff -= sizeof(DWORD);


	fread(useless, 2*sizeof(WORD), 1, psrcFile);
	fwrite(useless, 2*sizeof(WORD), 1, pdestFile);
	remoff -= 2 * sizeof(WORD);

	fread(&off, sizeof(DWORD), 1, psrcFile);
	fwrite(&off, sizeof(DWORD), 1, pdestFile);
	remoff -= sizeof(DWORD);
	remoff += off;


	fread(useless, sizeof(DWORD), 1, psrcFile);
	fwrite(useless, sizeof(DWORD), 1, pdestFile);
	remoff -= sizeof(DWORD);


	fread(&width, sizeof(LONG), 1, psrcFile);
	fread(&height, sizeof(LONG), 1, psrcFile);
	fwrite(&height, sizeof(LONG), 1, pdestFile);
	fwrite(&width, sizeof(LONG), 1, pdestFile);
	remoff -= 2 * sizeof(LONG);


	fread(useless, sizeof(WORD), 1, psrcFile);
	fwrite(useless, sizeof(WORD), 1, pdestFile);
	remoff -= sizeof(WORD);


	fread(&bit, sizeof(WORD), 1, psrcFile);
	fwrite(&bit, sizeof(WORD), 1, pdestFile);
	remoff -= sizeof(WORD);
	bytes = bit / 8;


	fread(useless, 2*sizeof(DWORD), 1, psrcFile);
	fwrite(useless, 2*sizeof(DWORD), 1, pdestFile);
	remoff -= 2 * sizeof(DWORD);

	fread(&hres, sizeof(LONG), 1, psrcFile);
	fwrite(&vres, sizeof(LONG), 1, pdestFile);
	fread(&hres, sizeof(LONG), 1, psrcFile);
	fwrite(&vres, sizeof(LONG), 1, pdestFile);
	remoff -= 2 * sizeof(LONG);

	fread(useless, 2 * sizeof(DWORD), 1, psrcFile);
	fwrite(useless, 2 * sizeof(DWORD), 1, pdestFile);
	remoff -= 2 * sizeof(DWORD);

	if (remoff != 0) {	//还有part3没读
		fread(useless, remoff, 1, psrcFile);
		fwrite(useless, remoff, 1, pdestFile);
	}

	for (int h = height - 1; h >= 0; h--)
		for (int w = 0; w < width; w++) {
			srcImgData[h][w].str = new char[bytes];
			destImgData[h][w].str = new char[bytes];
		}

	for (int h = height - 1; h >= 0; h--)
		for (int w = 0; w < width; w++)
			fread(srcImgData[h][w].str, bytes, 1, psrcFile);
	//Begin rotation!
	for (int w = width - 1; w >= 0; w--) {
		for (int h = height - 1; h >= 0; h--) {
			fwrite(srcImgData[h][w].str, bytes, 1, pdestFile);
		}
	}

	for (int h = height - 1; h >= 0; h--)
		for (int w = 0; w < width; w++) {
			delete[]srcImgData[h][w].str;
			delete[]destImgData[h][w].str;
		}

	fclose(psrcFile);
	fclose(pdestFile);
	return 0;
}