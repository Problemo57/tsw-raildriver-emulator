#ifndef TSW_DRIVER_EMULATOR_LIBRARY_H
#define TSW_DRIVER_EMULATOR_LIBRARY_H

#define uint unsigned int
#define longlong long long
#define ulonglong unsigned long long
#include <stdbool.h>

typedef int (*PHIDDataEvent)(unsigned char *pData, int deviceID, int error);
typedef int (*PHIDErrorEvent)(int deviceID, int status);

typedef struct  _HID_ENUM_INFO  {
    int     PID;
    int     Usage;
    int     UP;
    long    readSize;
    long    writeSize;
    char    DevicePath[256];
    int     Handle;
    int     Version;
    char    ManufacturerString[128];
    char    ProductString[128];
    char    SerialNumberString[128];
} TEnumHIDInfo;

#define MAX_XKEY_DEVICES		128
#define PI_VID					0x5F3

#define RAIL_DRIVER_ID           210

void SuppressDuplicateReports(long handle, bool disable);
void DisableDataCallback(long handle, bool disable);
bool IsDataCallbackDisabled(long handle);
bool GetSuppressDuplicateReports(long handle);
void GetErrorString(int errorNumber, char* errorString, int size);
int GetXKeyVersion(long handle);
int ReadLast(long handle, unsigned char* data);
int ReadData(long handle, unsigned char* data);
int BlockingReadData(long handle, unsigned char* data, int maxMillis);
int WriteData(long handle, const unsigned char* data);
int FastWrite(long handle, unsigned char* data);
int ClearBuffer(long handle);
int GetReadLength(long handle);
int SetDataCallback(long handle, PHIDDataEvent pDataEvent);
int SetErrorCallback(long handle, PHIDErrorEvent pErrorCall);
int GetWriteLength(long handle);
void DongleCheck2(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, uint param_8, uint *param_9, uint *param_10, uint *param_11, uint *param_12);
int SendLEDSausage(int param_1);
void CloseInterface(long handle);
void CleanupInterface(long handle);
void EnumeratePIE(int VID, TEnumHIDInfo* device_info, long* device_count);
int SetupInterfaceEx(long handle);

#endif //TSW_DRIVER_EMULATOR_LIBRARY_H
