typedef enum _COLORTYPE
{
    CMYK_C,
    CMYK_M,
    CMYK_Y,
    CMYK_K,
    CMYK_LC,
    CMYK_LM,
    CMYK_LY,
    CMYK_G
}COLORTYPE;
/**************************************************************************
* @file   		ConvertPrnToPixmap
* @brief		将 prn 文件转化为 Pixmap
* @param		QString strPrnFile		要转换的文件
*				char *&pBuff			接收转换成功的字符数组
*				int &iWidth				图片的宽
*				int &iHeight			图片的高
*				const int FormWidget	要显示图片的像素
*				QVector<COLORTYPE> *vec	组成图片色素的成分(单色、四色...)
* @return		void
* @note			void
* @author		赵向前
* @date			2019/8/2
***************************************************************************/
size_t ConvertPrnToPixmap(QString strPrnFile, char *&pBuff, int &iWidth, int &iHeight, const int FormWidget, QVector<COLORTYPE> *vec)
{
    //文件的宽和高（像素）
    int nViewportWidth, nViewportHeight;
    //prn 文件格式
    T_PRT1_IMAGEPROP prnHeader;

    QFile file(strPrnFile);
    if (file.exists() && file.open(QIODevice::ReadOnly))
    {
        //读取文件头
        file.read(reinterpret_cast<char *>(&prnHeader), sizeof(prnHeader));
        /**
        *	iPrnWidthInByte                 每一行的字节数
        *	prnHeader.nImageWidth          一行所包含的像素点
        *	prnHeader.GrayLevelBits        灰度级，每个像素由 2 个比特组成
        **/
        int iPrnWidthInByte = (prnHeader.nImageWidth * prnHeader.nGreyBit + 7) >> 3;
        //每一行像素所包含的字节
        int nByteOfLine = iPrnWidthInByte * static_cast<int>(prnHeader.nCntOfColors);

        //计算缩放比例
        int m_zoomRadio = (static_cast<int>(prnHeader.nImageWidth) + FormWidget - 1) / FormWidget;
        //为 nViewportWidth 和 nViewportHeight 赋值
        nViewportWidth = static_cast<int>(prnHeader.nImageWidth) / m_zoomRadio;
        nViewportHeight = static_cast<int>(prnHeader.nImageHeight) / m_zoomRadio;

        //掩码
        uchar ucMask = (prnHeader.nGreyBit == 1) ? 0x1 : 0x3;
        int nShiftMask = (prnHeader.nGreyBit == 1) ? 0x7 : 0x3;

        char *pSrc = new char[nByteOfLine];
        //计算 CMYLLcLmLyG 的位置
        uchar *pSrcCMYK;
        //nBMPWidthBytes 将上述的 prn 图片转换为 bmp 图片每行所需的字节数
        //转化为 bmp 图片，该图片的位深是 32 (即每个像素点用 32 bit 表示)
        int nBMPWidthBytes = (nViewportWidth * HT_BITMAPBITSCONT + 7) / 8;

        //计算bmp图像像素所需的总字节数
        int nDataSize = nBMPWidthBytes * nViewportHeight;
        //计算目标文件大小
        pBuff = new char[sizeof(BITMAP_FILE_HEADER) + sizeof(BITMAP_INFO_HEADER) + static_cast<unsigned long>(nDataSize)];
        //获取目标文件头
        BITMAP_FILE_HEADER *pHeader = reinterpret_cast<BITMAP_FILE_HEADER *>(pBuff);
        //获取目标文件信息
        BITMAP_INFO_HEADER *pInfo = reinterpret_cast<BITMAP_INFO_HEADER *>(pBuff + sizeof(BITMAP_FILE_HEADER));
        //bmp文件头填充
        pHeader->bfType = MAKEWORD('B', 'M');
        pHeader->bfOffBits = sizeof(BITMAP_FILE_HEADER) + sizeof(BITMAP_INFO_HEADER);
        pHeader->bfSize = pHeader->bfOffBits + nDataSize;
        pHeader->bfReserved1 = pHeader->bfReserved2 = 0;

        pInfo->biSize = sizeof(BITMAP_INFO_HEADER);
        pInfo->biWidth = nViewportWidth;
        pInfo->biHeight = -nViewportHeight;
        pInfo->biPlanes = 1;
        pInfo->biBitCount = HT_BITMAPBITSCONT;
        pInfo->biCompression = 0;
        pInfo->biSizeImage = nDataSize;
        pInfo->biXPelsPerMeter = pInfo->biYPelsPerMeter = 0;
        pInfo->biClrUsed = pInfo->biClrImportant = 0;

        unsigned int nMax = (prnHeader.nGreyBit == 1) ? 1 : 3;
        if (prnHeader.nGreyBit == 8)
            nMax = 255;

        //pData用来遍历bmp文件的内存区
        char *pData = reinterpret_cast<char *>(pBuff + pHeader->bfOffBits);
        //高度为循环第一层
        qint64 ret;
        for (int i = 0, k = 0; i < nViewportHeight; i++)
        {
            while(1)
            {
                ret = file.read(pSrc, nByteOfLine);
                if(k++ % m_zoomRadio == 0)
                {
                    break;
                }
            }
            if(ret <= 0)
            {
                break;
            }

            Pixel *pPixel = reinterpret_cast<Pixel *>(pData);
            int nPos = 0;
            //宽度为第二层
            for (int j = 0; j< nViewportWidth; j++)
            {
                unsigned int valC = 0, valM = 0, valY = 0, valK = 0, valLC = 0, valLM = 0, valLY = 0, valG = 0;
                //使用四种颜色
                if (prnHeader.nGreyBit == 8)
                {
                    for (int k = 0; k < vec->size(); k++)
                    {
                        pSrcCMYK = reinterpret_cast<uchar *>(pSrc) + iPrnWidthInByte * k;
                        switch (vec->at(k))
                        {
                        case 0:
                            valC = pSrcCMYK[nPos];
                            break;
                        case 1:
                            valM = pSrcCMYK[nPos];
                            break;
                        case 2:
                            valY = pSrcCMYK[nPos];
                            break;
                        case 3:
                            valK = pSrcCMYK[nPos];
                            break;
                        case 4:
                            valLC = pSrcCMYK[nPos];
                            break;
                        case 5:
                            valLM = pSrcCMYK[nPos];
                            break;
                        case 6:
                            valLY = pSrcCMYK[nPos];
                            break;
                        case 7:
                            valG = pSrcCMYK[nPos];
                            break;
                        }
                    }
                    nPos += m_zoomRadio;
                }
                else
                {
                    //不是使用四种颜色
                    int nShift = (nShiftMask - (j&nShiftMask)) * static_cast<int>(prnHeader.nGreyBit);
                    for (int k = 0; k < vec->size(); k++)
                    {
                        pSrcCMYK = reinterpret_cast<uchar *>(pSrc) + iPrnWidthInByte * k;
                        switch (vec->at(k))
                        {
                        case 0:
                            valC = (pSrcCMYK[nPos] >> nShift) & ucMask;
                            break;
                        case 1:
                            valM = (pSrcCMYK[nPos] >> nShift) & ucMask;
                            break;
                        case 2:
                            valY = (pSrcCMYK[nPos] >> nShift) & ucMask;
                            break;
                        case 3:
                            valK = (pSrcCMYK[nPos] >> nShift) & ucMask;
                            break;
                        case 4:
                            valLC = (pSrcCMYK[nPos] >> nShift) & ucMask;
                            break;
                        case 5:
                            valLM = (pSrcCMYK[nPos] >> nShift) & ucMask;
                            break;
                        case 6:
                            valLY = (pSrcCMYK[nPos] >> nShift) & ucMask;
                            break;
                        case 7:
                            valG = (pSrcCMYK[nPos] >> nShift) & ucMask;
                            break;
                        }
                    }
                    if (nShift == 0)
                        nPos += m_zoomRadio;
                }
				//将valLC、valLM、valLY、valG合并到valC、valM、valY、valK中
				//mergeCMYK(valLC, valLM, valLY, valG, valC, valM, valY, valK);
                //将rgb值写入bmp的对应像素位
                pPixel[j].rgbRed = char(qreal(nMax - valC) / nMax * (nMax - valK) / nMax * 255);
                pPixel[j].rgbGreen = char(qreal(nMax - valM) / nMax * (nMax - valK) / nMax * 255);
                pPixel[j].rgbBlue = char(qreal(nMax - valY) / nMax * (nMax - valK) / nMax * 255);

            }
            pData += nBMPWidthBytes;
        }
        delete[]pSrc;

        iWidth = nViewportWidth;
        iHeight = nViewportHeight;
        file.close();
        return sizeof(BITMAP_FILE_HEADER) + sizeof(BITMAP_INFO_HEADER) + static_cast<unsigned long>(nDataSize);
    }
    return 0;
}
//将valLC、valLM、valLY、valG合并到valC、valM、valY、valK中
void mergeCMYK(const int valLC, const int valLM, const int valLY, const int valG, 
					int &valC, int &valM, int &valY, int &valK)
{
	valC += valLC / settingLight * 255;
	valM += valLM / settingLight * 255;
	valY += valLY / settingLight * 255;
	valK += valG / settingLight * 255;
}
//读取xml文档
void ReadXmlFile(QString ColorXmlFile, QVector<COLORTYPE> &vec)
{
    QString strRoot = "root";
    Xml colorXml(ColorXmlFile, strRoot);
    //获取节点的值
    QDomNodeList colorList = colorXml.GetRoot()->childNodes();
    for(int i = 0; i < colorList.size(); i++)
    {
        if(colorList.at(i).nodeName() == "colors")
        {
            QDomNodeList colorsList = colorList.at(i).childNodes();
            for(int i = 0; i < colorsList.size(); i++)
            {
                if(colorsList.at(i).nodeName() == "basic")
                {
                    QDomNodeList basicList = colorsList.at(i).childNodes();
                    for(int i = 0; i < basicList.size(); i++)
                    {
                        if(basicList.at(i).nodeName() == "cyan")
                            vec.append(CMYK_C);
                        if(basicList.at(i).nodeName() == "megenta")
                            vec.append(CMYK_M);
                        if(basicList.at(i).nodeName() == "yellow")
                            vec.append(CMYK_Y);
                        if(basicList.at(i).nodeName() == "black")
                            vec.append(CMYK_K);
                    }
                }
                else if(colorsList.at(i).nodeName() == "light")
                {
                    QDomNodeList lightList = colorsList.at(i).childNodes();
                    for(int i = 0; i < lightList.size(); i++)
                    {
                        if(lightList.at(i).nodeName() == "light_cyan")
                            vec.append(CMYK_LC);
                        if(lightList.at(i).nodeName() == "light_megenta")
                            vec.append(CMYK_LM);
                        if(lightList.at(i).nodeName() == "light_yellow")
                            vec.append(CMYK_LY);
                        if(lightList.at(i).nodeName() == "light_black")
                            vec.append(CMYK_G);
                    }
                }
            }
        }
    }
}
