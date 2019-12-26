#ifndef TIFREADER_H 
#define TIFREADER_H 
 
#include <stdio.h>
#include <string.h>
 
#ifndef NULL
#define NULL   0
#endif
 
#ifndef TRUE
#define TRUE   1
#define FALSE  0
#endif
 
 
typedef struct  
{
  unsigned short Byte_order;//
  unsigned short Version;//校验文件是否是TIF文件
  unsigned   int OffsetToFirstFID;//相对对文件开始处的偏移量
 // unsigned short wDECount;//多少目录入口
}IFH;
 
typedef struct
{
	unsigned short tag;//属性的编号
	unsigned short type;//数据类型
	unsigned long length;//数据的数量
	unsigned long valueOffset;//tag标识的属性代表的变量值相对文件开始处的偏移量
}DE;
typedef struct  
{
	int width;
	int height;
	
}Size;
typedef struct 
 {
	int *data;
}DATA;
typedef struct 
{
	DE *pde;
	int wDECount;
}PDE;
bool readTIF(char* path,IFH &ifh,PDE &de,Size &size,DATA &Data)
{
	unsigned char *data;
	int *dat;
    unsigned short wDECount;//多少目录入口
	
//	ZeroMemory(&ifh, sizeof(IFH));
//	ZeroMemory(&de, sizeof(DE));
 
    FILE *fp;
    fp=fopen(path,"rb");
	if(fp == NULL)
	{
		cout<<"open file error"<<endl;
		return false;
	}
	if(sizeof(IFH) != fread(&ifh, 1,sizeof(IFH),fp))
	{
        cout<<"读TIF文件头失败";
        return FALSE;
	}
	 if(0x2a != ifh.Version)
	 {
		  cout<<"该文件不是TIF格式，读文件失败";
		  return FALSE;
	 }
 
	 if(0x4949 != ifh.Byte_order)
	 {
		  cout<<"该TIF文件不是IBMPC字节序，读文件失败";
		  return FALSE;
	 }
 
	 fseek(fp,ifh.OffsetToFirstFID,SEEK_SET);//将文件指针定位到IFD
     //读文件有多少个目录入口 
	if(2 != fread(&wDECount,1,sizeof(unsigned short),fp))
	 {
		  cout<<"无法获得TIF文件目录入口数量";
		  return FALSE;
	 }
	cout<<"该TIF文件有"<<wDECount<<"个目录入口"<<endl;
    //创建DE数组，接收信息，数组中有wDECount个元素 
    de.pde = new DE[wDECount];
    DE* pTemp = de.pde;
	de.wDECount = wDECount;
    memset(de.pde, 0, sizeof(DE)*wDECount);
	 if(sizeof(DE)*wDECount != fread(de.pde,1, sizeof(DE)*wDECount,fp))
	 {
		  cout<<"读图象文件目录失败";
		  delete []de.pde;
		  return false ;
	 }
    //把图像的大小和图像数据的容量保存到成员变量中
	 int m_size_x;
	 int m_size_y;
	 int m_size;
	 int i;
	for(i=0; i<wDECount; i++)
	 {
		  pTemp =de.pde + i;
		  if(256 == pTemp->tag) //tag为256的目录入口中的变量标识了图象宽度
		  {
		      m_size_x = pTemp->valueOffset;
		  }
		  if(257 == pTemp->tag) //图象高度
		  {
		      m_size_y = pTemp->valueOffset;
		  }
		  if(273 == pTemp->tag) //计算图象数据占用字节数
		  {
		   //m_dwBmSize = pTemp->valueOffset - sizeof(IFH);
		   //或者把tag=256的valueOffset乘以tag=257的valueOffset
		      m_size = m_size_x * m_size_y;
		  }
	}
    //填充所有像素数据, 颠倒图象数据从最后一行开始读起
	 int j = 0;
	// int i = 0;
	 data = (unsigned char*)malloc(m_size*sizeof(BYTE));
	 dat = (int*)malloc(m_size*sizeof(int));
	 for(i=m_size_y-1; i>=0; i--)
	 {
		 fseek(fp,sizeof(IFH) + i*m_size_x, SEEK_SET);
		 fread((BYTE*)(data + 1) + j*m_size_x,sizeof(BYTE), m_size_x,fp);
		  j++;
	 }
	 cout<<"width:"<<m_size_x<<endl;
     cout<<"height:"<<m_size_y<<endl;
	 unsigned char* p;
	 p = data;
	 int *ptr;
	 ptr = dat;
	 for (i=0;i<m_size;i++,p++,ptr++)
	 {
		 *ptr = (int)(*p);
		 int  h= *ptr;
		// cout<<h<<" ";
	 }
	 size.width = m_size_x;
	 size.height = m_size_y;
	 Data.data = dat;
	 return TRUE;
  
}
bool saveTIF(char* path,IFH ifh,PDE de,Size size,DATA Data)
{
	unsigned char *data;
//    unsigned short wDECount;//多少目录入口
	
//	ZeroMemory(&ifh, sizeof(IFH));
//	ZeroMemory(&de, sizeof(DE));
 
    FILE *fp;
    fp=fopen(path,"wb");
	if(fp == NULL)
	{
		cout<<"open file error"<<endl;
		return false;
	}
	if(sizeof(IFH) != fwrite(&ifh, 1,sizeof(IFH),fp))
	{
        cout<<"写TIF文件头失败";
        return FALSE;
	}
	 fseek(fp,ifh.OffsetToFirstFID,SEEK_SET);//将文件指针定位到IFD
     //读文件有多少个目录入口 
	if(2 != fwrite(&de.wDECount,1,sizeof(unsigned short),fp))
	 {
		  cout<<"无法获得TIF文件目录入口数量";
		  return FALSE;
	 }
    //创建DE数组，接收信息，数组中有wDECount个元素 
 
	 if(sizeof(DE)*de.wDECount != fwrite(de.pde,1, sizeof(DE)*de.wDECount,fp))
	 {
		  cout<<"读图象文件目录失败";
		  return false ;
	 }
    //填充所有像素数据, 颠倒图象数据从最后一行开始读起
	 int j = 0;
	 int i = 0;
	 data = (unsigned char*)malloc(size.width*size.height*sizeof(BYTE));
	 int *ptr = Data.data;
 
	 unsigned char* p;
	 p = data;
	 for (i=0;i<size.width*size.height;i++,p++,ptr++)
	 {
		 *p = (unsigned char)(*ptr);
		// int  h= *ptr;
		// cout<<h<<" ";
	 }	
	 for(i=size.height-1; i>=0; i--)
	 {
		 fseek(fp,sizeof(IFH) + i*size.width, SEEK_SET);
		 fwrite((BYTE*)(data + 1) + j*size.width,sizeof(BYTE), size.width,fp);
		  j++;
	 }
 
	 return TRUE;
  
}
#endif