BOOL Thinning(HWND hWnd)

{

       DWORD                             OffBits,BufSize;

     LPBITMAPINFOHEADER    lpImgData;

       LPSTR                            lpPtr;

       HLOCAL                  hTempImgData;

       LPBITMAPINFOHEADER    lpTempImgData;

       LPSTR                   lpTempPtr;

       HDC                      hDc;

       HFILE                    hf;

       LONG                    x,y;

       int                                        num;

       BOOL                     Finished;

       int                        nw,n,ne,w,e,sw,s,se;

//为了处理的方便，仍采用256级灰度图，不过只用调色板中0和255两项

       if( NumColors!=256){

MessageBox(hWnd,"Must be a mono bitmap with grayscale palette!",

"Error Message",MB_OK|MB_ICONEXCLAMATION);

return FALSE;

}

OffBits=bf.bfOffBits-sizeof(BITMAPFILEHEADER);

//BufSize为缓冲区大小

       BufSize=OffBits+bi.biHeight*LineBytes;

//为新的缓冲区分配内存

       if((hTempImgData=LocalAlloc(LHND,BufSize))==NULL)

{

            MessageBox(hWnd,"Error alloc memory!","Error Message",

MB_OK|MB_ICONEXCLAMATION);

return FALSE;

}

     lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData);    

       lpTempImgData=(LPBITMAPINFOHEADER)LocalLock(hTempImgData);

       //拷贝头信息和位图数据     

       memcpy(lpTempImgData,lpImgData,BufSize);

       //结束标志置成假

       Finished=FALSE;

while(!Finished){ //还没有结束

              //结束标志置成假

            Finished=TRUE;

       //先进行水平方向的细化

              for (y=1;y<bi.biHeight-1;y++){ //注意为防止越界，y的范围从1到高度-2

                     //lpPtr指向原图数据，lpTempPtr指向新图数据

                     lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);

                     lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);

                     x=1; //注意为防止越界，x的范围从1到宽度-2

                     while(x<bi.biWidth-1){

                            if(*(lpPtr+x)==0){ //是黑点才做处理

                                   w=(unsigned char)*(lpPtr+x-1);  //左邻点

                                   e=(unsigned char)*(lpPtr+x+1);  //右邻点

                                   if( (w==255)|| (e==255)){ 

//如果左右两个邻居中至少有一个是白点才处理

                                          nw=(unsigned char)*(lpPtr+x+LineBytes-1); //左上邻点

                                          n=(unsigned char)*(lpPtr+x+LineBytes); //上邻点

                                          ne=(unsigned char)*(lpPtr+x+LineBytes+1); //右上邻点

                                          sw=(unsigned char)*(lpPtr+x-LineBytes-1); //左下邻点

                                          s=(unsigned char)*(lpPtr+x-LineBytes); //下邻点

                                          se=(unsigned char)*(lpPtr+x-LineBytes+1); //右下邻点

                                          //计算索引

                            num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+

sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //经查表，可以删除

//在原图缓冲区中将该黑点删除

                                                 *(lpPtr+x)=(BYTE)255; 

//结果图中该黑点也删除

                                                 *(lpTempPtr+x)=(BYTE)255; 

                                                 Finished=FALSE; //有改动，结束标志置成假

                                                 x++; //水平方向跳过一个象素

                                          }

                                   }

                            }

                            x++; //扫描下一个象素

                     }

              }

       //再进行垂直方向的细化

              for (x=1;x<bi.biWidth-1;x++){ //注意为防止越界，x的范围从1到宽度-2

                     y=1; //注意为防止越界，y的范围从1到高度-2

                     while(y<bi.biHeight-1){

                            lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);

                            lpTempPtr=(char*)lpTempImgData+

(BufSize-LineBytes-y*LineBytes);

                            if(*(lpPtr+x)==0){ //是黑点才做处理

                                   n=(unsigned char)*(lpPtr+x+LineBytes);

                                   s=(unsigned char)*(lpPtr+x-LineBytes);

                                   if( (n==255)|| (s==255)){

//如果上下两个邻居中至少有一个是白点才处理

                                          nw=(unsigned char)*(lpPtr+x+LineBytes-1);

                                          ne=(unsigned char)*(lpPtr+x+LineBytes+1);

                                          w=(unsigned char)*(lpPtr+x-1);

                                          e=(unsigned char)*(lpPtr+x+1);

                                          sw=(unsigned char)*(lpPtr+x-LineBytes-1);

                                          se=(unsigned char)*(lpPtr+x-LineBytes+1);

                                          //计算索引

num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+

sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //经查表，可以删除

//在原图缓冲区中将该黑点删除

                                                 *(lpPtr+x)=(BYTE)255; 

//结果图中该黑点也删除

                                                 *(lpTempPtr+x)=(BYTE)255; 

                                                 Finished=FALSE; //有改动，结束标志置成假

                                                 y++;//垂直方向跳过一个象素

                                          }

                                   }

                            }

                            y++; //扫描下一个象素

                     }

              } 

}

     if(hBitmap!=NULL)

           DeleteObject(hBitmap);

       hDc=GetDC(hWnd);     

       //产生新的位图

       hBitmap=CreateDIBitmap(hDc,(LPBITMAPINFOHEADER)lpTempImgData,

(LONG)CBM_INIT,

(LPSTR)lpTempImgData+

sizeof(BITMAPINFOHEADER)+

NumColors*sizeof(RGBQUAD),

(LPBITMAPINFO)lpTempImgData,

DIB_RGB_COLORS);

hf=_lcreat("c:\\thinning.bmp",0);

       _lwrite(hf,(LPSTR)&bf,sizeof(BITMAPFILEHEADER)); 

       _lwrite(hf,(LPSTR)lpTempImgData,BufSize);

       _lclose(hf);

       //释放内存及资源

      ReleaseDC(hWnd,hDc);

       LocalUnlock(hTempImgData);

       LocalFree(hTempImgData);

       GlobalUnlock(hImgData);

       return TRUE;

}