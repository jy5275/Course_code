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
	//const char *srcfile = "32.bmp", *destfile = "32out.bmp";
	int size, width, height, hres, vres, off, remoff = 0;
	short bit, bytes;
	ifstream srcFile(srcfile, ios::in | ios::binary);
	if (!srcFile) { cout << "Open image error" << endl; _exit(0); }
	ofstream destFile(destfile, ios::app | ios::binary);
	if (!srcFile) { cout << "Open image error" << endl; _exit(0); }

	srcFile.read(useless, sizeof(WORD));	//读取文件大小之前的
	destFile.write(useless, sizeof(WORD));
	remoff -= sizeof(WORD);

	srcFile.read((char*)(&size), sizeof(DWORD));	//读取文件大小
	destFile.write((char*)(&size), sizeof(DWORD));
	remoff -= sizeof(DWORD);

	srcFile.read(useless, 2 * sizeof(WORD));	//没用的信息...
	destFile.write(useless, 2 * sizeof(WORD));
	remoff -= 2*sizeof(WORD);

	srcFile.read((char*)(&off), sizeof(DWORD));	//读取文件offset
	destFile.write((char*)(&off), sizeof(DWORD));
	remoff -= sizeof(DWORD);
	remoff += off;

	srcFile.read(useless, sizeof(DWORD));	//没用的信息...
	destFile.write(useless, sizeof(DWORD));
	remoff -= sizeof(DWORD);

	srcFile.read((char*)(&width), sizeof(LONG));
	srcFile.read((char*)(&height), sizeof(LONG));
	destFile.write((char*)(&height), sizeof(LONG));
	destFile.write((char*)(&width), sizeof(LONG));
	remoff -= 2*sizeof(LONG);

	srcFile.read(useless, sizeof(WORD));	//没用的信息...
	destFile.write(useless, sizeof(WORD));
	remoff -= sizeof(WORD);

	srcFile.read((char*)(&bit), sizeof(WORD));	//位数...
	destFile.write((char*)(&bit), sizeof(WORD));
	remoff -= sizeof(WORD);
	bytes = bit / 8;

	srcFile.read(useless, 2 * sizeof(DWORD));	//没用的信息...
	destFile.write(useless,2 * sizeof(DWORD));
	remoff -= 2 * sizeof(DWORD);

	srcFile.read((char*)(&hres), sizeof(LONG));
	srcFile.read((char*)(&vres), sizeof(LONG));
	destFile.write((char*)(&vres), sizeof(LONG));
	destFile.write((char*)(&hres), sizeof(LONG));
	remoff -= 2 * sizeof(LONG);

	srcFile.read(useless, 2 * sizeof(DWORD));	//没用的信息...
	destFile.write(useless, 2 * sizeof(DWORD));
	remoff -= 2 * sizeof(DWORD);

	if (remoff != 0) {	//还有part3没读
		srcFile.read(useless, remoff);
		destFile.write(useless, remoff);
	}

	for (int h = height - 1; h >= 0; h--)
		for (int w = 0; w < width; w++) {
			srcImgData[h][w].str = new char[bytes];
			destImgData[h][w].str = new char[bytes];
		}
	
	for (int h = height - 1; h >= 0; h--)
		for (int w = 0; w < width; w++)
			srcFile.read(srcImgData[h][w].str, bytes);
	//Begin rotation!
	for (int w = width - 1; w >= 0; w--) {
		for (int h = height - 1; h >= 0; h--) {
			destFile.write(srcImgData[h][w].str, bytes);
		}
	}

	for (int h = height - 1; h >= 0; h--)
		for (int w = 0; w < width; w++) {
			delete []srcImgData[h][w].str;
			delete []destImgData[h][w].str;
		}
	
	srcFile.close();
	destFile.close();

	return 0;
}