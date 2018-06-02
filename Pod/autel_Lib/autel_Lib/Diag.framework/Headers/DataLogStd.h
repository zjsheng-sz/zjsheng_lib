#ifndef __LOG_MACRO_H__
#define __LOG_MACRO_H__

//////////////////LOGHEAD

#define		LOGHEAD_FILETYPE  			"LOGHEAD_FILETYPE"  			//日志文件分类
#define		LOGHEAD_MAKE    			"LOGHEAD_MAKE"    				//取车系名VehicleName()
#define		LOGHEAD_VIN      			"LOGHEAD_VIN"      				//VIN码
#define		LOGHEAD_AREA    			"LOGHEAD_AREA"    				//区域   //区域文本ID@文本串
#define		LOGHEAD_VEHICLE  			"LOGHEAD_VEHICLE"  				//车型名  //车型名称文本ID@文本串
#define		LOGHEAD_YEAR    			"LOGHEAD_YEAR"    				//年款 //年款文本ID@文本串
#define		LOGHEAD_IDENT_INFOR  		"LOGHEAD_IDENT_INFOR"  			//工程师想任意添加的信息、数据、描述等等 //以上信息在调用Start()时必须要有
#define		LOGHEAD_SYSTEM  			"LOGHEAD_SYSTEM"  				//系统名称ID @ 系统名称文本	
#define		LOGHEAD_ECUNO  				"LOGHEAD_ECUNO"  				//值根据车系而定
#define		LOGHEAD_MENUGRP  			"LOGHEAD_MENUGRP"  				//菜单组宏定义
#define		LOGHEAD_FUNGRP    			"LOGHEAD_FUNGRP"    			//功能组宏定义
#define		LOGHEAD_ERRORTYPE  			"LOGHEAD_ERRORTYPE"  			//错误类型  例: ERROR_ECU_NORESPONSE
#define		LOGHEAD_OTHER_INFOR  		"LOGHEAD_OTHER_INFOR"  			//工程师想任意添加的信息、数据、描述等等



/////////////////////////LOGHEAD_FILETYPE (日志文件分类)
#define		LOG_TYPE_BUG				"LOG_TYPE_BUG"				//出错  只要是工程师认为是bug的情况都可以归为此类，例如：未定义故障码、Coding失败、编程失败、新ID、清码失败等等
#define		LOG_TYPE_COLLECTDATA		"LOG_TYPE_COLLECTDATA"		//收集数据  收集进入数据、某个未解出功能的命令响应等等


///////////////////////LOGHEAD_MENUGRP(菜单组)
#define 	LOG_MNU_ENTERSYSTEM    			"LOG_MNU_ENTERSYSTEM"    		//进系统
#define 	LOG_MNU_ECUINFO         		"LOG_MNU_ECUINFO"         	//版本信息
#define 	LOG_MNU_READCODE       			"LOG_MNU_READCODE"       		//读取故障码
#define 	LOG_MNU_ERASECODE      			"LOG_MNU_ERASECODE"      		//清除故障码
#define 	LOG_MNU_LIVEDATA        		"LOG_MNU_LIVEDATA"        	//数据流
#define 	LOG_MNU_ACTIVETEST      		"LOG_MNU_ACTIVETEST"      	//动作测试
#define 	LOG_MNU_SPECIFUNCTION   		"LOG_MNU_SPECIFUNCTION"   	//特殊功能
#define 	LOG_MNU_CONFIGURATION  			"LOG_MNU_CONFIGURATION"  		//配置
#define 	LOG_MNU_CODING         			"LOG_MNU_CODING"         		//Coding,设码
#define 	LOG_MNU_PROGRAM       			"LOG_MNU_PROGRAM"       		//编程
#define 	LOG_MNU_BASICSETTING    		"LOG_MNU_BASICSETTING"    	//基本设定
#define 	LOG_MNU_ADAPTION       			"LOG_MNU_ADAPTION"       		//自适应
#define 	LOG_MNU_FREEZEFRAME	 			"LOG_MNU_FREEZEFRAME"	 			//冻结帧
#define 	LOG_MNU_INITIALIZATION			"LOG_MNU_INITIALIZATION"	 	//初始化



///////////////////////LOGHEAD_FUNCGRP(功能组)
#define		LOG_FNT_EPB        		"LOG_FNT_EPB"           //EPB
#define		LOG_FNT_OILRESET   		"LOG_FNT_OILRESET"       //Oil Reset
#define		LOG_FNT_TPMS       		"LOG_FNT_TPMS"          //TPMS
#define		LOG_FNT_DPF        		"LOG_FNT_DPF"           //DPF
#define		LOG_FNT_SAS        		"LOG_FNT_SAS"           //Steering
#define		LOG_FNT_KEYPROGRAM 		"LOG_FNT_KEYPROGRAM"   	//防盗
#define		LOG_FNT_THROTTLE   		"LOG_FNT_THROTTLE"      //节气门匹配


///////////////////////LOGHEAD_ERRORTYPE(错误类型)
#define		LOG_ERR_ECU_NORESPONSE 				"LOG_ERR_ECU_NORESPONSE"   //ECU未响应
#define		LOG_ERR_ECU_REFUSE     				"LOG_ERR_ECU_REFUSE"       //ECU拒绝
#define		LOG_ERR_ECU_DATA       				"LOG_ERR_ECU_DATA"         //错误的ECU数据
#define		LOG_ERR_ECU_NEWID      				"LOG_ERR_ECU_NEWID"        //ECU新ID
#define		LOG_ERR_ERASEDTC_FAIL  				"LOG_ERR_ERASEDTC_FAIL"    //清码失败
#define		LOG_ERR_DTC_UNDEFINE   				"LOG_ERR_DTC_UNDEFINE"     //故障码未定义
#define		LOG_ERR_CODING_FAIL    				"LOG_ERR_CODING_FAIL"      //Coding失败
#define		LOG_ERR_PROGRAM_FAIL   				"LOG_ERR_PROGRAM_FAIL"     //Program失败
#define		LOG_ERR_SECURITY_ACCESS				"LOG_ERR_SECURITY_ACCESS"	 //安全访问失败


#endif
