BOOL Dilation(HWND hWnd,BOOL Hori)

{

       DWORD                             OffBits,BufSize;

LPBITMAPINFOHEADER    lpImgData;

       LPSTR                   lpPtr;

       HLOCAL                  hTempImgData;

       LPBITMAPINFOHEADER    lpTempImgData;

       LPSTR                     lpTempPtr;

       HDC                     hDc;

       HFILE                    hf;

       LONG                    x,y;

       unsigned char              num;

       int                        i;

//为了处理的方便，仍采用256级灰度图，不过只调色板中0和255两项

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

       if(Hori)

       {   

//在水平方向进行膨胀运算

              for(y=0;y<bi.biHeight;y++){

                     //lpPtr指向原图数据，lpTempPtr指向新图数据

                     lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes)+1;

                     lpTempPtr=(char*)lpTempImgData+

(BufSize-LineBytes-y*LineBytes)+1;

                     for(x=1;x<bi.biWidth-1;x++){ 

//注意为防止越界，x的范围从1到宽度-2

                            num=(unsigned char)*lpPtr;

//原图中是黑点的，新图中肯定也是，所以要考虑的是那些原图

//中的白点，看是否有可能膨胀成黑点

                            if (num==255){

                                   *lpTempPtr=(unsigned char)255; //先置成白点

                                   for(i=0;i<3;i++){ 

                                          num=(unsigned char)*(lpPtr+i-1);

//只要左右邻居中有一个是黑点，就膨胀成黑点

                                          if(num==0){

*lpTempPtr=(unsigned char)0;

                                                 break;

                                          }

                                   }

                            }

//原图中就是黑点的，新图中仍是黑点

                            else *lpTempPtr=(unsigned char)0;

                            //指向下一个象素

                            lpPtr++;

                            lpTempPtr++;

                     }

              }

       }

       else{

//在垂直方向进行腐蚀运算

              for(y=1;y<bi.biHeight-1;y++){ //注意为防止越界，y的范围从1到高度-2

              lpPtr=(char *)lpImgData+(BufSize-LineBytes-y*LineBytes);

                     lpTempPtr=(char *)lpTempImgData+(BufSize-LineBytes-y*LineBytes);

                     for(x=0;x<bi.biWidth;x++){

                            num=(unsigned char)*lpPtr;

                            if (num==255){

                                   *lpTempPtr=(unsigned char)255;

                                   for(i=0;i<3;i++){

                                          num=(unsigned char)*(lpPtr+(i-1)*LineBytes);

//只要上下邻居中有一个是黑点，就膨胀成黑点

                                          if(num==0){

                                                 *lpTempPtr=(unsigned char)0;

                                                 break;

                                          }

                                   }

                            }

                            else *lpTempPtr=(unsigned char)0;

                            lpPtr++;

                            lpTempPtr++;

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

       //起不同的结果文件名

       if(Hori)

              hf=_lcreat("c:\\hdilation.bmp",0);

       else

              hf=_lcreat("c:\\vdilation.bmp",0);

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