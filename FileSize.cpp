/**************************************************************************
* @file   		FileSize
* @brief		实现文件大小的计算
* @param		void
* @return		返回文件的大小
* @note			void
* @author		赵向前
* @date			2019/7/4
***************************************************************************/
qint64 FileSelectWidget::FileSize(const QString &path)
{
	qint64 size = 0;
	QFileInfo FileInfo(path);
	if (FileInfo.isFile())
	{
		size = FileInfo.size();
		return size;
	}
	QDir dir(path);
	// dir.entryInfoList(QDir::Files)返回文件信息
	foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files))
		//计算文件大小
		size += fileInfo.size();
	// dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)返回所有子目录，并进行过滤
	foreach(QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
		//若存在子目录，则递归调用du函数
		size += FileSize(path + QDir::separator() + subDir);
	return size;
}

