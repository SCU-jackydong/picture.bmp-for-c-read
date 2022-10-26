#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
 #pragma()
/* 定义WORD为两个字节的类型 */
typedef unsigned short WORD;
/* 定义DWORD为四个字节的类型 */
typedef unsigned int DWORD;
 
/* 位图文件头主要是对位图文件的一些描述 位图信息头主要是对位图图像方面信息的描述 */
/*************************** 位图标准信息(54字节) ******************************************/
/* 位图文件头 （位图头的字节数 = 位图文件字节数 - 位图图像数据字节数）*/
typedef struct BMP_FILE_HEADER
{
	WORD bType;      // 文件标识符 
	DWORD bSize;     // 文件的大小 
	WORD bReserved1; // 保留值,必须设置为0  
	WORD bReserved2; // 保留值,必须设置为0 
	DWORD bOffset;   // 文件头的最后到图像数据位开始的偏移量 
} __attribute__((packed)) BMPFILEHEADER;     // 14 字节
 
/* 位图信息头 */

typedef struct BMP_INFO
{
	DWORD bInfoSize;            // 信息头的大小   
	DWORD bWidth;               // 图像的宽度     
	DWORD bHeight;              // 图像的高度     
	WORD bPlanes;               // 图像的位面数   
	WORD bBitCount;             // 每个像素的位数 
	DWORD bCompression;         // 压缩类型 
	DWORD bmpImageSize;         // 图像的大小,以字节为单位 
	DWORD bXPelsPerMeter;       // 水平分辨率 
	DWORD bYPelsPerMeter;       // 垂直分辨率 
	DWORD bClrUsed;             // 使用的色彩数 
	DWORD bClrImportant;        // 重要的颜色数 
} __attribute__((packed))  BMPINF;            // 40 字节
 
/* 彩色表:调色板 */
typedef struct RGB_QUAD 
{
	char rgbBlue;     // 蓝色强度 
	char rgbGreen;    // 绿色强度 
	char rgbRed;      // 红色强度 
	char rgbReversed; // 保留值 
} __attribute__((packed)) RGBQUAD;

 
int main(int argc, char *argv[ ])
{

while(1)
{
char str1[100];
char str2[100];

printf("请输入要处理的图片路径\n");
scanf("%s",str1);
printf("请输入图片处理后的输出路径\n");
scanf("%s",str2);




pid_t pid =fork();
if(pid==-1)
{
printf("无法创建进程");
}
else if(pid==0)
{
FILE *fp;                     // 定义一个文件指针
	BMPFILEHEADER bmpFileHeader;  // 定义一个 BMP 文件头的结构体
	BMPINF bmpInfo;               // 定义一个 BMP 文件信息结构体 
    RGBQUAD bgr;
    



	// "rb" 只读打开一个二进制文件，只允许读数据。'b'指的是让这个库函数以二进制形式打开此文件。
	// 读取失败会返回空指针，读取成功后，fp 会指向一块具有 bmp 属性的内存,我们可以对这块内存开始操作
	if((fp = fopen(str1, "rb")) == NULL) // fp = 0x00426aa0
	{
		printf("Cann't open the file!\n");
		return 0;
	}
 
	// 让 fp 指向 bmp 文件的开始 
	// 第 2 个参数是偏移量 第三个参数是文件起始地址 所以此函数执行成功后文件指针会指向文件的开始
	fseek(fp, 0, SEEK_SET);                            // fp = 0000
 
	// 读取文件信息
	/*
		参数1: 读出数据的存放缓冲区
		参数2: 读取多少个字节的数据
		参数3: 读取几包这样的数据
		参数4: 文件指针（源数据）
	*/
	fread(&bmpFileHeader, 14, 1, fp); 
	
	fread(&bmpInfo, 40, 1, fp);
   
 
 
	// 输出BMP文件的位图文件头的所有信息
    //int arr[bmpInfo.bWidth][bmpInfo.bHeight];
    unsigned char  *p;
    p = (unsigned char *)malloc(sizeof(unsigned char )* bmpInfo.bHeight*bmpInfo.bWidth);
        unsigned char  *p1;
    p1 = (unsigned char *)malloc(sizeof(unsigned char )*1024);
   fread(p1,1024,1,fp);
    fread(p, bmpInfo.bHeight*bmpInfo.bWidth,1,fp);

	for(int i=0;i<bmpInfo.bHeight*bmpInfo.bWidth;i++)
	{
		if(p[i]>80)
		{
			p[i]=255;
		}
		else{
			p[i]=0;
		}
	}
printf("文件头大小%ld \n",sizeof(BMPFILEHEADER));
printf("文件信息大小%ld \n",sizeof(BMPINF));
printf("调色板信息大小%ld \n",sizeof(RGBQUAD));


	printf("BMP 文件大小 = %d 字节\n", bmpFileHeader.bSize);


 
	// 输出BMP文件的位图信息头的所有信息

	printf("psinyi = 0X%X\n", bmpFileHeader.bOffset);
	printf("信息头的大小 = %d 字节\n", bmpInfo.bInfoSize);
	printf("位图的高度 = %d \n", bmpInfo.bHeight);
	printf("位图的宽度 = %d \n", bmpInfo.bWidth);

	printf("每个像素的位数 = %d 位\n", bmpInfo.bBitCount);


	printf("图像的大小 = %d 字节\n", bmpInfo.bmpImageSize);

 
FILE *fwp;

if((fwp = fopen(str2,"wb")) == NULL)
{
		printf("Cann't create the file!\n");
		return 0;
	}
    fseek(fwp, 0, SEEK_SET);   
    fwrite(&bmpFileHeader, 14, 1, fwp);
    fwrite(&bmpInfo, 40, 1, fwp);
    
    fwrite(p1, 1024, 1, fwp);

    fwrite(p, bmpInfo.bHeight*bmpInfo.bWidth, 1, fwp);

 free(p);
 free(p1);
	fclose(fp);
    fclose(fwp);
}
else{

}

	
 }

 
	return 0;
 
}