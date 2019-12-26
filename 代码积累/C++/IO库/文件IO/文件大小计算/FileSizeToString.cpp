/**************************************************************************
* @file   		FileSizeToString
* @brief		将以 Byte 为单位的文件化为 K、M、G
* @param		void
* @return		以 String 的形式返回文件的大小
* @note			void
* @author		赵向前
* @date			2019/7/4
***************************************************************************/
QString FileSelectWidget::FileSizeToString(qint64 size)
{
	char unit = 'B';
	qint64 curSize = size;
	if (curSize > 1024)
	{
		curSize /= 1024;
		unit = 'K';
		if (curSize > 1024)
		{
			curSize /= 1024;
			unit = 'M';
			if (curSize > 1024)
			{
				curSize /= 1024;
				unit = 'G';
			}
		}
	}
	return QString("%1%2").arg(curSize).arg(unit);
}