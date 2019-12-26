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
* @brief		�� prn �ļ�ת��Ϊ Pixmap
* @param		QString strPrnFile		Ҫת�����ļ�
*				char *&pBuff			����ת���ɹ����ַ�����
*				int &iWidth				ͼƬ�Ŀ�
*				int &iHeight			ͼƬ�ĸ�
*				const int FormWidget	Ҫ��ʾͼƬ������
*				QVector<COLORTYPE> *vec	���ͼƬɫ�صĳɷ�(��ɫ����ɫ...)
* @return		void
* @note			void
* @author		����ǰ
* @date			2019/8/2
***************************************************************************/
size_t ConvertPrnToPixmap(QString strPrnFile, char *&pBuff, int &iWidth, int &iHeight, const int FormWidget, QVector<COLORTYPE> *vec)
{
    //�ļ��Ŀ�͸ߣ����أ�
    int nViewportWidth, nViewportHeight;
    //prn �ļ���ʽ
    T_PRT1_IMAGEPROP prnHeader;

    QFile file(strPrnFile);
    if (file.exists() && file.open(QIODevice::ReadOnly))
    {
        //��ȡ�ļ�ͷ
        file.read(reinterpret_cast<char *>(&prnHeader), sizeof(prnHeader));
        /**
        *	iPrnWidthInByte                 ÿһ�е��ֽ���
        *	prnHeader.nImageWidth          һ�������������ص�
        *	prnHeader.GrayLevelBits        �Ҷȼ���ÿ�������� 2 ���������
        **/
        int iPrnWidthInByte = (prnHeader.nImageWidth * prnHeader.nGreyBit + 7) >> 3;
        //ÿһ���������������ֽ�
        int nByteOfLine = iPrnWidthInByte * static_cast<int>(prnHeader.nCntOfColors);

        //�������ű���
        int m_zoomRadio = (static_cast<int>(prnHeader.nImageWidth) + FormWidget - 1) / FormWidget;
        //Ϊ nViewportWidth �� nViewportHeight ��ֵ
        nViewportWidth = static_cast<int>(prnHeader.nImageWidth) / m_zoomRadio;
        nViewportHeight = static_cast<int>(prnHeader.nImageHeight) / m_zoomRadio;

        //����
        uchar ucMask = (prnHeader.nGreyBit == 1) ? 0x1 : 0x3;
        int nShiftMask = (prnHeader.nGreyBit == 1) ? 0x7 : 0x3;

        char *pSrc = new char[nByteOfLine];
        //���� CMYLLcLmLyG ��λ��
        uchar *pSrcCMYK;
        //nBMPWidthBytes �������� prn ͼƬת��Ϊ bmp ͼƬÿ��������ֽ���
        //ת��Ϊ bmp ͼƬ����ͼƬ��λ���� 32 (��ÿ�����ص��� 32 bit ��ʾ)
        int nBMPWidthBytes = (nViewportWidth * HT_BITMAPBITSCONT + 7) / 8;

        //����bmpͼ��������������ֽ���
        int nDataSize = nBMPWidthBytes * nViewportHeight;
        //����Ŀ���ļ���С
        pBuff = new char[sizeof(BITMAP_FILE_HEADER) + sizeof(BITMAP_INFO_HEADER) + static_cast<unsigned long>(nDataSize)];
        //��ȡĿ���ļ�ͷ
        BITMAP_FILE_HEADER *pHeader = reinterpret_cast<BITMAP_FILE_HEADER *>(pBuff);
        //��ȡĿ���ļ���Ϣ
        BITMAP_INFO_HEADER *pInfo = reinterpret_cast<BITMAP_INFO_HEADER *>(pBuff + sizeof(BITMAP_FILE_HEADER));
        //bmp�ļ�ͷ���
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

        //pData��������bmp�ļ����ڴ���
        char *pData = reinterpret_cast<char *>(pBuff + pHeader->bfOffBits);
        //�߶�Ϊѭ����һ��
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
            //���Ϊ�ڶ���
            for (int j = 0; j< nViewportWidth; j++)
            {
                unsigned int valC = 0, valM = 0, valY = 0, valK = 0, valLC = 0, valLM = 0, valLY = 0, valG = 0;
                //ʹ��������ɫ
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
                    //����ʹ��������ɫ
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
				//��valLC��valLM��valLY��valG�ϲ���valC��valM��valY��valK��
				//mergeCMYK(valLC, valLM, valLY, valG, valC, valM, valY, valK);
                //��rgbֵд��bmp�Ķ�Ӧ����λ
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
//��valLC��valLM��valLY��valG�ϲ���valC��valM��valY��valK��
void mergeCMYK(const int valLC, const int valLM, const int valLY, const int valG, 
					int &valC, int &valM, int &valY, int &valK)
{
	valC += valLC / settingLight * 255;
	valM += valLM / settingLight * 255;
	valY += valLY / settingLight * 255;
	valK += valG / settingLight * 255;
}
//��ȡxml�ĵ�
void ReadXmlFile(QString ColorXmlFile, QVector<COLORTYPE> &vec)
{
    QString strRoot = "root";
    Xml colorXml(ColorXmlFile, strRoot);
    //��ȡ�ڵ��ֵ
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
