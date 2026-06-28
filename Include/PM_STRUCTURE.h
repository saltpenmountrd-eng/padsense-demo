#pragma once

//******************************
//* Definition
//******************************

#define PM_HANDLE						PVOID

// Touch Event Notify
// Function : Touch Notify Callback Function
#define TOUCH_DOWN						0x10
#define TOUCH_UP						0x20
#define TOUCH_ENABLE					0x30
#define TOUCH_DISABLE					0x40
#define EVENT_NOTIFY					0x50

// Structure : PM_DEVICE_NOTIFY
#define DEVICETYPE_COUNT				3

//* BYTE byDeviceType
//* Function : EnumeratePMDevices
#define DEVICE_PCI_USB					0x01
#define DEVICE_6K_USB					0x02
#define DEVICE_PCI_RS					0x04
#define DEVICE_6K_RS					0x08

//* INT *piDeviceChange
//* Function : PMDeviceChange
#define PMDC_NONE						-1
#define PMDC_REMOVE						0
#define PMDC_ARRIVAL					1
#define PMDC_FIELD_UPDATE				2
#define PMDC_UPDATE_FINISH				3

//* BYTE *pbyOutput
//* Function : FlushParameter
#define FLUSH_AP_PARA					0x01
#define FLUSH_BT_PARA					0x02
#define FLUSH_AP_SUCC					0x04
#define FLUSH_BT_SUCC					0x08

//* BYTE bySetParaRes
//* Structure : 0xF6 command structure series
#define CU_RS_NONE						0x00
#define CU_RS_RESET						0x01
#define CU_RS_REINIT					0x02
#define CU_RS_NOW						0x04
#define CU_RS_FAIL						0xFF

//* BYTE byHostInterface & pmHostInterface.byParameter
//* Structure : PM_PARA_HOSTINTERFACE
#define HOSTIF_USB						0x00
#define HOSTIF_UART						0x01
#define HOSTIF_I2C						0x02
#define HOSTIF_SPI						0x03
#define HOSTIF_AUTO2					0x04
#define HOSTIF_AUTO						0x08

//* BYTE pmHostInterface.byMaxValue
//* Structure : PM_PARA_HOSTINTERFACE
#define HOSTIF_USB_SUPPORT				0x01
#define HOSTIF_UART_SUPPORT				0x02
#define HOSTIF_I2C_SUPPORT				0x04
#define HOSTIF_SPI_SUPPORT				0x08
#define HOSTIF_AUTO2_SUPPORT			0x40
#define HOSTIF_AUTO_SUPPORT				0x80

//* BYTE pmBaudRateIndex.byParameter
//* Structure : PM_PARA_HOSTINTERFACE
#define BAUD_RATE_115200				0
#define BAUD_RATE_57600					1
#define BAUD_RATE_38400					2
#define BAUD_RATE_19200					3
#define BAUD_RATE_9600					4

//* BYTE pmHIDReport.byParameter
//* Structure : PM_PARA_HOSTINTERFACE
//* BYTE *pbyReportType / byReportType
//* Function : Get / SetHidReportType
#define HID_REPORT_WINDOWS8				0
#define HID_REPORT_MOUSE				1
#define HID_REPORT_DIGITIZER_TOUCH		2
#define HID_REPORT_DIGITIZER_PEN		3

//* BYTE pmWaterSwitch.byMaxValue
//* Structure : PM_PARA_WATER
#define USE_WATER_DETECT				0x01
#define USE_WATER_PERFORMANCE			0x02

//* BYTE pmWaterSwitch.byParameter
//* Structure : PM_PARA_WATER
#define ENABLE_WATER_DETECT				0x01
#define ENABLE_WATER_PERFORMANCE		0x11

//* BYTE pmOrientation.byParameter
//* Structure : PM_PARA_COORDINATE
#define LANDSPACE						0
#define PORTRAIT						1
#define LANDSPACE_FLIPPED				2
#define PORTRAIT_FLIPPED				3
#define LANDSPACE_XYSWAP				4
#define PORTRAIT_XYSWAP					5
#define LANDSPACE_FLIPPED_XYSWAP		6
#define PORTRAIT_FLIPPED_XYSWAP			7

//* BYTE pmIdleScanInterval.byParameter
//* Structure : PM_PARA_POWERSAVING
#define SCAN_INTERVAL_50MS				0
#define SCAN_INTERVAL_30MS				1
#define SCAN_INTERVAL_20MS				2
#define SCAN_INTERVAL_10MS				3

//* BYTE pmDrivingVoltage.byParameter
//* Structure : PM_PARA_DRIVEIC
#define DRIVING_VOLTAGE_0V				0
#define DRIVING_VOLTAGE_6V				1
#define DRIVING_VOLTAGE_8V				2
#define DRIVING_VOLTAGE_10V				3
#define DRIVING_VOLTAGE_12V				4
#define DRIVING_VOLTAGE_14V				5
#define DRIVING_VOLTAGE_16V				6
#define DRIVING_VOLTAGE_18V				7

//* BYTE pmCurrentLimit.byParameter
//* Structure : PM_PARA_DRIVEIC
#define CURRENT_LIMIT_200mA				0
#define CURRENT_LIMIT_600mA				1
#define CURRENT_LIMIT_1000mA			2
#define CURRENT_LIMIT_1500mA			3

//* BYTE byTouchType
//* Function : SetPMDriverTouchType
#define PMDRIVER_MOUSE					0x01
#define PMDRIVER_DIGITIZER				0x02

//* WORD wSRState
//* Structure : PM_SR_INFO
#define SRSTATE_INVALID					0x01

//* BYTE *pbyBuildRes
//* Function : BuildSystemReferenceW / A
#define BUILDSR_NOT_SUPPORT				0x00
#define BUILDSR_SUCCESS					0x01
#define BUILDSR_FAILED_SENDE4			0x02
#define BUILDSR_FAILED_SENDF5			0x03
#define BUILDSR_FAILED_SENDF6			0x04
#define BUILDSR_FAILED_TIMEOUT			0x05
#define BUILDSR_FAILED_STATE			0x06
#define BUILDSR_FAILED_NOISE			0x07
#define BUILDSR_FAILED_GET_BASE			0x08
#define BUILDSR_FAILED_OS				0x09
#define BUILDSR_FAILED_GET_DIFF			0x0A
#define BUILDSR_FAILED_FLAT				0x0B
#define BUILDSR_FAILED_SAVE				0x0C
#define BUILDSR_NOT_COMPLETE			0x80
#define BUILDSR_INVALID_VALUE			0xFF

//* BYTE *pbyCombineRes
//* Function : CombinePFPW / A
#define COMBPFP_NOT_SUPPORT				0x00
#define COMBPFP_SUCCESS					0x01
#define COMBPFP_FAILED_LOADFILE			0x02
#define COMBPFP_FAILED_GETFWINFO		0x03
#define COMBPFP_FAILED_GETPARALIST		0x04
#define COMBPFP_FAILED_GETPARACRC		0x05
#define COMBPFP_FAILED_SAVEFILE			0x06
#define COMBPFP_FAILED_CHECKFWFILE		0x07
#define COMBPFP_NOT_COMPLETE			0x80

//* BYTE byDiagTestProgress / byDiagTestFailed
//* Function : DIAGTEST_RESULT_NOTIFY
#define DIAGTEST_INVALID_VALUE			0xFF
#define DIAGTEST_NOT_COMPLETE			0x80

//* BYTE byDiagTestFailed
//* Function : DIAGTEST_RESULT_NOTIFY
#define OSTEST_SUCCESS					0x01
#define OSTEST_FAILED_GETRAWCOUNT		0x02
#define OSTEST_FAILED_SAME_DATA			0x03
#define OSTEST_FAILED_DEBOUNCE			0x04
#define OSTEST_FAILED_DRIVER_ABNORMAL	0x05
#define OSTEST_FAILED_SENSOR_ABNORMAL	0x06
#define OSTEST_FAILED_ABSOLUTE_DATA		0x07
#define OSTEST_FAILED_NEAR_RAW_COUNT	0x08
#define OSTEST_FAILED_BASE_FLAT			0x09
#define OSTEST_FAILED_FILE_OPEN			0x0A

#define NOILVL_SUCCESS					0x01
#define NOILVL_FAILED_GETRAWCOUNT		0x02
#define NOILVL_FAILED_FILE_OPEN			0x03

//* BYTE byDiagTestProgress
//* Function : DIAGTEST_RESULT_NOTIFY
#define OSTEST_WAIT_BASE_STABLE_FINISH	0x80
#define OSTEST_GET_RAW_COUNT_FINISH		0x81
#define OSTEST_GET_ALLPSCAN_FINISH		0x82
#define OSTEST_GET_MODE_DIFF_FINISH		0x83
#define OSTEST_CHECK_SAME_DATA			0x84
#define OSTEST_CHECK_DEBOUNCE			0x85
#define OSTEST_CHECK_DRIVER_ABNORMAL	0x86
#define OSTEST_CHECK_SENSOR_ABNORMAL	0x87
#define OSTEST_CHECK_ABSOLUTE_DATA		0x88
#define OSTEST_CHECK_ND_BASE_DATA		0x89
#define OSTEST_CHECK_NEAR_RAW_COUNT		0x8A
#define OSTEST_CHECK_BASE_FLAT			0x8B
#define OSTEST_LOG_TEST_RESULT			0x8C
#define OSTEST_FINISH					0x8D

//* BYTE *pbyTestRes
//* Function : OpenShortTestW / A
#define RESULT_GREAT	1
#define RESULT_BAD		2
#define RESULT_GOOD		3

//******************************
//* Structure typedef
//******************************

// Firmware version string structure
typedef struct _PM_FWVERW
{
	WCHAR szFWVer[50];
	WCHAR szSlvVer[4][50];
	BOOL  bBootMode;
	BOOL  bSlvBootMode[4];
	INT   iSlaveNumber;
} PM_FWVERW, *PPM_FWVERW;

typedef struct _PM_FWVERA
{
	CHAR  szFWVer[50];
	CHAR  szSlvVer[4][50];
	BOOL  bBootMode;
	BOOL  bSlvBootMode[4];
	INT   iSlaveNumber;
} PM_FWVERA, *PPM_FWVERA;

#ifdef UNICODE
typedef  PM_FWVERW   PM_FWVER;
typedef PPM_FWVERW  PPM_FWVER;
#else
typedef  PM_FWVERA   PM_FWVER;
typedef PPM_FWVERA  PPM_FWVER;
#endif
// State & Flag structure
typedef struct _PM_STATEFLAG
{
	BYTE byPCIMFlag;
	BYTE byPCIMState;
	BYTE byPCIMState2;
	BYTE byPCIMDIag;
} PM_STATEFLAG, *PPM_STATEFLAG;

// Register Device Notification structure
typedef struct _PM_DEVICE_NOTIFY
{
	HDEVNOTIFY g_hDeviceNotify[DEVICETYPE_COUNT];
} PM_DEVICE_NOTIFY, *PPM_DEVICE_NOTIFY;

// Parameter List structure
typedef struct _PM_PARALIST
{
	BYTE  byAPParaSize;
	BYTE  byBTParaSize;
	BYTE  byDbgParaSize;
	BYTE  bySlvParaSize;
	BYTE *pbyAPParaList;
	BYTE *pbyBTParaList;
	BYTE *pbyDbgParaList;
	BYTE *pbySlvParaList[4];
} PM_PARALIST, *PPM_PARALIST;

// System Reference Information Structure
typedef struct _PM_SR_INFO
{
	BYTE bySRMajorVersion;
	BYTE bySRMinorVersion;
	WORD wSRState;
} PM_SR_INFO, *PPM_SR_INFO;

// Open Short Test Threshold Structure
typedef struct _PM_OSTEST_LEVEL
{
	int iLevelMinus;
	int iLevelNode;
	int iLevelDeb;
	int iLevelDrv;
	int iLevelSen;
	int iLevelAbs;
} PM_OSTEST_LEVEL, *PPM_OSTEST_LEVEL;

#define NOILVL_LEVEL_COUNT_MAX	10
typedef struct _PM_NOISELVL_LEVEL
{
	double dLevel[NOILVL_LEVEL_COUNT_MAX][2];
	INT iResultLevel;
} PM_NOISELVL_LEVEL, *PPM_NOISELVL_LEVEL;

//******************************
//* Parameter Setting Structure typedef
//******************************

// Byte parameter set (include parameter and max value)
typedef struct _PARA_BYTE_PM
{
	BYTE byParameter;
	BYTE byMaxValue;
	BYTE byPreValue;
	BOOL bValid;
} PARA_BYTE_PM, *PPARA_BYTE_PM;

// Byte parameter set (include parameter, default value and max value)
typedef struct _PARA_BYTE_PMD
{
	BYTE byParameter;
	BYTE byMaxValue;
	BYTE byDefaultValue;
	BYTE byPreValue;
	BOOL bValid;
} PARA_BYTE_PMD, *PPARA_BYTE_PMD;

typedef struct _PARA_BYTE_PMMD
{
	BYTE byParameter;
	BYTE byMaxValue;
	BYTE byMinValue;
	BYTE byDefaultValue;
	BYTE byPreValue;
	BYTE byReserved[3];
	BOOL bValid;
} PARA_BYTE_PMMD, *PPARA_BYTE_PMMD;

// WORD parameter set (include parameter, default value)
typedef struct _PARA_WORD_PD
{
	WORD wParameter;
	WORD wDefaultValue;
	WORD wPreValue;
	BOOL bValid;
} PARA_WORD_PD, *PPARA_WORD_PD;

// General Info structure
typedef struct _PM_PARA_GENERALINFO
{
	DWORD cbSize;
	WORD  wFunctionList;
	BYTE  byMainVersion;
	BYTE  bySubVersion;
	BYTE  byDllSupportMainVersion;
	BYTE  byAPParameterFlushCount;
	BYTE  byBootParameterFlushCount;
	BYTE  byPeripheralClock;
	BYTE  byMPUClock;
	BYTE  byAPParameterFlushCountHigh;
	BYTE  byBootParameterFlushCountHigh;
	BYTE  byParameterMajorVersion;
	BYTE  byParameterMinorVersion;
	BYTE  byReserved[3];
} PM_PARA_GENERALINFO, *PPM_PARA_GENERALINFO;

// Host Interface structure
typedef struct _PM_PARA_HOSTINTERFACE
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PM pmHostInterface;
	PARA_BYTE_PM pmI2CAddress;
	PARA_BYTE_PM pmBaudRateIndex;
	BYTE  byHostInterface;
	BYTE  byHIDReportMask;
	BYTE  byReserved2[2];
	BOOL  bNewBaudRate;
	BYTE  byODMIFMask;
	BYTE  byHostIFList;
	BYTE  byAPHIFList;
	BYTE  byBTHIFList;
} PM_PARA_HOSTINTERFACE, *PPM_PARA_HOSTINTERFACE;

// Panel structure
typedef struct _PM_PARA_PANEL
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PM pmPanelSize;
	PARA_BYTE_PM pmCoverLens;
	PARA_BYTE_PM pmSensorSkip;
	PARA_BYTE_PM pmDriverSkip;
	PARA_BYTE_PM pmSensorPinNumber;
	PARA_BYTE_PM pmDriverPinNumber;
	BYTE  byXAxisPinNumber;
	BYTE  byYAxisPinNumber;
	BYTE  bySectorSize;
	BYTE  bySectorNumber;
	BYTE  bySlaveSensorPin;
	BYTE  byMasterSensorPin;
	BYTE  byDiplexShift;
	BYTE  byDiplexScale;
	WORD  wResolutionX;
	WORD  wResolutionY;
	BYTE  bySensorPinMinRange;
	BYTE  byDriverPinMinRange;
	BYTE  byPanelPitch;
	BYTE  byPanelVersion;
	WORD  wActiveAreaX;
	WORD  wActiveAreaY;
} PM_PARA_PANEL, *PPM_PARA_PANEL;

// Finger structure
typedef struct _PM_PARA_FINGER
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PM pmSensitivityLevel;
	PARA_BYTE_PM pmFingerNumber;
	PARA_BYTE_PM pmFingerStopNumber;
	PARA_BYTE_PM pmWindowLock;
	PARA_BYTE_PM pmWindowLock2;
	PARA_BYTE_PM pmFastMoveCheck;
	PARA_BYTE_PM pmPenDownDebounce;
	PARA_BYTE_PM pmPenUpDebounce;
	PARA_BYTE_PM pmMinimumScanTimer;
	BYTE  byMutualThreshold;
	BYTE  bySectorThreshold;
	BYTE  byReserved[2];
} PM_PARA_FINGER, *PPM_PARA_FINGER;

// Palm structure
typedef struct _PM_PARA_PALM
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PM pmPalmLimit;
	PARA_BYTE_PM pmPalmDisableRange;
	PARA_BYTE_PM pmPalmUpDebounce;
	PARA_BYTE_PM pmPalmEdgeEnable;
	PARA_BYTE_PM pmPalmFingerSize;
	PARA_BYTE_PM pmPalmRejectDisable;
} PM_PARA_PALM, *PPM_PARA_PALM;

// Base structure
typedef struct _PM_PARA_BASE
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PM pmBaseUpdateDriverNumber;
	PARA_BYTE_PM pmBaseUpdateDelayTime;
	PARA_BYTE_PM pmBaseUpdateInactiveSkipCount;
	PARA_BYTE_PM pmBaseUpdateActiveSkipCount;
	PARA_BYTE_PM pmBaseUpdateDisable;
	PARA_BYTE_PM pmSystemReferenceDisable;
} PM_PARA_BASE, *PPM_PARA_BASE;

// Water Performance structure
typedef struct _PM_PARA_WATER
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PMD pmdWaterSwitch;
	PARA_BYTE_PM  pmWaterDetectScanSkip;
	PARA_BYTE_PM  pmWaterDetectThreshold;
	PARA_BYTE_PM  pmWaterDetectThresholdOffset;
	PARA_BYTE_PMD pmdWaterPerformanceLevel;
	PARA_BYTE_PM  pmWaterPerformanceNegitaveFix;
	PARA_BYTE_PM  pmWaterPerformanceNegitaveThreshold;
	PARA_BYTE_PM  pmWaterPerformanceActiveThreshold;
	PARA_BYTE_PM  pmWaterPerformanceLockSwitch;
	BYTE  byAbnormalLevel;
	BYTE  byAbnormalCount;
	BYTE  byAbnormalThreshold;
	BYTE  byWaterPerformanceFlag;
} PM_PARA_WATER, *PPM_PARA_WATER;

// Anti Noise structure
typedef struct _PM_PARA_ANTINOISE
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PMD pmdLowPassFilter;
	PARA_BYTE_PM  pmNoiseAcceptThreshold;
	PARA_BYTE_PM  pmNoiseAcceptAdd;
	PARA_BYTE_PM  pmNoiseRelaxLevel;
	PARA_BYTE_PM  pmAbnAcceptThreshold;
	PARA_BYTE_PM  pmAbnAcceptAdd;
	PARA_BYTE_PM  pmAbnRelaxLevel;
	PARA_BYTE_PM  pmTwoDriverEnable;
} PM_PARA_ANTINOISE, *PPM_PARA_ANTINOISE;

// Coordinate structure
typedef struct _PM_PARA_COORDINATE
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_WORD_PD pdPanelLeft;
	PARA_WORD_PD pdPanelRight;
	PARA_WORD_PD pdPanelTop;
	PARA_WORD_PD pdPanelBottom;
	PARA_WORD_PD pdScreenLeft;
	PARA_WORD_PD pdScreenRight;
	PARA_WORD_PD pdScreenTop;
	PARA_WORD_PD pdScreenBottom;
	PARA_BYTE_PM pmXAxisReverse;
	PARA_BYTE_PM pmYAxisReverse;
	PARA_BYTE_PM pmXYAxisSwitch;
	PARA_BYTE_PM pmOrientation;
	BYTE  byZeroPosition;
	BYTE  byReserved;
	WORD  w2ndSubFunctionList;
	PARA_BYTE_PM pmEdgeLeft;
	PARA_BYTE_PM pmEdgeRight;
	PARA_BYTE_PM pmEdgeTop;
	PARA_BYTE_PM pmEdgeBottom;
} PM_PARA_COORDINATE, *PPM_PARA_COORDINATE;

// Power saving structure
typedef struct _PM_PARA_POWERSAVING
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PM pmSleepDisable;
	PARA_BYTE_PM pmIdleDisable;
	PARA_BYTE_PM pmIdleScanInterval;
	PARA_BYTE_PM pmIdleEnterDelay;
} PM_PARA_POWERSAVING, *PPM_PARA_POWERSAVING;

// Misc structure
typedef struct _PM_PARA_MISC
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PM pmWatchDogDisable;
	PARA_BYTE_PM pmEventNotifyDisable;
	PARA_BYTE_PM pmUSBRemoveWakeupKeep;
	PARA_BYTE_PM pmSmoothDisable;
} PM_PARA_MISC, *PPM_PARA_MISC;

// Drive IC structure
typedef struct _PM_PARA_DRIVEIC
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PM pmDrivingVoltage;
	PARA_BYTE_PM pmCurrentLimit;
	BYTE  byDriveICNumber;
	BYTE  byDrivePin[15];
} PM_PARA_DRIVEIC, *PPM_PARA_DRIVEIC;

// Pressure Structure
typedef struct _PM_PARA_PRESSURE
{
	DWORD cbSize;
	WORD  wSubFunctionList;
	BYTE  bySetParaRes;
	BYTE  byReserved0;
	BOOL  bValid;
	PARA_BYTE_PMMD pmmPressureADCCount;
	PARA_BYTE_PMMD pmmPressureDisable;
	PARA_BYTE_PMMD pmmPressureUnitDisable;
	PARA_BYTE_PMMD pmmPressureSet;
	PARA_BYTE_PMMD pmmPressureActiveThreshold;
} PM_PARA_PRESSURE, *PPM_PARA_PRESSURE;
