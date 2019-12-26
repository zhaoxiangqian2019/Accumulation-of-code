//C++错误码规范

//1、需要准确描述出错信息
//2、记录出错场景（关键参数记录）
//3、尽量使用场景中词汇描述错误信息

//错误码
enum {
	ERR_CONFIG_FILE_NOT_EXIST,             	//配置文件不存在
		/*
			RECORD_ERR(ERR_CONFIG_FILE_NOT_EXIST, "Configuration file（%s） does not exist !",fileName);
			...
		*/
    ERR_DATA_NOT_EXIST,                    	//数据不存在
		/*
			RECORD_ERR(ERR_DATA_NOT_EXIST, "Data(%s) does not exist !",dataName);
			...
		*/
	ERR_FAILED_OPERATION                   	//失败的操作
		/*
			RECORD_ERR(ERR_FAILED_OPERATION, "File(%s) write failed !",deviceName);
			RECORD_ERR(ERR_FAILED_OPERATION, "File(%s) read failure !",deviceName);
			RECORD_ERR(ERR_FAILED_OPERATION, "File(%s) creation failed !", fileName);
			RECORD_ERR(ERR_FAILED_OPERATION, "File(%s) open failed !",file);
			...
		*/
	ERR_FILE_NOT_EXIST,                    	//文件不存在
		/*
			RECORD_ERR(ERR_FILE_NOT_EXIST, "File(%s) does not exist !",fileName);
			...
		*/
	ERR_GENERATE_MARK_MATRIX_FAILED,       	//生成加标矩阵失败
		/*
			RECORD_ERR(ERR_GENERATE_MARK_MATRIX_FAILED, "Generate mark matrix failed !");
			...
		*/
	ERR_GET_MEMORY_STAT_FAILED,            	//获取内存状态失败
		/*
			RECORD_ERR(ERR_GET_MEMORY_STAT_FAILED, "Failed to get memory state!");
			...
		*/
	ERR_GET_MEMSAGE_FAIL,                 	//获取信息失败
		/*
			RECORD_ERR(ERR_GET_MEMSAGE_FAIL, "%s failed to retrieve %s information !", Who, What information);
			RECORD_ERR(ERR_GET_MEMSAGE_FAIL, "%s failed to obtain %s information !", Who, What information);
			...
		*/
    ERR_GET_SYSTEM_TIME_FAILED,            	//获取系统时间失败
		/*
			RECORD_ERR(ERR_GET_SYSTEM_TIME_FAILED, "%s failed to get system time !", Who);
			...
		*/
	ERR_ICC_FILE_NOT_EXIST,                	//icc文件不存在
		/*
			RECORD_ERR(ERR_ICC_FILE_NOT_EXIST, "%s iccFile does not exist !",fileName);
			...
		*/
	ERR_INK_SIZE_INVALID,                  	//墨滴大小异常
		/*
			RECORD_ERR(ERR_INK_SIZE_INVALID, "The drop size is abnormal");
			...
		*/
	ERR_INPUT_PARA_INVALID,                	//输入参数有误
		/*
			RECORD_ERR(ERR_INPUT_PARA_INVALID, "Input para error ! paraName", Who, What's the matter?);
			...
		*/
	ERR_JOB_NOT_EXIST,                     	//任务不存在
		/*
			RECORD_ERR(ERR_JOB_NOT_EXIST, "Job (id = %d) not exist !", iJobId);
			...
		*/
    ERR_JOB_START_FAILED,                  	//进程启动失败
		/*
			RECORD_ERR(ERR_JOB_START_FAILED, "Job( id = %d ) start failed ! ", Process_id);
			...
		*/
	ERR_KEY_FILE_NOT_EXIST,                	//解密文件不存在
		/*
			RECORD_ERR(ERR_KEY_FILE_NOT_EXIST, "Decrypted file(%s) does not exist !", fileName);
			...
		*/
	ERR_LINEARIZATION_FILE_NOT_EXIST,      	//线性化文件不存在
		/*
			RECORD_ERR(ERR_LINEARIZATION_FILE_NOT_EXIST, "Job(id = %d) strLinearFile: %s not exist!",p->dwJobId, p->strLinearFile1);
			...
		*/
    ERR_MALLOC_FAILED,                    	//分配内存失败
		/*
			RECORD_ERR(ERR_MALLOC_FAILED, "Memory allocation failed ! Alloc size = %d", size);
			...
		*/
	ERR_MAP_POS_OR_SIZE_INVALID,          	//图像位置非法
		/*
			RECORD_ERR(ERR_MAP_POS_OR_SIZE_INVALID, "%s image position illegal !", imageName);
			...
		*/
    ERR_MARK_COUNT_EXCEED_MAX,           	//标的数量超过最大值
		/*
			RECORD_ERR(ERR_MARK_COUNT_EXCEED_MAX, "The number of marks exceeds the maximum !");
			...
		*/
	ERR_MARK_LINE_WIDTH_INVALID,           	//mark的线宽非法
		/*
			RECORD_ERR(ERR_MARK_LINE_WIDTH_INVALID, "Line width of illegal ! LineWidth: %d", lineWidth);
			...
		*/
	ERR_MARK_NUM_NOT_MATCH,             	//标的数量不匹配
		/*
			RECORD_ERR(ERR_MARK_NUM_NOT_MATCH, "The number of marks does not match !");
			...
		*/
	ERR_MARK_PARA_INVALID,                 	//加标参数有错误
		/*
			RECORD_ERR(ERR_MARK_PARA_INVALID, "Error in marking parameter ! MarkName: %s, Parameter", %d);
			...
		*/
	ERR_MARK_POS_OR_SIZE_INVALID,         	//标大小非法
		/*
			RECORD_ERR(ERR_MARK_POS_OR_SIZE_INVALID, "%s mark size illegal", markName);
			...
		*/
	ERR_MESSAGE_LENGTH_NOT_MATCH,    		//消息长度不匹配
		/*
			RECORD_ERR(ERR_MESSAGE_LENGTH_NOT_MATCH, "Message length mismatch ! length = %d", length);
			...
		*/
    ERR_MESSAGE_UNKNOWN,                	//消息无法识别
		/*
			RECORD_ERR(ERR_MESSAGE_UNKNOWN, "%s message not recognized !", memageName);
			RECORD_ERR(ERR_MESSAGE_UNKNOWN, "Cmd(%d) unknown!", e->iPara1);
			...
		*/
	ERR_PAGE_FILE_SIZE_INVALID,            	//目标页文件大小非法
		/*
			RECORD_ERR(ERR_PAGE_FILE_SIZE_INVALID, "%s file size illegal !", fileName);
			...
		*/
	ERR_PAGE_RANGE_INVALID,                	//页范围不合法
		/*
			RECORD_ERR(ERR_PAGE_RANGE_INVALID, "Job(id = %d) Page range invalid. begin: %d, end: %d",
						p->dwJobId, p->pageRange.dwBegin, p->pageRange.dwEnd);
			...
		*/
	ERR_PARSE_CONFIG_FAILED,               	//解析配置文件失败
		/*
			RECORD_ERR(ERR_PARSE_CONFIG_FAILED, "Failed to parse the configuration file ! fileName: %s", fileName);
			...
		*/
	ERR_PATH_NOT_EXIST,                    	//路径不存在
		/*
			RECORD_ERR(ERR_PATH_NOT_EXIST, "Path does not exist ! Path: %s", path);
			...
		*/
	ERR_PDF_FILE_OPEN_FAILED,             	//pdf打开失败
		/*
			RECORD_ERR(ERR_PDF_FILE_OPEN_FAILED, "Job(id = %d) Open file(%s) failed!",
						ctrl->pPara->dwJobId, (char *)ctrl->pPara->strFile);
			...
		*/
    ERR_PROCESS_CNT_EXCEED_LIMIT,          	//进程数目超过了最大值
		/*
			RECORD_ERR(ERR_PROCESS_CNT_EXCEED_LIMIT, "The number of processes(%d) exceeded the maximum(%d) !", ProcessesNum, Maximum);
			...
		*/
	ERR_PROCESS_EXIT_WITH_CRASH,           	//进程异常退出
		/*
			RECORD_ERR(ERR_PROCESS_EXIT_WITH_CRASH, "Process(%s(%d)) exit !", process_name, process_id);
			RECORD_ERR(ERR_PROCESS_EXIT_WITH_CRASH, "Jobid:%d ProcessId:%d Last finished page:%d ",
							ctrl->pPara->dwJobId, iProcessId, ctrl->stProcessCtrl[i].iFinishedPage);
			...
		*/
    ERR_PROCESS_PARA_INVALID,              	//进程参数异常
		/*
			RECORD_ERR(ERR_PROCESS_PARA_INVALID, "Process(%s(%d)) parameter exception ! abnormal value: %s", 
						process_name, process_id, abnormal value);
			...
		*/
	ERR_PROCESS_RESTART_FAILED,            	//进程重启失败
		/*
			RECORD_ERR(ERR_PROCESS_RESTART_FAILED, "Process(%s(%d)) restart failed !", process_name, process_id);
			...
		*/
	ERR_RIP_PARA_INVALID,                  	//rip参数有错误
		/*
			RECORD_ERR(ERR_RIP_PARA_INVALID, "Parameter error !");
			RECORD_ERR(ERR_RIP_PARA_INVALID, "Job(id = %d), Process Num = %d, ErrCode: %d", ctrl->pPara->dwJobId, id, iRet);
			...
		*/
	ERR_RIP_PROCESS_FAILED,                	//rip进程返回错误
		/*
			RECORD_ERR(ERR_RIP_PROCESS_FAILED, "Jobid: %d, ProcessId: %d, Err info: %s, Finished page: %d",
                ctrl->pPara->dwJobId, iProcessId, QStringToChar(str), ctrl->iFinishedPageCnt);
			...
		*/
	ERR_RUN_OUT_OF_MEM,                  	//内存耗尽
		/*
			RECORD_ERR(ERR_RUN_OUT_OF_MEM, "Run out of memory !");
			...
		*/
    ERR_RUN_OUT_OF_RD,                    	//random disk耗尽
		/*
			RECORD_ERR(ERR_RUN_OUT_OF_RD, "Run out of random disk !");
			...
		*/
    ERR_UNKNOWN_JOB_STATE,                	//任务状态无法识别
		/*
			RECORD_ERR(ERR_UNKNOWN_JOB_STATE, "Task status not recognized !");
			RECORD_ERR(ERR_UNKNOWN_JOB_STATE, "Job(id = %d) State(%d) is invalid.", 
							ctrl->pPara->dwJobId ,iState);
			...
		*/
	NORMAL = 0,                            	//工作正常
};
