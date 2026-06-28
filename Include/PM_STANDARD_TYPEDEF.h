#pragma once

#include "PM_STRUCTURE.h"

//******************************
//* Enum / Find Device API
//******************************

//*	Enum Device Callback function
//*	input parameter :	szDeviceName : Device name
//*						szProduct  : Device Product name
//*						iPortIndex : USB or COM port index
//*	output parameter :	none
//*	return value :		TRUE  : Enum success
//*						FALSE : Enum failed
typedef BOOL (*ENUM_PROCW) (WCHAR szDeviceName[MAX_PATH], WCHAR szProduct[20], INT iPortIndex);
typedef BOOL (*ENUM_PROCA) ( CHAR szDeviceName[MAX_PATH],  CHAR szProduct[20], INT iPortIndex);

//*	Enum Device Callback function
//*	input parameter :	szDeviceName : Device name
//*						szProduct  : Device Product name
//*						szPortName : USB port name
//*	output parameter :	none
//*	return value :		TRUE  : Enum success
//*						FALSE : Enum failed
typedef BOOL (*ENUM_PROC_EXW) (WCHAR szDeviceName[MAX_PATH], WCHAR szProduct[20], WCHAR szPortName[20]);
typedef BOOL (*ENUM_PROC_EXA) ( CHAR szDeviceName[MAX_PATH],  CHAR szProduct[20],  CHAR szPortName[20]);

//*	Find Hid Driver Device
//*	input parameter :	none
//*	output parameter :	*hDevice  : Device handle
//*						szProduct : Device Product name
//*						*piUSBPortIndex : USB port index
//*	return value :		TRUE  : Find Device for Hid Driver
//*						FALSE : not Find Device for Hid Driver
#ifdef UNICODE
#define SZFINDHIDDEVICE	"FindHidDeviceW"
typedef BOOL (* pFnFindHidDevice)(HANDLE *phDevice, WCHAR szProduct[20], INT *piUSBPortIndex);
#else
#define SZFINDHIDDEVICE	"FindHidDeviceA"
typedef BOOL (* pFnFindHidDevice)(HANDLE *phDevice,  CHAR szProduct[20], INT *piUSBPortIndex);
#endif

//*	Find PenMount Driver Device
//*	input parameter :	none
//*	output parameter :	*hDevice  : Device handle
//*						szProduct : Device Product name
//*						*piUSBPortIndex : USB port index
//*	return value :		TRUE  : Find Device for PenMount Driver
//*						FALSE : not Find Device for PenMount Driver
#ifdef UNICODE
#define SZFINDPMDEVICE	"FindPMDeviceW"
typedef BOOL (* pFnFindPMDevice)(HANDLE *phDevice, WCHAR szProduct[20], INT *piUSBPortIndex);
#else
#define SZFINDPMDEVICE	"FindPMDeviceA"
typedef BOOL (* pFnFindPMDevice)(HANDLE *phDevice,  CHAR szProduct[20], INT *piUSBPortIndex);
#endif

//*	Find RS232 Driver Device
//*	input parameter :	iComPort  : Com Port number
//*						iBaudRate : Baud Rate
//*	output parameter :	*hDevice  : Device handle
//*						szProduct : Device Product name
//*	return value :		TRUE  : Find Device for RS232 Driver
//*						FALSE : not Find Device for RS232 Driver
#ifdef UNICODE
#define SZFINDRSDEVICE	"FindRSDeviceW"
#define SZFIND9KDEVICE	"Find9KDeviceW"
typedef BOOL (* pFnFindRSDevice)(INT iComPort, INT iBaudRate, HANDLE *phDevice, WCHAR szProduct[20]);
typedef BOOL (* pFnFind9KDevice)(INT iComPort, INT iBaudRate, HANDLE *phDevice, WCHAR szProduct[20]);
#else
#define SZFINDRSDEVICE	"FindRSDeviceA"
#define SZFIND9KDEVICE	"Find9KDeviceA"
typedef BOOL (* pFnFindRSDevice)(INT iComPort, INT iBaudRate, HANDLE *phDevice,  CHAR szProduct[20]);
typedef BOOL (* pFnFind9KDevice)(INT iComPort, INT iBaudRate, HANDLE *phDevice,  CHAR szProduct[20]);
#endif

//*	Enumerate Hid Driver Device
//*	input parameter :	none
//*	output parameter :	Callback : Callback for ENUM_PROC
//*	return value :		TRUE  : Enum success
//*						FALSE : Enum failed
#ifdef UNICODE
#define SZENUMHIDDEVICE	"EnumerateHidDevicesW"
typedef BOOL (* pFnEnumHidDevice)(ENUM_PROCW Callback);
#else
#define SZENUMHIDDEVICE	"EnumerateHidDevicesA"
typedef BOOL (* pFnEnumHidDevice)(ENUM_PROCA Callback);
#endif

//*	Enumerate Hid Driver Device Ex
//*	input parameter :	none
//*	output parameter :	Callback : Callback for ENUM_PROC_EX
//*	return value :		TRUE  : Enum success
//*						FALSE : Enum failed
#ifdef UNICODE
#define SZENUMHIDDEVICEEX	"EnumerateHidDevicesExW"
typedef BOOL (* pFnEnumHidDeviceEx)(ENUM_PROC_EXW CallbackEx);
#else
#define SZENUMHIDDEVICEEX	"EnumerateHidDevicesExA"
typedef BOOL (* pFnEnumHidDeviceEx)(ENUM_PROC_EXA CallbackEx);
#endif

//*	Enumerate PenMount Driver Device
//*	input parameter :	byDeviceType : PenMount Device Type
//*	output parameter :	Callback : Callback for ENUM_PROC
//*	return value :		TRUE  : Enum success
//*						FALSE : Enum failed
#ifdef UNICODE
#define SZENUMPMDEVICE	"EnumeratePMDevicesW"
typedef BOOL (* pFnEnumPMDevice)(ENUM_PROCW Callback, BYTE byDeviceType);
#else
#define SZENUMPMDEVICE	"EnumeratePMDevicesA"
typedef BOOL (* pFnEnumPMDevice)(ENUM_PROCA Callback, BYTE byDeviceType);
#endif

//*	Enumerate PenMount Driver Device Ex
//*	input parameter :	byDeviceType : PenMount Device Type
//*	output parameter :	Callback : Callback for ENUM_PROC_EX
//*	return value :		TRUE  : Enum success
//*						FALSE : Enum failed
#ifdef UNICODE
#define SZENUMPMDEVICEEX	"EnumeratePMDevicesExW"
typedef BOOL (* pFnEnumPMDeviceEx)(ENUM_PROC_EXW CallbackEx, BYTE byDeviceType);
#else
#define SZENUMPMDEVICEEX	"EnumeratePMDevicesExA"
typedef BOOL (* pFnEnumPMDeviceEx)(ENUM_PROC_EXA CallbackEx, BYTE byDeviceType);
#endif

//*	Enumerate RS232 Driver Device
//*	input parameter :	none
//*	output parameter :	Callback : Callback for ENUM_PROC
//*	return value :		TRUE  : Enum success
//*						FALSE : Enum failed
#ifdef UNICODE
#define SZENUMRSDEVICE	"EnumerateRSDevicesW"
#define SZENUM9KDEVICE	"Enumerate9KDevicesW"
typedef BOOL (* pFnEnumRSDevice)(ENUM_PROCW Callback);
typedef BOOL (* pFnEnum9KDevice)(ENUM_PROCW Callback);
#else
#define SZENUMRSDEVICE	"EnumerateRSDevicesA"
#define SZENUM9KDEVICE	"Enumerate9KDevicesA"
typedef BOOL (* pFnEnumRSDevice)(ENUM_PROCA Callback);
typedef BOOL (* pFnEnum9KDevice)(ENUM_PROCA Callback);
#endif

//*	Open Device
//*	input parameter :	szDeviceName : Device name
//*	output parameter :	*hDevice : Device handle
//*	return value :		TRUE  : Open Device success
//*						FALSE : Open Device failed
#ifdef UNICODE
#define SZOPENDEVICE	"OpenDeviceW"
typedef BOOL (* pFnOpenDevice)(WCHAR szDeviceName[MAX_PATH], HANDLE *phDevice);
#else
#define SZOPENDEVICE	"OpenDeviceA"
typedef BOOL (* pFnOpenDevice)( CHAR szDeviceName[MAX_PATH], HANDLE *phDevice);
#endif

//*	Close Device
//*	input parameter  :	hDevice : Device handle
//*	output parameter :	none
//*	return value :		TRUE  : Close Device success
//*						FALSE : Close Device failed
//*	Function Name :		CloseDevice
typedef BOOL (* pFnCloseDevice)(HANDLE hDevice);

//*	Check Last Touch Device Handle
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pbRes : Last Touch Device Handle is equal to hDevice (TRUE) or not (FALSE)
//*	return value :		TRUE  : Check Last Touch Device Handle success
//*						FALSE : Check Last Touch Device Handle failed
//*	Function Name :		CheckLastTouchDeviceHandle
typedef BOOL (* pFnCheckLastTouchDeviceHandle)(HANDLE hDevice, BOOL *pbRes);

//******************************
//* Send Command API
//******************************

//*	Send Command
//*	input parameter :	hDevice : Device handle
//*						command : Send command
//*	output parameter :	result  : receive command
//*	return value :		TRUE  : Send Command success
//*						FALSE : Send Command failed
//*	Function Name :		SendCmd
typedef BOOL (* pFnSendCmd)(HANDLE hDevice, BYTE command[5], BYTE result[5]);

//******************************
//* Device Change Message API
//******************************

//*	Device Change Event Process
//*	input parameter :	wParam : Event Type
//*						lParam : Structure Pointer for specific event type
//*	output parameter :	*piDeviceChange : Device Change Message Event result
//*	return value :		TRUE  : Device Change Message Event success
//*						FALSE : Device Change Message Event failed
//*	Function Name :		PMDeviceChange
typedef BOOL (* pFnPMDeviceChange)(WPARAM wParam, LPARAM lParam, INT *piDeviceChange);

//*	Register Device Change Notify
//*	input parameter :	hWnd : Window handle which need notify
//*	output parameter :	pPmDeviceNotify : PenMount Device Notify Structure pointer
//*	return value :		TRUE  : Register Device Change Notify success
//*						FALSE : Register Device Change Notify failed
//*	Function Name :		RegisterNotify
typedef BOOL (* pFnRegisterNotify)(HWND hWnd, PPM_DEVICE_NOTIFY pPmDeviceNotify);

//*	Un-Register Device Change Notify
//*	input parameter :	pPmDeviceNotify : PenMount Device Notify Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Un-Register Device Change Notify success
//*						FALSE : Un-Register Device Change Notify failed
//*	Function Name :		UnRegisterNotify
typedef BOOL (* pFnUnRegisterNotify)(PPM_DEVICE_NOTIFY pPmDeviceNotify);

//******************************
//* Get Information API
//******************************

//*	Get Firmware Version
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmFwVersion : Firmware Version Structure pointer
//*	return value :		TRUE  : Get Firmware Version success
//*						FALSE : Get Firmware Version failed
#ifdef UNICODE
#define SZFNGETFWVERSION	"GetFWVersionW"
typedef BOOL (* pFnGetFWVersion)(HANDLE hDevice, PPM_FWVERW pPmFwVersion);
#else
#define SZFNGETFWVERSION	"GetFWVersionA"
typedef BOOL (* pFnGetFWVersion)(HANDLE hDevice, PPM_FWVERA pPmFwVersion);
#endif

//*	Get State Flag
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmStateFlag : State Flag Structure pointer
//*	return value :		TRUE  : Get State Flag success
//*						FALSE : Get State Flag failed
//*	Function Name :		GetStateFlag
typedef BOOL (* pFnGetStateFlag)(HANDLE hDevice, PPM_STATEFLAG pPmStateFlag);

//*	Get Panel Size Information
//*	input parameter :	hDevice : Device handle
//*						iIndex  : Index of Panel Size Information
//*	output parameter :	szPanelSize : Panel Size Information
//*	return value :		TRUE  : Get Panel Size Information success
//*						FALSE : Get Panel Size Information failed
#ifdef UNICODE
#define SZFNGETPANELSIZE	"GetPanelSizeInfoW"
typedef BOOL (* pFnGetPanelSizeInfo)(HANDLE hDevice, INT iIndex, WCHAR szPanelSize[40]);
#else
#define SZFNGETPANELSIZE	"GetPanelSizeInfoA"
typedef BOOL (* pFnGetPanelSizeInfo)(HANDLE hDevice, INT iIndex,  CHAR szPanelSize[40]);
#endif

//*	Get Cover Lens Information
//*	input parameter :	hDevice : Device handle
//*						iIndex  : Index of Cover Lens Information
//*	output parameter :	szPanelSize : Cover Lens Information
//*	return value :		TRUE  : Get Cover Lens Information success
//*						FALSE : Get Cover Lens Information failed
#ifdef UNICODE
#define SZFNGETCOVERLENS	"GetCoverLensInfoW"
typedef BOOL (* pFnGetCoverLensInfo)(HANDLE hDevice, INT iIndex, WCHAR szCoverLens[40]);
#else
#define SZFNGETCOVERLENS	"GetCoverLensInfoA"
typedef BOOL (* pFnGetCoverLensInfo)(HANDLE hDevice, INT iIndex,  CHAR szCoverLens[40]);
#endif

//*	Get Data Report State
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pbEnable : Data Report Enable (TRUE) or Disable (FALSE)
//*	return value :		TRUE  : Get Data Report State success
//*						FALSE : Get Data Report State failed
//*	Function Name :		GetDataReportState
typedef BOOL (* pFnGetDataReportState)(HANDLE hDevice, BOOL *pbEnable);

// Get Parameter CRC
//*	input parameter :	hDevice : Device handle
//*	output parameter :	*pwParaCRC : Parameter CRC
//*	return value :		TRUE  : Get Parameter CRC success
//*						FALSE : Get Parameter CRC failed
//*	Function Name :		GetParameterCRC
typedef BOOL (* pFnGetParameterCRC)(HANDLE hDevice, WORD *pwParaCRC);

// Get Parameter CRC Ex
//*	input parameter :	hDevice : Device handle
//*						pPmParaList : Parameter List Structure Pointer
//*	output parameter :	*pwParaCRC : Parameter CRC
//*	return value :		TRUE  : Get Parameter CRC Ex success
//*						FALSE : Get Parameter CRC Ex failed
//*	Function Name :		GetParameterCRCEx
typedef BOOL (* pFnGetParameterCRCEx)(HANDLE hDevice, PPM_PARALIST pPmParaList, WORD *pwParaCRC);

//*	Get PenMount Driver Touch Type
//*	input parameter :	hDevice : Device handle
//*	output parameter :	*pbyTouchType : Mouse Emulation (PMDRIVER_MOUSE) or Digitizer (PMDRIVER_DIGITIZER)
//*	return value :		TRUE  : Get PenMount Driver Touch Type success
//*						FALSE : Get PenMount Driver Touch Type failed
//*	Function Name :		GetPMDriverTouchType
typedef BOOL (* pFnGetPMDriverTouchType)(HANDLE hDevice, BYTE *pbyTouchType);

//*	Get Hid Report Type
//*	input parameter :	hDevice : Device handle
//*	output parameter :	*pbyReportType: HID_REPORT_WINDOWS8 ( Windows 8 Protocol ) or
//*										HID_REPORT_MOUSE ( Mouse Emulation ) or
//*										HID_REPORT_DIGITIZER_TOUCH ( Digitizer Touch ) or
//*										HID_REPORT_DIGITIZER_PEN ( Digitizer Pen ) or
//*										HID_REPORT_WIN8_PRESSURE ( Win8 Pressure Mode )
//*	return value :		TRUE  : Get Hid Report Type success
//*						FALSE : Get Hid Report Type failed
//*	Function Name :		GetHidReportType
typedef BOOL (* pFnGetHidReportType)(HANDLE hDevice, BYTE *pbyReportType);

//*	Get Touch and Hold Setting
//*	input parameter :	hDevice : Device handle
//*	output parameter :	*pbTouchAndHold : Touch and Hold Enable (TRUE) or Disable (FALSE)
//*	return value :		TRUE  : Get Touch and Hold Setting success
//*						FALSE : Get Touch and Hold Setting failed
//*	Function Name :		GetTouchAndHold
typedef BOOL (* pFnGetTouchAndHold)(HANDLE hDevice, BOOL *pbTouchAndHold);

//*	Get System Reference Information
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmSRInfo : System Reference Information Structure pointer
//*	return value :		TRUE  : Get System Reference Information success
//*						FALSE : Get System Reference Information failed
//*	Function Name :		GetSystemReferenceInformation
typedef BOOL (* pFnGetSystemReferenceInformation)(HANDLE hDevice, PPM_SR_INFO pPmSRInfo);

//*	Get Linux Support Device Rotate at Screen Rotate
//*	input parameter :	none
//*	output parameter :	*pbRotate : Device rotate at screen rotate (TRUE) or not (FALSE)
//*	return value :		TRUE  : Get Linux Support Device Rotate at Screen Rotate success
//*						FALSE : Get Linux Support Device Rotate at Screen Rotate failed
//*	Function Name :		GetLXSupportDeviceRotate
typedef BOOL (* pFnGetLXSupportDeviceRotate)(BOOL *pbRotate);

//******************************
//* Set Control API
//******************************

//*	Enable / Disable Data Report
//*	input parameter :	hDevice : Device handle
//*						bEnable : Switch Data Report Enable (TRUE) or Disable (FALSE)
//*	output parameter :	none
//*	return value :		TRUE  : Switch Data Report success
//*						FALSE : Switch Data Report failed
//*	Function Name :		EnableDataReport
typedef BOOL (* pFnEnableDataReport)(HANDLE hDevice, BOOL bEnable);

//*	Enable / Disable PCAP Scan
//*	input parameter :	hDevice : Device handle
//*						bEnable : Switch PCAP Scan Enable (TRUE) or Disable (FALSE)
//*	output parameter :	none
//*	return value :		TRUE  : Switch PCAP Scan success
//*						FALSE : Switch PCAP Scan failed
//*	Function Name :		EnablePCAPScan
typedef BOOL (* pFnEnablePCAPScan)(HANDLE hDevice, BOOL bEnable);

//*	Reset MPU
//*	input parameter :	hDevice : Device handle
//*	output parameter :	none
//*	return value :		TRUE  : Reset MPU success
//*						FALSE : Reset MPU failed
//*	Function Name :		ResetMPU
typedef BOOL (* pFnResetMPU)(HANDLE hDevice);

//*	Set PenMount Driver Touch Type
//*	input parameter :	hDevice : Device handle
//*						byTouchType : Mouse Emulation (PMDRIVER_MOUSE) or Digitizer (PMDRIVER_DIGITIZER)
//*	return value :		TRUE  : Set PenMount Driver Touch Type success
//*						FALSE : Set PenMount Driver Touch Type failed
//*	Function Name :		SetPMDriverTouchType
typedef BOOL (* pFnSetPMDriverTouchType)(HANDLE hDevice, BYTE byTouchType);

//*	Set Hid Report Type
//*	input parameter :	hDevice : Device handle
//*						byReportType :  HID_REPORT_WINDOWS8 ( Windows 8 Protocol ) or
//*										HID_REPORT_MOUSE ( Mouse Emulation ) or
//*										HID_REPORT_DIGITIZER_TOUCH ( Digitizer Touch ) or
//*										HID_REPORT_DIGITIZER_PEN ( Digitizer Pen ) or
//*										HID_REPORT_WIN8_PRESSURE ( Win8 Pressure Mode )
//*	return value :		TRUE  : Set Hid Report Type success
//*						FALSE : Set Hid Report Type failed
//*	Function Name :		SetHidReportType
typedef BOOL (* pFnSetHidReportType)(HANDLE hDevice, BYTE byReportType);

//*	Set Touch and Hold Setting
//*	input parameter :	hDevice : Device handle
//*						bTouchAndHold : Set Touch And Hold Enable (TRUE) Disable (FALSE)
//*	return value :		TRUE  : Set Touch and Hold Setting success
//*						FALSE : Set Touch and Hold Setting failed
//*	Function Name :		SetTouchAndHold
typedef BOOL (* pFnSetTouchAndHold)(HANDLE hDevice, BOOL bTouchAndHold);

//*	Callback function for Build Result Notify
//*	input parameter :	hDevice : Device handle
//*						byBuildSRProgress : Build SR Progress (if byBuildSRFailed == BUILDSR_INVALID_VALUE)
//*						byBuildSRFailed   : Build SR Failed Condition (if byBuildSRProgress == BUILDSR_INVALID_VALUE)
//*	output parameter :	none
//*	return value :		none
typedef VOID (*BUILDSR_RESULT_NOTIFY)(HANDLE hDevice, BYTE byBuildSRProgress, BYTE byBuildSRFailed);

//*	Build System Reference
//*	input parameter :	hDevice : Device handle
//*						szLogPath : Log Build System Reference Result File Path
//*	output parameter :	CallBack : CallBack for BUILDSR_RESULT_NOTIFY
//*						*pbyBuildRes : Build System Reference Result
//*	return value :		TRUE  : Firmware support Build System Reference
//*						FALSE : Firmware not support Build System Reference
#ifdef UNICODE
#define SZFNBUILDSR			"BuildSystemReferenceW"
typedef BOOL (* pFnBuildSystemReference)(HANDLE hDevice, BUILDSR_RESULT_NOTIFY CallBack, WCHAR szLogPath[MAX_PATH], BYTE *pbyBuildRes);
#else
#define SZFNBUILDSR			"BuildSystemReferenceA"
typedef BOOL (* pFnBuildSystemReference)(HANDLE hDevice, BUILDSR_RESULT_NOTIFY CallBack,  CHAR szLogPath[MAX_PATH], BYTE *pbyBuildRes);
#endif

//*	Continue Build System Reference
//*	input parameter :	hDevice : Device handle
//*						bContinueBuildSR : Continue Build System Reference (TRUE) or not (FALSE)
//*	output parameter :	none
//*	return value :		TRUE  : Continue Build System Reference success
//*						FALSE : Continue Build System Reference failed
//*	Function Name :		ContinueBuildSystemReference
typedef BOOL (* pFnContinueBuildSystemReference)(HANDLE hDevice, BOOL bContinueBuildSR);

//*	Combine PFP
//*	input parameter :	hDevice : Device handle
//*						szFilePath : PenMount Firmware File Path
//*	output parameter :	*pbyCombineRes : Combine PFP Firmware File Result
//*	return value :		TRUE  : Combine PFP Firmware File success
//*						FALSE : Combine PFP Firmware File failed
#ifdef UNICODE
#define SZFNCOMBINEPFP		"CombinePFPW"
typedef BOOL (* pFnCombinePFP)(HANDLE hDevice, WCHAR szFilePath[MAX_PATH], BYTE *pbyCombineRes);
#else
#define SZFNCOMBINEPFP		"CombinePFPA"
typedef BOOL (* pFnCombinePFP)(HANDLE hDevice,  CHAR szFilePath[MAX_PATH], BYTE *pbyCombineRes);
#endif

//*	Callback function for Diagnostic Test, include Open Short Test and Noise Level
//*	input parameter :	byDiagTestProgress : Diagnostic Test Progress (if byDiagTestFailed == DIAGTEST_INVALID_VALUE)
//*						byDiagTestFailed   : Diagnostic Test Failed Condition (if byDiagTestProgress == DIAGTEST_INVALID_VALUE)
//*	output parameter :	none
//*	return value :		none
typedef VOID (*DIAGTEST_RESULT_NOTIFY)(BYTE byDiagTestProgress, BYTE byDiagTestFailed);

// Open Short Test
//*	input parameter :	hDevice : Device handle
//*						szINIPath : The level used in Open Short Test File Path
//*						szLogPath : Log Open Short Test Result File Path
//*	output parameter :	CallBack : CallBack for DIAGTEST_RESULT_NOTIFY
//*						*pbyTestRes : Open Short Test Result Map for every Mutual node ( 1 : Great ; 2 : Bad )
//*	return value :		TRUE  : Open Short Test success
//*						FALSE : Open Short Test failed
#ifdef UNICODE
#define SZFNOPENSHORTTEST	"OpenShortTestW"
typedef BOOL (* pFnOpenShortTest)(HANDLE hDevice, DIAGTEST_RESULT_NOTIFY CallBack,
				WCHAR szINIPath[MAX_PATH], WCHAR szLogPath[MAX_PATH], BYTE *pbyTestRes);
#else
#define SZFNOPENSHORTTEST	"OpenShortTestA"
typedef BOOL (* pFnOpenShortTest)(HANDLE hDevice, DIAGTEST_RESULT_NOTIFY CallBack,
				 CHAR szINIPath[MAX_PATH],  CHAR szLogPath[MAX_PATH], BYTE *pbyTestRes);
#endif

// Noise Level
//*	input parameter :	hDevice : Device handle
//*						szLogPath : Log Noise Level Result File Path
//*						pPmNoiseLevelLvl : the level of Noise Level Structure pointer
//*	output parameter :	CallBack : CallBack for DIAGTEST_RESULT_NOTIFY
//*						*pbyTestRes : Noise Level Result Map for every Mutual node ( 1 : Great ; 3 : Good; 2 : Bad )
//*	return value :		TRUE  : Noise Level success
//*						FALSE : Noise Level failed
#ifdef UNICODE
#define SZFNNOISELEVEL		"NoiseLevelW"
typedef BOOL (* pFnNoiseLevel)(HANDLE hDevice, DIAGTEST_RESULT_NOTIFY CallBack,
				PPM_NOISELVL_LEVEL pPmNoiseLevelLvl, WCHAR szLogPath[MAX_PATH], BYTE *pbyTestRes);
#else
#define SZFNNOISELEVEL		"NoiseLevelA"
typedef BOOL (* pFnNoiseLevel)(HANDLE hDevice, DIAGTEST_RESULT_NOTIFY CallBack,
				PPM_NOISELVL_LEVEL pPmNoiseLevelLvl,  CHAR szLogPath[MAX_PATH], BYTE *pbyTestRes);
#endif

// Log Firmware Information
#ifdef UNICODE
#define SZFNLOGFWINFO		"LogFirmwareInformationW"
typedef BOOL (* pFnLogFirmwareInformation)(HANDLE hDevice, WCHAR szLogPath[MAX_PATH], WORD wLogFlag);
#else
#define SZFNLOGFWINFO		"LogFirmwareInformationA"
typedef BOOL (* pFnLogFirmwareInformation)(HANDLE hDevice,  CHAR szLogPath[MAX_PATH], WORD wLogFlag);
#endif

// Log Memory Dump
#ifdef UNICODE
#define SZFNLOGMEMORYDUMP		"LogMemoryDumpW"
typedef BOOL (* pFnLogMemoryDump)(HANDLE hDevice, WCHAR szLogPath[MAX_PATH]);
#else
#define SZFNLOGMEMORYDUMP		"LogMemoryDumpA"
typedef BOOL (* pFnLogMemoryDump)(HANDLE hDevice,  CHAR szLogPath[MAX_PATH]);
#endif

// Firmware Update (Support Multiple Thread) from PenMountP2 API
#ifdef UNICODE
#define SZFNFIRMWAREUPDATEEX	"FirmwareUpdateExW"
typedef BOOL (* pFnFirmwareUpdateEx)(WCHAR *szFilePath, WCHAR *szPortName, INT *piRes);
#else
#define SZFNFIRMWAREUPDATEEX		"FirmwareUpdateExA"
typedef BOOL (* pFnFirmwareUpdateEx)( CHAR *szFilePath,  CHAR *szPortName, INT *piRes);
#endif

// Get Firmware File Version from PenMountP2 API
#ifdef UNICODE
#define SZFNGETFIRMWAREFILEVERSION		"GetFirmwareFileVersionW"
typedef BOOL (* pFnGetFirmwareFileVersion)(WCHAR *szFilePath, WCHAR *szFileVersion, INT *piCRC);
#else
#define SZFNGETFIRMWAREFILEVERSION		"GetFirmwareFileVersionA"
typedef BOOL (* pFnGetFirmwareFileVersion)( CHAR *szFilePath,  CHAR *szFileVersion, INT *piCRC);
#endif

// Check RMT Device or not
//*	Function Name : CheckRMTDevice
typedef BOOL (* pFnCheckRMTDevice)(HANDLE hDevice, BOOL *pbIsRMTDevice);

// Start RMT Device Calibration
//*	Function Name : StartRMTCalibration
typedef BOOL (* pFnStartRMTCalibration)(HANDLE hDevice, INT iInnerPercent, INT iInnerPermille);

// Suspend RMT Device Calibration
//*	Function Name : SuspendRMTCalibration
typedef BOOL (* pFnSuspendRMTCalibration)(HANDLE hDevice);

// Check RMT Calibration State
//*	Function Name : RMTCheckState
typedef BOOL (* pFnRMTCheckState)(HANDLE hDevice, INT iState, BOOL *pbCheckState);

// Check RMT Device Calibration Result
//*	Function Name : RMTCalibrationResult
typedef BOOL (* pFnRMTCalibrationResult)(HANDLE hDevice, INT iNearByThreshold, BOOL *pbCalibrationReuslt);

//******************************
//* Get Parameter List API
//******************************

// Get Parameter List
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaList : Parameter List Structure pointer
//*	return value :		TRUE  : Get Parameter List success
//*						FALSE : Get Parameter List failed
//*	Function Name :		GetAPBTParaList
typedef BOOL (* pFnGetParameterList)(HANDLE hDevice, PPM_PARALIST pPmParaList);

//******************************
//* User Setting API
//******************************

//* Get Parameter General Info
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaGeneralInfo : Parameter General Info Structure pointer
//*	return value :		TRUE  : Get Parameter General Info success
//*						FALSE : Get Parameter General Info failed
//*	Function Name :		GetParameterGeneralInfo
typedef BOOL (* pFnGetParameterGeneralInfo)(HANDLE hDevice, PPM_PARA_GENERALINFO pPmParaGeneralInfo);

//* Flush Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pbyOutput : Flush Result
//*	return value :		TRUE  : Flush Parameter success
//*						FALSE : Flush Parameter failed
//*	Function Name :		FlushParameter
typedef BOOL (* pFnFlushParameter)(HANDLE hDevice, BYTE *pbyOutput);

//* Reload Default Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	none
//*	return value :		TRUE  : Reload Default Parameter success
//*						FALSE : Reload Default Parameter failed
//*	Function Name :		ReloadDefaultParameter
typedef BOOL (* pFnReloadDefaultParameter)(HANDLE hDevice);

//* Reload Flush Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	none
//*	return value :		TRUE  : Reload Flush Parameter success
//*						FALSE : Reload Flush Parameter failed
//*	Function Name :		ReloadFlushParameter
typedef BOOL (* pFnReloadFlushParameter)(HANDLE hDevice);

//* Lock / Unlock Parameter Update
//*	input parameter :	hDevice : Device handle
//*						bUpdateEn : Switch Parameter Update Enable (TRUE : Unlock) or Disable (FALSE : Lock)
//*	output parameter :	none
//*	return value :		TRUE  : Switch Parameter Update success
//*						FALSE : Switch Parameter Update failed
//*	Function Name :		ParameterUpdateLock
typedef BOOL (* pFnParameterUpdateLock)(HANDLE hDevice, BOOL bUpdateEn);

//* Get Host Interface Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaHostInterface : Host Interface Parameter Structure pointer
//*	return value :		TRUE  : Get Host Interface Parameter success
//*						FALSE : Get Host Interface Parameter failed
//*	Function Name :		GetParameterHostInterface
typedef BOOL (* pFnGetParameterHostInterface)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_HOSTINTERFACE pPmParaHostInterface);

//* Set Host Interface Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaHostInterface : Host Interface Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Host Interface Parameter success
//*						FALSE : Set Host Interface Parameter failed
//*	Function Name :		SetParameterHostInterface
typedef BOOL (* pFnSetParameterHostInterface)(HANDLE hDevice, PPM_PARA_HOSTINTERFACE pPmParaHostInterface);

//* Get Panel Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaPanel : Panel Parameter Structure pointer
//*	return value :		TRUE  : Get Panel Parameter success
//*						FALSE : Get Panel Parameter failed
//*	Function Name :		GetParameterPanel
typedef BOOL (* pFnGetParameterPanel)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_PANEL pPmParaPanel);

//* Set Panel Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaPanel : Panel Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Panel Parameter success
//*						FALSE : Set Panel Parameter failed
//*	Function Name :		SetParameterPanel
typedef BOOL (* pFnSetParameterPanel)(HANDLE hDevice, PPM_PARA_PANEL pPmParaPanel);

//* Get Finger Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaFinger : Finger Parameter Structure pointer
//*	return value :		TRUE  : Get Finger Parameter success
//*						FALSE : Get Finger Parameter failed
//*	Function Name :		GetParameterFinger
typedef BOOL (* pFnGetParameterFinger)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_FINGER pPmParaFinger);

//* Set Finger Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaFinger : Finger Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Finger Parameter success
//*						FALSE : Set Finger Parameter failed
//*	Function Name :		SetParameterFinger
typedef BOOL (* pFnSetParameterFinger)(HANDLE hDevice, PPM_PARA_FINGER pPmParaFinger);

//* Get Palm Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaPalm : Palm Parameter Structure pointer
//*	return value :		TRUE  : Get Palm Parameter success
//*						FALSE : Get Palm Parameter failed
//*	Function Name :		GetParameterPalm
typedef BOOL (* pFnGetParameterPalm)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_PALM pPmParaPalm);

//* Set Palm Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaPalm : Palm Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Palm Parameter success
//*						FALSE : Set Palm Parameter failed
//*	Function Name :		SetParameterPalm
typedef BOOL (* pFnSetParameterPalm)(HANDLE hDevice, PPM_PARA_PALM pPmParaPalm);

//* Get Base Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaBase : Base Parameter Structure pointer
//*	return value :		TRUE  : Get Base Parameter success
//*						FALSE : Get Base Parameter failed
//*	Function Name :		GetParameterBase
typedef BOOL (* pFnGetParameterBase)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_BASE pPmParaBase);

//* Set Base Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaBase : Base Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Base Parameter success
//*						FALSE : Set Base Parameter failed
//*	Function Name :		SetParameterBase
typedef BOOL (* pFnSetParameterBase)(HANDLE hDevice, PPM_PARA_BASE pPmParaBase);

//* Get Water Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaWater : Water Parameter Structure pointer
//*	return value :		TRUE  : Get Water Parameter success
//*						FALSE : Get Water Parameter failed
//*	Function Name :		GetParameterWater
typedef BOOL (* pFnGetParameterWater)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_WATER pPmParaWater);

//* Set Water Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaWater : Water Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Water Parameter success
//*						FALSE : Set Water Parameter failed
//*	Function Name :		SetParameterWater
typedef BOOL (* pFnSetParameterWater)(HANDLE hDevice, PPM_PARA_WATER pPmParaWater);

//* Get Anti-Noise Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaAntiNoise : Anti-Noise Parameter Structure pointer
//*	return value :		TRUE  : Get Anti-Noise Parameter success
//*						FALSE : Get Anti-Noise Parameter failed
//*	Function Name :		GetParameterAntiNoise
typedef BOOL (* pFnGetParameterAntiNoise)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_ANTINOISE pPmParaAntiNoise);

//* Set Anti-Noise Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaAntiNoise : Anti-Noise Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Anti-Noise Parameter success
//*						FALSE : Set Anti-Noise Parameter failed
//*	Function Name :		SetParameterAntiNoise
typedef BOOL (* pFnSetParameterAntiNoise)(HANDLE hDevice, PPM_PARA_ANTINOISE pPmParaAntiNoise);

//* Get Coordinate Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaCoordinate : Coordinate Parameter Structure pointer
//*	return value :		TRUE  : Get Coordinate Parameter success
//*						FALSE : Get Coordinate Parameter failed
//*	Function Name :		GetParameterCoordinate
typedef BOOL (* pFnGetParameterCoordinate)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_COORDINATE pPmParaCoordinate);

//* Set Coordinate Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaCoordinate : Coordinate Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Coordinate Parameter success
//*						FALSE : Set Coordinate Parameter failed
//*	Function Name :		SetParameterCoordinate
typedef BOOL (* pFnSetParameterCoordinate)(HANDLE hDevice, PPM_PARA_COORDINATE pPmParaCoordinate);

//* Get Power Saving Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaPowerSaving : Power Saving Parameter Structure pointer
//*	return value :		TRUE  : Get Power Saving Parameter success
//*						FALSE : Get Power Saving Parameter failed
//*	Function Name :		GetParameterPowerSaving
typedef BOOL (* pFnGetParameterPowerSaving)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_POWERSAVING pPmParaPowerSaving);

//* Set Power Saving Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaPowerSaving : Power Saving Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Power Saving Parameter success
//*						FALSE : Set Power Saving Parameter failed
//*	Function Name :		SetParameterPowerSaving
typedef BOOL (* pFnSetParameterPowerSaving)(HANDLE hDevice, PPM_PARA_POWERSAVING pPmParaPowerSaving);

//* Get Miscellaneous Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaMisc : Miscellaneous Parameter Structure pointer
//*	return value :		TRUE  : Get Miscellaneous Parameter success
//*						FALSE : Get Miscellaneous Parameter failed
//*	Function Name :		GetParameterMisc
typedef BOOL (* pFnGetParameterMisc)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_MISC pPmParaMisc);

//* Set Miscellaneous Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaMisc : Miscellaneous Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Miscellaneous Parameter success
//*						FALSE : Set Miscellaneous Parameter failed
//*	Function Name :		SetParameterMisc
typedef BOOL (* pFnSetParameterMisc)(HANDLE hDevice, PPM_PARA_MISC pPmParaMisc);

//* Get Drive IC Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaDriveIC : Drive IC Parameter Structure pointer
//*	return value :		TRUE  : Get Drive IC Parameter success
//*						FALSE : Get Drive IC Parameter failed
//*	Function Name :		GetParameterDriveIC
typedef BOOL (* pFnGetParameterDriveIC)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_DRIVEIC pPmParaDriveIC);

//* Set Drive IC Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaDriveIC : Drive IC Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Drive IC Parameter success
//*						FALSE : Set Drive IC Parameter failed
//*	Function Name :		SetParameterDriveIC
typedef BOOL (* pFnSetParameterDriveIC)(HANDLE hDevice, PPM_PARA_DRIVEIC pPmParaDriveIC);

//* Get Pressure Parameter
//*	input parameter :	hDevice : Device handle
//*	output parameter :	pPmParaPressure : Pressure Parameter Structure pointer
//*	return value :		TRUE  : Get Pressure Parameter success
//*						FALSE : Get Pressure Parameter failed
//*	Function Name :		GetParameterPressure
typedef BOOL (* pFnGetParameterPressure)(HANDLE hDevice, WORD wFunctionList, PPM_PARA_PRESSURE pPmParaPressure);

//* Set Pressure Parameter
//*	input parameter :	hDevice : Device handle
//*						pPmParaPressure : Pressure Parameter Structure pointer
//*	output parameter :	none
//*	return value :		TRUE  : Set Pressure Parameter success
//*						FALSE : Set Pressure Parameter failed
//*	Function Name :		SetParameterPressure
typedef BOOL (* pFnSetParameterPressure)(HANDLE hDevice, PPM_PARA_PRESSURE pPmParaPressure);

//******************************
//* Touch Event Notify API
//******************************

//*	Touch Notify Callback function
//*	input parameter :	byHead : Touch Notify Head
//*						wXPosition : Position for X-Axis
//*						wYPosition : Position for Y-Axis
//*	output parameter :	none
//*	return value :		TRUE  : Notify success
//*						FALSE : Notify failed
typedef BOOL (*TOUCH_PROC) (BYTE byHead, WORD wXPosition, WORD wYPosition);

//*	Touch Notify Callback Ex function
//*	input parameter :	byHead : Touch Notify Head
//*						wXPosition : Position for X-Axis
//*						wYPosition : Position for Y-Axis
//*						hDevice    : Device Handle for Touch Nofity
//*	output parameter :	none
//*	return value :		TRUE  : Notify success
//*						FALSE : Notify failed
typedef BOOL (*TOUCH_PROC_EX) (BYTE byHead, WORD wXPosition, WORD wYPosition, HANDLE hDevice);

//*	Pad Sense Callback function
//*	input parameter :	byHead : Touch Notify Head
//*						wXPosition : Position for X-Axis
//*						wYPosition : Position for Y-Axis
//*						byStatus   : Pad Sense status
//*						0 : Pen Up
//*						1 : Pen Down
//*						2 : after debounce
//*						3 : check slope success
//*						4 : after heavy time
//*						hDevice    : Device Handle for Touch Nofity
//*	output parameter :	none
//*	return value :		TRUE  : Notify success
//*						FALSE : Notify failed
typedef BOOL (*PADSENSE_PROC) (BYTE byHead, WORD wXPosition, WORD wYPosition, BYTE byStatus, HANDLE hDevice);
//*	Register Touch Notify
//*	input parameter :	Callback : Callback for TOUCH_PROC
//*	output parameter :	none
//*	return value :		TRUE  : Register Touch Notify success
//*						FALSE : Register Touch Notify failed
//*	Function Name :		RegisterTouchNotify
typedef BOOL (* pFnRegisterTouchNotify)(TOUCH_PROC CallBack);

//*	Register Touch Notify Ex
//*	input parameter :	CallbackEx : Callback for TOUCH_PROC_EX
//*	output parameter :	none
//*	return value :		TRUE  : Register Touch Notify Ex success
//*						FALSE : Register Touch Notify Ex failed
//*	Function Name :		RegisterTouchNotifyEx
typedef BOOL (* pFnRegisterTouchNotifyEx)(TOUCH_PROC_EX CallBackEx);

//*	Register PadSense Notify
//*	input parameter :	CallBack  : Callback for PADSENSE_PROC
//*						iSlope    : Slope threshold
//*						iHeavyTime: 
//*	output parameter :	none
//*	return value :		TRUE  : Register PadSense Notify success
//*						FALSE : Register PadSense Notify failed
//*	Function Name :		RegisterPadSenseNotify
typedef BOOL (* pFnRegisterPadSenseNotify)(PADSENSE_PROC CallBack, INT iSlope, INT iHeavyTime);
//*	Un-Register Touch Notify
//*	input parameter :	none
//*	output parameter :	none
//*	return value :		TRUE  : Un-Register Touch Notify success
//*						FALSE : Un-Register Touch Notify failed
//*	Function Name :		UnRegisterTouchNotify
typedef BOOL (* pFnUnRegisterTouchNotify)();
