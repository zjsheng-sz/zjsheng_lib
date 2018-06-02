#ifndef __EN_STD_TXT_H__
#define __EN_STD_TXT_H__

#define 		STD_INFO				"\xff\x05\x00\x00\x00"  
#define			STD_PROG				"\xff\x06\x00\x00\x00"

#define 		STD_STANDARD			"\xff\x00\x00\x00\x00"

#define STD_BTN_OK						CBinary(STD_STANDARD"\x00", 6)
#define STD_BTN_FREEZEFRAME				CBinary(STD_STANDARD"\x10", 6)


#define	STD_TTL_MNU_SYSTEM				CBinary(STD_INFO"\x01", 6)			//	"System Menu"
#define	STD_TTL_MNU_MODE				CBinary(STD_INFO"\x02", 6)			//	"Mode Menu"
#define	STD_TTL_MSG_COMM				STD_TEXT_COMM_STATUS		//CBinary(STANDARD"\x07\x00\x00\x00\x31",6) //"Communication status"
										//CBinary(STD_INFO"\x03", 6)			  //"Communicating"
#define	STD_TXT_MSG_SCANSYS				CBinary(STD_INFO"\x04", 6)			//	"Diagnostic System Initializing..."
#define	STD_TXT_MSG_CONFIRMIGN			STD_TEXT_TIP_CONNECT	//CBinary(STANDARD"\x07\x00\x00\x00\x2A",6) //"1.Make sure ignition switch is on.\n2. Make sure the Tester is connected to the vehicle DLC."
										//20150206 CBinary(STD_INFO"\x05", 6)	  //"1.Make sure the ignition is switched ON.\n2.Check the cables between the tester and the vehicle DLC."
#define	STD_TXT_MSG_ENTERSYS			CBinary(STD_INFO"\x06", 6)			//	"System Data Initializing \n\nPlease Wait..."
#define STD_TTL_MSG_ERASEDTC			CBinary(STD_INFO"\x08", 6)			//	"Erase Codes"
#define STD_TXT_MSG_ERASEDTC			STD_TEXT_TIP_EARSE_CODES			//CBinary(STANDARD"\x07\x00\x00\x00\x27",6) //"DTCs and Freeze Frame Data will be deleted. \nAre you sure you want to continue?"
										//CBinary(STD_INFO"\x09", 6)			  //"DTCs and Freeze Data will be lost\nDo you wish to continue?"
#define STD_TXT_MSG_COMMANDCANCEL		STD_TEXT_TIP_COMD_ABORT		//CBinary(STANDARD"\x07\x00\x00\x00\x28",6) //"Command aborted."
										//CBinary(STD_INFO"\x0A", 6)			  //"Command Cancelled"
#define STD_TXT_MSG_ENGINEOFFKEYON		STD_TEXT_TIP_IGNITION		//CBinary(STANDARD"\x07\x00\x00\x00\x2B",6) //"Switch the ignition on and turn the engine off."
										//CBinary(STD_INFO"\x0B", 6)			  //"Ignition on and engine stopped?"
#define STD_TXT_MSG_NOCODES				STD_TEXT_TIP_NO_FAULT_CODES		//CBinary(STANDARD"\x07\x00\x00\x00\x34",6) //"No fault codes detected."
										//CBinary(STD_INFO"\x0C", 6)			  //"System pass.\nNo fault codes detected."
#define STD_TXT_MSG_CODESERASED			STD_TEXT_EARSE_CODES_SEND		//CBinary(STANDARD"\x07\x00\x00\x00\x29",6) //"Codes have been successfully erased. Tap 'Read codes' to verify."
										//CBinary(STD_INFO"\x0D", 6)			  //"Erase Codes command sent.\nPerform Read Codes function to verify."
#define	STD_TXT_MSG_ESTABILISHCOMM		STD_TEXT_TIP_COMM	//CBinary(STANDARD"\x07\x00\x00\x00\x3e",6) //"Establishing vehicle communication..."
										//CBinary(STD_INFO"\x0E", 6)			  //"Establishing vehicle communications.\nPlease wait..."
#define	STD_TXT_MSG_COMMFAIL			STD_TEXT_TIP_NOT_COMM		//CBinary(STANDARD"\x07\x00\x00\x00\x3a",6) //"No communication between the tester and control unit.\n1. Make sure ignition switch is on.\n2. Make sure the Tester is connected to the vehicle DLC.\n3. Make sure the battery is charged."
										//CBinary(STD_INFO"\x0F", 6)			  //"Tester not communicating with control unit.\n\n1.Make sure the ignition is switched ON.\n2.Check the cables between the Tester and the vehicle DLC.\n3.Check that the vehicle battery is charged."
#define STD_TXT_MSG_EXITSYSTEM			STD_TEXT_TIP_EXIT		//CBinary(STANDARD"\x07\x00\x00\x00\x26",6) //"Are you sure you want to exit diagnostic program?"
										//CBinary(STD_INFO"\x10", 6)			  //"Exit Diagnostic System.\nAre you sure?"
#define STD_TXT_MSG_PLEASE_WAIT			CBinary(STD_INFO"\x11", 6)			//	"-Please Wait-"
#define STD_TTL_MSG_MODEL_MENU			CBinary(STD_INFO"\x12", 6)			//	"Model Menu"
#define STD_TTL_MSG_INFORMATION			CBinary(STD_INFO"\x13", 6)			//	"Information"
#define STD_TTL_MSG_SAVEHICHILEREC		CBinary(STD_INFO"\x14", 6)			//	"Save Vehicle Record"
#define STD_TXT_MSG_SAVEHICHILEREC		CBinary(STD_INFO"\x15", 6)			//	"Input vehicle name:\nMaximum length is 25 characters."


#define STD_TXT_MSG_INPUT_VEHICLE_NAME_MAX25CHAR			CBinary(STD_INFO"\x15", 6)		//	"Input vehicle name:\nMaximum length is 25 characters."
#define STD_TXT_MSG_LOADING_DATA_FAILURE					CBinary(STD_INFO"\x16", 6)		//	"Loading data failure."
#define STD_TXT_MSG_COMMUNICATION							CBinary(STD_INFO"\x20", 6)			  //"Communication"
#define STD_TXT_MSG_ENTERSYSFAIL							CBinary(STANDARD"\x07\x00\x00\x00\x2C",6) //" No communication between the tester and control unit.\n1.Make sure ignition switch is on.\n2.Make sure the cables between the Tester and the vehicle DLC are connected.\n3.Make sure the battery is charged.\n4. Make sure the system is configured for the vehicle."
															//CBinary(STD_INFO"\x21", 6)			  //"Tester not communicating with control unit.\n\n1.Make sure the ignition is switched ON.\n2.Check the cables between the Tester and the vehicle DLC.\n3.Check that the vehicle battery is charged.\n4.Verify if the system is configured for the Vehicle."
#define STD_TTL_MNU_MAIN_GROUPS								CBinary(STD_INFO"\x22", 6)		//	"Main Groups"
#define STD_TTL_MNU_AUTO_SCAN								CBinary(STD_INFO"\x23", 6)		//	"Auto Scan"
#define STD_TTL_MNU_CONTROL_UNITS							CBinary(STD_INFO"\x24", 6)		//	"Control Units"
#define STD_TTL_MNU_VEHICLE_RECORD							CBinary(STD_INFO"\x25", 6)		//	"Vehicle Record"
#define STD_TTL_MNU_START_NEW_SESSION						CBinary(STD_INFO"\x26", 6)		//	"Start New Session"
#define STD_TTL_MNU_FUNCTION_MENU							CBinary(STD_INFO"\x27", 6)		//	"Function Menu"
#define STD_TTL_MNU_FREEZE_FRAME_DATA						CBinary(STD_INFO"\x28", 6)		//	"Freeze Frame Data"
#define STD_TTL_MNU_ECU_INFORMATION							CBinary(STD_INFO"\x29", 6)		//	"ECU Information"
#define STD_TTL_MNU_READ_CODES								CBinary(STD_INFO"\x2A", 6)		//	"Read Codes"
#define STD_TTL_MNU_LIVE_DATA								CBinary(STD_INFO"\x2B", 6)		//	"Live Data"
#define STD_TTL_MNU_ACTIVE_TEST								CBinary(STD_INFO"\x2C", 6)		//	"Active Test"
#define STD_TXT_MSG_PASS									CBinary(STD_INFO"\x2D", 6)		//	"Pass"
#define STD_TXT_MSG_NO_FAULT								CBinary(STD_INFO"\x2E", 6)		//	"No Fault"
#define STD_TXT_MSG_FAULT									CBinary(STD_INFO"\x2F", 6)		//	"Fault"
#define STD_TXT_MSG_READCODES_FAIL							CBinary(STD_INFO"\x30", 6)		//	"-!-"
#define STD_TXT_MSG_HAVE_SYSTEM_MENUSUB						CBinary(STD_INFO"\x31", 6)		//	"-?-"
#define STD_TXT_MSG_SCANNING								CBinary(STD_INFO"\x32", 6)		//	"Scanning..."
#define STD_TXT_MSG_FAULT_CODES								CBinary(STD_INFO"\x33", 6)		//	"Fault Codes"
#define STD_TXT_MSG_ERASING									CBinary(STD_INFO"\x34", 6)		//	"Erasing..."
#define STD_TXT_MSG_READING_CODES							CBinary(STD_INFO"\x35", 6)		//	"Reading Codes..."
#define STD_TXT_MSG_DIAGNOSTIC_SYSTEM_INITIALIZING			CBinary(STD_INFO"\x04", 6)		//	"Diagnostic System Initializing..."
//#define STD_TXT_MSG_PLEASE_WAIT								CBinary(STD_INFO"\x37", 6)		//	"Please Wait."
#define STD_TXT_MSG_THE_SELECTED_FUNCTION_IS_NOT_SUPPORTED	CBinary(STD_INFO"\x38", 6)		//	"The selected function is not supported."
#define STD_TTL_MNU_CUSTOM_LIST								CBinary(STD_INFO"\x39", 6)		//	"Custom List"
#define STD_TXT_MSG_ALL_DATA								CBinary(STD_INFO"\x3A", 6)		//	"All Data"
#define STD_TXT_MSG_THE_VEHICLE_HAS_SAVED					CBinary(STD_INFO"\x3B", 6)		//	"The Vehicle has saved!"
#define STD_TXT_MSG_REPORT_Status							CBinary(STD_INFO"\x3C", 6)		//"Status"          
#define STD_TXT_MSG_REPORT_DTCCOUNT							CBinary(STD_INFO"\x3D", 6)		//"DTC Counts"      
#define STD_TXT_MSG_REPORT_SYSNAME							CBinary(STD_INFO"\x3E", 6)		//"System Name"     
#define STD_TXT_MSG_REPORT_DTCCODE							CBinary(STD_INFO"\x3F", 6)		//"DTC Code"        
#define STD_TXT_MSG_REPORT_DTC_CONTENT						CBinary(STD_INFO"\x40", 6)		//"DTC Content"     
#define STD_TXT_MSG_REPORT_FAULT							CBinary(STD_INFO"\x41", 6)		//"Fault"           
#define STD_TXT_MSG_REPORT_PASS								CBinary(STD_INFO"\x42", 6)		//"Pass"            
#define STD_TXT_MSG_REPORT_RESULT							CBinary(STD_INFO"\x43", 6)		//"Result"          
#define STD_TXT_MSG_REPORT_RESULT_REPORT					CBinary(STD_INFO"\x44", 6)		//"Result Report"   
#define STD_TXT_MSG_REPORT_DTCSTATUS						CBinary(STD_INFO"\x45", 6)		//"DTC Status"  


#define STD_TTL_MNU_SELECT_APPLICATION								CBinary(STD_INFO"\x5F",6)		//"Select Application"
#define STD_TTL_MNU_DIAGNOSTIC								CBinary(STD_INFO"\x60",6)		//"Diagnosis"
#define STD_TTL_MNU_SERVICE									CBinary(STD_INFO"\x61",6)		//Service
#define STD_TTL_MNU_PROGRAMMING_CUSTOMIZATION				CBinary(STD_INFO"\x62",6)		//Programming/Customization
#define STD_TTL_MNU_PROGRAMMING								CBinary(STD_INFO"\x63",6)
#define STD_TTL_MNU_CUSTOMIZATION							CBinary(STD_INFO"\x64",6)
#define STD_TTL_MNU_CODING									CBinary(STD_INFO"\x65",6)
#define STD_TTL_MNU_MAINTENANCE								CBinary(STD_INFO"\x66",6)
#define STD_TTL_MNU_POWERTRAIN								CBinary(STD_INFO"\x67",6)
#define STD_TTL_MNU_CHASSIS									CBinary(STD_INFO"\x68",6)
#define STD_TTL_MNU_BODY									CBinary(STD_INFO"\x69",6)


#define STD_TTL_MNU_OILRESET						CBinary(STD_INFO"\x6A",6)		//"Oil Reset"
#define STD_TTL_MNU_OILRESET_WITH_TOOL					CBinary(STD_INFO"\x6B",6)		//"Reset with tool"
#define STD_TTL_MNU_OILRESET_WITHOUT_TOOL				CBinary(STD_INFO"\x6C",6)		//"Reset without tool"

#define STD_TXT_MSG_CABLE_INFO						CBinary(STD_PROG"\x00",6)	//"Note: \n - Please connect MaxiFlashPro to MaxiSYS with USB cable or ethernet cable. \n -Please make sure MaxiSYS is connected to the network before connection."
#define STD_TXT_MSG_CHECKING_NETWORK			CBinary(STD_PROG"\x01",6)	//"Checking network ...\n Please wait."
#define STD_TXT_MSG_NETWORK_FAIL					CBinary(STD_PROG"\x02",6)	//"Network check failed!\nCan't connect to MaxiSYS server!\nDo you want to try again?"
#define STD_TXT_MSG_SENDING_FAIL					CBinary(STD_PROG"\x03",6)	//"Sending failed!\nCheck the network please!"
#define STD_TXT_MSG_RECEIVE_FAIL					CBinary(STD_PROG"\x04",6)	//"Receive failed!\nCheck the network please!"
#define STD_TXT_MSG_TRANSFER_FAIL					CBinary(STD_PROG"\x05",6)	//"Transfer data failed.\nDo you want to try again?"
#define STD_TXT_MSG_DOWNLOAD_FAIL					CBinary(STD_PROG"\x06",6)	//"Download calibration file failed!\nCheck the network please!"
#define STD_TXT_MSG_PROG_VALTAGE					CBinary(STD_PROG"\x07",6)	//"Programming Voltage = "
#define STD_TXT_MSG_V											CBinary(STD_PROG"\x08",6)	//"V"
#define STD_TXT_MSG_SUBMIT_ERROR					CBinary(STD_PROG"\x09",6)	//"Do you want to submit this EORROR to the server."
#define	STD_TXT_MSG_NETWORK							CBinary(STD_PROG"\x0A", 6)			//	"Network Data Initializing \n\nPlease Wait..."



#define STANDARD                           "\xFF"
#define STD_TEXT_AUTO_DETECT	CBinary(STANDARD"\x07\x00\x00\x00\x01",6)	//Scan VIN
#define STD_TEXT_DETECTING	CBinary(STANDARD"\x07\x00\x00\x00\x02",6)	//Scanning…(x/y)
#define STD_TEXT_CANCEL	CBinary(STANDARD"\x00\x00\x00\x00\x01",6)	//Cancel
#define STD_TEXT_ENTER_VIN	CBinary(STANDARD"\x07\x00\x00\x00\x03",6)	//Enter VIN 
#define STD_TEXT_SEARCH_FAILED	CBinary(STANDARD"\x07\x00\x00\x00\x04",6)	//VIN scanning failed.
#define STD_TEXT_ENTER_DONE	CBinary(STANDARD"\x07\x00\x00\x00\x06",6)	//Done
#define STD_TEXT_ENTER_VIN	CBinary(STANDARD"\x07\x00\x00\x00\x03",6)	//Enter VIN
#define STD_TEXT_TIP_DIAG_LOAD	CBinary(STANDARD"\x07\x00\x00\x00\x0B",6)	//Diagnostic program loading…
#define STD_TEXT_INIT	CBinary(STANDARD"\x07\x00\x00\x00\x0C",6)	//Initialization
#define STD_TEXT_TIP_DIAG_INIT	CBinary(STANDARD"\x07\x00\x00\x00\x0D",6)	//Diagnostic program initializing…
#define STD_TEXT_VEHICLE_HIS	CBinary(STANDARD"\x07\x00\x00\x00\x0E",6)	//Vehicle history
#define STD_TEXT_TIP_LAST	CBinary(STANDARD"\x07\x00\x00\x00\x0F",6)	//Do you want to use the last vehicle data?
#define STD_TEXT_YES	CBinary(STANDARD"\x00\x00\x00\x00\x03",6)	//Yes
#define STD_TEXT_NO	CBinary(STANDARD"\x00\x00\x00\x00\x04",6)	//No
#define STD_TEXT_SELECT_VEHICLE	CBinary(STANDARD"\x07\x00\x00\x00\x3B",6)	//Select diagnostic type
#define STD_TEXT_AUTO_SELECT	CBinary(STANDARD"\x07\x00\x00\x00\x10",6)	//Automatic selection
#define STD_TEXT_MAN_SELECT	CBinary(STANDARD"\x07\x00\x00\x00\x11",6)	//Manual selection
#define STD_TEXT_SYS_SELECT	CBinary(STANDARD"\x07\x00\x00\x00\x12",6)	//System selection
#define STD_TEXT_ESC	CBinary(STANDARD"\x07\x00\x00\x00\x13",6)	//ESC
#define STD_TEXT_ACQUIRE_VIN	CBinary(STANDARD"\x07\x00\x00\x00\x14",6)	//Acquire VIN information
#define STD_TEXT_TIP_ENTER_VIN	CBinary(STANDARD"\x07\x00\x00\x00\x08",6)	//"Enter VIN manually or tap 'Read' to acquire VIN. "
#define STD_TEXT_READ	CBinary(STANDARD"\x07\x00\x00\x00\x09",6)	//Read
#define STD_TEXT_OK	CBinary(STANDARD"\x00\x00\x00\x00\x00",6)	//OK
#define STD_TEXT_DECODE_VIN	CBinary(STANDARD"\x07\x00\x00\x00\x36",6)	//Decode VIN
#define STD_TEXT_VIN_DECODING	CBinary(STANDARD"\x07\x00\x00\x00\x37",6)	//VIN information decoding…
#define STD_TEXT_VIN_DECODING_FAILED	CBinary(STANDARD"\x07\x00\x00\x00\x38",6)	//VIN  (%s)  decoding failed.  
#define STD_TEXT_READ_VIN	CBinary(STANDARD"\x07\x00\x00\x00\x16",6)	//Read VIN
#define STD_TEXT_VIN_READING_FAILED	CBinary(STANDARD"\x07\x00\x00\x00\x39",6)	//VIN reading failed.
#define STD_TEXT_READING_VIN	CBinary(STANDARD"\x07\x00\x00\x00\x17",6)	//Reading VIN…
#define STD_TEXT_CONFIRM_VEHICLE	CBinary(STANDARD"\x07\x00\x00\x00\x2E",6)	//Confirm vehicle profile
#define STD_TEXT_MODEL_YEAR	CBinary(STANDARD"\x07\x00\x00\x00\x1A",6)	//Model year:
#define STD_TEXT_MODEL_TYPE	CBinary(STANDARD"\x07\x00\x00\x00\x1B",6)	//Model type:
#define STD_TEXT_MODEL_SERIES	CBinary(STANDARD"\x07\x00\x00\x00\x1C",6)	//Model series:
#define STD_TEXT_MODEL	CBinary(STANDARD"\x07\x00\x00\x00\x1D",6)	//Model:
#define STD_TEXT_VIN	CBinary(STANDARD"\x07\x00\x00\x00\x1E",6)	//VIN:
//#define STD_TTL_MSG_INFORMATION	CBinary(STANDARD"\x05\x00\x00\x00\x13",6)	//Information
#define STD_TEXT_SYS_LOAD	CBinary(STANDARD"\x07\x00\x00\x00\x2D",6)	//System data loading…
#define STD_TEXT_MAIN_MENU	CBinary(STANDARD"\x07\x00\x00\x00\x35",6)	//Main menu
#define STD_TEXT_DIAGNOSIS	CBinary(STANDARD"\x05\x00\x00\x00\x60",6)	//Diagnosis
#define STD_TEXT_SERVICE	CBinary(STANDARD"\x05\x00\x00\x00\x61",6)	//Service
#define STD_TEXT_PROGRAMMING	CBinary(STANDARD"\x05\x00\x00\x00\x63",6)	//Programming
//#define STD_TTL_MNU_CODING	CBinary(STANDARD"\x05\x00\x00\x00\x65",6)	//Coding
#define STD_TEXT_VEHICLE_PROFILE	CBinary(STANDARD"\x07\x00\x00\x00\x18",6)	//Vehicle profile
#define STD_TEXT_HELP	CBinary(STANDARD"\x00\x00\x00\x00\x09",6)	//Help
#define STD_TEXT_SELECT_MODE	CBinary(STANDARD"\x07\x00\x00\x00\x21",6)	//Diagnostic menu
#define STD_TEXT_AUTO_SCAN	CBinary(STANDARD"\x05\x00\x00\x00\x23",6)	//Auto scan
#define STD_TEXT_CONTROL_UNIT	CBinary(STANDARD"\x07\x00\x00\x00\x3C",6)	//Control unit
#define STD_TEXT_PASS	CBinary(STANDARD"\x05\x00\x00\x00\x2D",6)	//Pass
#define STD_TEXT_NO_FAULT	CBinary(STANDARD"\x05\x00\x00\x00\x2E",6)	//No Fault
#define STD_TEXT_FAULT	CBinary(STANDARD"\x05\x00\x00\x00\x41",6)	//Fault
#define STD_TEXT_DETECTING	CBinary(STANDARD"\x07\x00\x00\x00\x02",6)	//Scanning…
#define STD_TEXT_SAVE	CBinary(STANDARD"\x00\x00\x00\x00\x0A",6)	//Save
#define STD_TEXT_REPORT	CBinary(STANDARD"\x05\x00\x00\x00\x43",6)	//Report
#define STD_TEXT_PAUSE	CBinary(STANDARD"\x07\x00\x00\x00\x22",6)	//Pause
#define STD_TEXT_TIP_EXIT	CBinary(STANDARD"\x07\x00\x00\x00\x30",6)	//Are you sure you want to exit?
#define STD_TEXT_FUNC_MENU	CBinary(STANDARD"\x05\x00\x00\x00\x27",6)	//Function menu
#define STD_TEXT_ECU_INFO	CBinary(STANDARD"\x05\x00\x00\x00\x29",6)	//ECU information
#define STD_TEXT_TROUBLE_CODES	CBinary(STANDARD"\x02\x00\x00\x00\x10",6)	//Trouble codes
#define STD_TEXT_LIVE_DATA	CBinary(STANDARD"\x05\x00\x00\x00\x2B",6)	//Live data
#define STD_TEXT_ACTIVE_TEST	CBinary(STANDARD"\x05\x00\x00\x00\x2C",6)	//Active test
#define STD_TEXT_SPEC_FUNC	CBinary(STANDARD"\x07\x00\x00\x00\x24",6)	//Special functions
#define STD_TEXT_SERVICE_MENU	CBinary(STANDARD"\x07\x00\x00\x00\x3D",6)	//Service menu
#define STD_TEXT_COMM_STATUS	CBinary(STANDARD"\x07\x00\x00\x00\x31",6)	//Communication status
#define STD_TEXT_TIP_COMM	CBinary(STANDARD"\x07\x00\x00\x00\x3E",6)	//Establishing vehicle communication…
#define STD_TEXT_TIP_NOT_COMM	CBinary(STANDARD"\x07\x00\x00\x00\x3A",6)	//"No communication between the tester and control unit. 1. Make sure ignition switch is on.2. Make sure the Tester is connected to the vehicle DLC.3. Make sure the battery is charged."
#define STD_TEXT_TIP_NO_SYS_COMM	CBinary(STANDARD"\x07\x00\x00\x00\x2C",6)	//"No communication between the tester and control unit. 1. Make sure ignition switch is on.2. Make sure the Tester is connected to the vehicle DLC.3. Make sure the battery is charged.4. Make sure the system is configured for the vehicle."
#define STD_TEXT_TIP_CONNECT	CBinary(STANDARD"\x07\x00\x00\x00\x2A",6)	//"1. Make sure ignition switch is on.2. Make sure the Tester is connected to the vehicle DLC."
#define STD_TEXT_TIP_IGNITION	CBinary(STANDARD"\x05\x00\x00\x00\x0b",6)	//Ignition on and engine off? 
#define STD_TEXT_ERASE_CODES	CBinary(STANDARD"\x05\x00\x00\x00\x08",6)	//Erase codes
#define STD_TEXT_TIP_EARSE_CODES	CBinary(STANDARD"\x07\x00\x00\x00\x3F",6)	//"DTCs and freeze data will be deleted.\n Are you sure you want to continue?"
#define STD_TEXT_TIP_COMD_ABORT	CBinary(STANDARD"\x07\x00\x00\x00\x28",6)	//Command aborted.
#define STD_TEXT_READ_CODES	CBinary(STANDARD"\x00\x00\x00\x00\x15",6)	//Read codes
#define STD_TEXT_TIP_NO_FAULT_CODES	CBinary(STANDARD"\x07\x00\x00\x00\x34",6)	//No fault codes detected.
#define STD_TEXT_EARSE_CODES_SEND	CBinary(STANDARD"\x07\x00\x00\x00\x29",6)	//Codes have been successfully erased.  Return to the function menu and tap 'Read codes' to verify.
//#define STD_TXT_MSG_SCANSYS	CBinary(STANDARD"\x05\x00\x00\x00\x04",6)	//Diagnostic system initializing…

#define STD_TEXT_MENU_HOTFUNCTION				CBinary(STANDARD"\x07\x00\x00\x00\x40",6)	//"Hot Function"
#define STD_TEXT_MENU_HOT_Oil						CBinary(STANDARD"\x07\x00\x00\x00\x41",6)	//"Oil Reset"
#define STD_TEXT_MENU_HOT_EPB						CBinary(STANDARD"\x07\x00\x00\x00\x42",6)	//"Electric Parking Brake"          
#define STD_TEXT_MENU_HOT_DPF						CBinary(STANDARD"\x07\x00\x00\x00\x43",6)	//"Diesel Particle Filter"          
#define STD_TEXT_MENU_HOT_TPMS					CBinary(STANDARD"\x07\x00\x00\x00\x44",6)	//"Tire Pressure Monitoring System" 
#define STD_TEXT_MENU_HOT_SAS						CBinary(STANDARD"\x07\x00\x00\x00\x45",6)	//"Steering Angle Sensor"           
#define STD_TEXT_MENU_HOT_TPMS_Replace	CBinary(STANDARD"\x07\x00\x00\x00\x46",6) //"Tire Pressure Sensor Replacement"


#define	STD_TXT_REPAIR								CBinary(STANDARD"\x07\x00\x00\x00\x47",6)	//"Repair information"
#define	STD_TEXT_MENU_HOT_BATTERY			CBinary(STANDARD"\x07\x00\x00\x00\x48",6)	//"Battery"
#define	STD_TEXT_MENU_HOT_BRAKE				CBinary(STANDARD"\x07\x00\x00\x00\x49",6)	//"Brake bleed"
#define	STD_TEXT_MENU_HOT_DPF_SCR			CBinary(STANDARD"\x07\x00\x00\x00\x4A",6)	//"DPF & SCR"
#define	STD_TEXT_MENU_HOT_IMMO_KEYS		CBinary(STANDARD"\x07\x00\x00\x00\x4B",6)	//"Immo & Keys"
#define	STD_TEXT_MENU_HOT_INJECTOR		CBinary(STANDARD"\x07\x00\x00\x00\x4C",6)	//"Injector"
#define	STD_TEXT_MENU_HOT_STEERING		CBinary(STANDARD"\x07\x00\x00\x00\x4D",6)	//"Steering"
#define	STD_TEXT_MENU_HOT_SUSPENSION	CBinary(STANDARD"\x07\x00\x00\x00\x4E",6)	//"Suspension"
#define	STD_TEXT_MENU_HOT_THROTTLE		CBinary(STANDARD"\x07\x00\x00\x00\x4F",6)	//"Throttle"
#define	STD_TEXT_MENU_HOT_WDR					CBinary(STANDARD"\x07\x00\x00\x00\x51",6)	//"Window,door and roof"
#define	STD_TEXT_MENU_HOT_SEATS				CBinary(STANDARD"\x07\x00\x00\x00\x52",6)	//"Seats"
#define	STD_TEXT_MENU_HOT_ODOMETER		CBinary(STANDARD"\x07\x00\x00\x00\x53",6)	//"Odometer"
#define	STD_TEXT_MENU_HOT_LANGUAGE		CBinary(STANDARD"\x07\x00\x00\x00\x54",6)	//"Language Change"
#define	STD_TEXT_MENU_HOT_HEADLAMP		CBinary(STANDARD"\x07\x00\x00\x00\x55",6)	//"Headlamp"
#define	STD_TEXT_MENU_HOT_TIRE				CBinary(STANDARD"\x07\x00\x00\x00\x56",6)	//"Change tire size"
#define	STD_TEXT_MENU_HOT_TEC					CBinary(STANDARD"\x07\x00\x00\x00\x57",6)	//"TEC Learn"
#define	STD_TEXT_MENU_HOT_TPMS_S			CBinary(STANDARD"\x07\x00\x00\x00\x58",6)	//"TPMS"
#define	STD_TXT_MSG_FAULT_REASONS		CBinary(STANDARD"\x07\x00\x00\x00\x59",6)	//"The selected function is not yet run by ECU, possible reasons:\n1.The engine is running \n2.The vehicle has current diagnostic fault code(s) which remain(s) unrepaired."
#define	STD_TXT_MSG_NOT_SUPPORTED			CBinary(STANDARD"\x07\x00\x00\x00\x5A",6)	//"The selected function is not supported by the ECU."
#define	STD_TXT_MSG_FAILED_FEEDBACK		CBinary(STANDARD"\x07\x00\x00\x00\x5B",6)	//"Running the selected function failed, please upload datalog and give feedback to vendor."
#define	STD_TXT_MSG_INCORRECT_MODEL		CBinary(STANDARD"\x07\x00\x00\x00\x5C",6)	//"Incorrect model associated.\n Do you want to download \"%s\" software?"

//商用车 标准库串信息
#define		TTL_CV_TASKINI						"Taskini"
#define		TXT_CV_SOPATH						"SoPath"
#define		TXT_CV_INPUTFILE					"InputFile"
#define		TXT_CV_OUTPUTFILE					"OutputFile"
#define		TXT_CV_MENUFILE						"MenuFile"
#define		TXT_CV_MENUID						"MenuID"
#define		TXT_CV_VEHICLENAME					"VehicleName"
#define		TXT_CV_SCANTYPE						"ScanType"
#define		TXT_CV_HEADBYTE						"HeadByte"
#define		TXT_CV_NUM							"Num"
#define		TXT_CV_MODULEINFO					"ModuleInfo"
#define		TXT_CV_TASKID						"TaskID"
#define		TXT_CV_MODULENAME					"ModuleName"


#define	STD_TXT_Replace 				                            CBinary(STANDARD"\x07\x00\x00\x00\x5D",6)	// "Replace brake pads (operating guide)” 
#define	STD_TEXT_MENU_HOT_parking_brake 			              CBinary(STANDARD"\x07\x00\x00\x00\x5E",6)	// "Please release the parking brake "
#define	STD_TEXT_MENU_HOT_Releasing 			                  CBinary(STANDARD"\x07\x00\x00\x00\x5F",6)	// "Releasing to the service position…"
#define	STD_TEXT_MENU_HOT_proceed 		                      CBinary(STANDARD"\x07\x00\x00\x00\x61",6)	// "Turn ignition switch OFF. \nReplace the brake pad and finish installation. \nTurn ignition switch ON.\nPlease click OK to proceed."
#define	STD_TEXT_MENU_HOT_Exiting_the_service_position 		  CBinary(STANDARD"\x07\x00\x00\x00\x62",6)	// "Exiting the service position…"
#define	STD_TEXT_MENU_HOT_apply_the_parking_brake 		      CBinary(STANDARD"\x07\x00\x00\x00\x63",6)	// "Please apply the parking brake"
#define	STD_TEXT_MENU_HOT_Rear_brake  		                  CBinary(STANDARD"\x07\x00\x00\x00\x64",6)	// "Rear brake pad replacement completed"
#define	STD_TEXT_MENU_HOT_Auto_oil_reset	                  CBinary(STANDARD"\x07\x00\x00\x00\x65",6)	// "Auto oil reset"
#define	STD_TEXT_MENU_HOT_Manual_oil_reset 		              CBinary(STANDARD"\x07\x00\x00\x00\x66",6)	// "Manual oil reset"


#endif
