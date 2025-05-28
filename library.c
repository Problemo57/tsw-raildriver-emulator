#include "library.h"

#include <math.h>
#include <stdio.h>
#include <processthreadsapi.h>
#include <string.h>
#include <synchapi.h>

#define spoof_handle 41

#define RAIL_DRIVER_INPUT_FILE "raildriver_input"
#define LOG_FILE "raildriver_emulator_log.txt"
#define LEDS_FILE "raildriver_leds.txt"

PHIDDataEvent data_callback = NULL;
PHIDErrorEvent error_callback = NULL;

int _CRT_INIT(int dll_handle, int reason, longlong reserviert);

void logtext(char* text) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "%s\n", text);
    fclose(file);
}

unsigned long data_thread(void* arg) {
    FILE* file = fopen(RAIL_DRIVER_INPUT_FILE, "w");
    fclose(file);

    char data[16];
    while (data_callback != NULL) {
        FILE* file = fopen(RAIL_DRIVER_INPUT_FILE, "r");
        fread(data, 1, 15, file);
        fclose(file);
        data[14] = RAIL_DRIVER_ID;
        data[15] = '\0';

        data_callback((unsigned char*)data, spoof_handle, 0);
        Sleep(10);
    }
    return 0;
}

char led2char(unsigned char led) {
    if (led == 128) {
        return '.';
    }

    if (led & 128) {
        logtext("Led has Point");
        led ^= 128;
    }

    if (led == 0) {
        return ' ';
    }

    if (led == 63) {
        return '0';
    }
    if (led == 6) {
        return '1';
    }
    if (led == 91) {
        return '2';
    }
    if (led == 79) {
        return '3';
    }
    if (led == 102) {
        return '4';
    }
    if (led == 109) {
        return '5';
    }
    if (led == 125) {
        return '6';
    }
    if (led == 7) {
        return '7';
    }
    if (led == 127) {
        return '8';
    }
    if (led == 111) {
        return '9';
    }

    if (led == 64) {
        return '-';
    }

    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "l: %d\n", led);
    fclose(file);


    logtext("Not an Number Led");
    return 0;
}

void SuppressDuplicateReports(const long handle, const bool disable) {
    logtext("SuppressDuplicateReports");
}

void DisableDataCallback(const long handle, const bool disable) {
    logtext("SetDataCallback");

    if (handle != spoof_handle) {
        logtext("Wrong handle");
        return;
    }

    // ?
    if (disable) {
        data_callback = NULL;
    }
}

bool IsDataCallbackDisabled(const long handle) {
    logtext("IsDataCallbackDisabled");
    if (handle != spoof_handle) {
        logtext("Wrong handle");
        return false;
    }

    if (data_callback == NULL) {
        return true;
    }

    return false;
}

bool GetSuppressDuplicateReports(const long handle) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "GetSuppressDuplicateReports param_1: %ld\n", handle);
    fclose(file);
    return true;
}

void GetErrorString(const int errorNumber, char* errorString, const int size) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "GetErrorString param_1: %d, param_2: %p, param_3: %d\n", errorNumber, errorString, size);
    fclose(file);
}

int GetXKeyVersion(const long handle) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "GetXKeyVersion param_1: %ld\n", handle);
    fclose(file);
    return 0xffff;
}

int ReadLast(const long handle, unsigned char* data) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "ReadLast param_1: %ld, param_2: %p\n", handle, data);
    fclose(file);
    return 0x137;
}

int ReadData(const long handle, unsigned char* data) {
    logtext("ReadData");

    if (handle != spoof_handle) {
        logtext("Wrong handle");
        return -1;
    }

    // Constants
    data[0] = 0;
    data[14] = RAIL_DRIVER_ID;

    // TODO
    for (int i = 1; i < 15; i++) {
        data[i] = 0;
    }

    return 0;
}

int BlockingReadData(long handle, unsigned char* data, int maxMillis) {
    logtext("BlockingReadData");
    return 0x137;
}

int WriteData(const long handle, const unsigned char* data) {
    if (handle != spoof_handle) {
        logtext("Wrong handle");
        return -1;
    }

    if (data[1] == 134) {
        // Led Display
        const unsigned char led3 = data[2];
        const unsigned char led2 = data[3];
        const unsigned char led1 = data[4];

        FILE* file = fopen(LEDS_FILE, "w");

        if (led3 < 128 && led2 < 128 && led1 < 128) {
            fprintf(file, "%c%c%c", led2char(led1), led2char(led2), led2char(led3));
        }
        else if (led2 > 128 && led3 < 128 && led1 < 128) {
            fprintf(file, "%c%c.%c", led2char(led1), led2char(led2), led2char(led3));
        }
        else {
            logtext("Wrong leds");
        }

        fclose(file);
    }
    else if (data[1] == 133) {
        // Speaker

    }
    else {
        logtext("Unknown Command Code");
        return -1;
    }

    return 0;
}

int FastWrite(const long handle, unsigned char* data) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "FastWrite param_1: %ld, param_2: %p\n", handle, data);
    fclose(file);
    return 0x191;
}

int ClearBuffer(const long handle) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "ClearBuffer param_1: %ld\n", handle);
    fclose(file);
    return 0x259;
}

int GetReadLength(const long handle) {
    logtext("GetReadLength");

    if (handle != spoof_handle) {
        logtext("Wrong handle");
        return -1;
    }

    return 15;
}

int GetWriteLength(const long handle) {
    logtext("GetWriteLength");

    if (handle != spoof_handle) {
        logtext("Wrong handle");
        return -1;
    }

    return 9;
}

int SetDataCallback(const long handle, const PHIDDataEvent pDataEvent) {
    logtext("SetDataCallback");

    if (handle != spoof_handle) {
        logtext("Wrong handle");
        return -1;
    }

    data_callback = pDataEvent;
    CreateThread(NULL, 0, &data_thread, NULL, 0, NULL);
    return 0;
}

int SetErrorCallback(const long handle, const PHIDErrorEvent pErrorCall) {
    logtext("SetErrorCallback");

    if (handle != spoof_handle) {
        logtext("Wrong handle");
        return -1;
    }

    error_callback = pErrorCall;
    return 0;
}

void DongleCheck2(const int param_1, const int param_2, const int param_3, const int param_4, const int param_5, const int param_6, const int param_7, const uint param_8, const uint *param_9, const uint *param_10, const uint *param_11, const uint *param_12) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "DongleCheck param_1: %d, param_2: %d, param_3: %d, param_4: %d, param_5: %d, param_6: %d, param_7: %d, param_8: %d, param_9: %d, param_10: %d, param_11: %d, param_12: %d",
        param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, *param_9, *param_10, *param_11, *param_12);
    fclose(file);
}

int SendLEDSausage(const int param_1) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "SendLEDSausage param_1: %d\n", param_1);
    fclose(file);
    return 0x137;
}

void CloseInterface(const long handle) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "CloseInterface param_1: %ld\n", handle);
    fclose(file);
}

void CleanupInterface(const long handle) {
    FILE* file = fopen(LOG_FILE, "a");
    fprintf(file, "CleanupInterface param_1: %ld\n", handle);
    fclose(file);
}

void EnumeratePIE(const int VID, TEnumHIDInfo* device_info, long* device_count) {
    // VID: [in] Vendor Identification number, for all P.I. Engineering products this value is 5F3h or 1523.
    // device_info [out] Returned data on the enumerated devices.
    // device_count: [out] Number of PIE devices found.
    char text[300];
    sprintf(text, "EnumeratePIE, VID: %d, Device_Count: %ld, P: %p, Device_Info: %p", VID, *device_count, device_count, device_info);
    logtext(text);

    // Spoof one Device
    *device_count = 1;

    // 12 is the Usage Page for the Rail Driver
    // Write Len/Size has to be greater than 10
    const TEnumHIDInfo fake_device = {
        RAIL_DRIVER_ID,
        1,
        12,
        GetReadLength(spoof_handle),
        GetWriteLength(spoof_handle),
        "fake_device",
        spoof_handle,
        1,
        "Problemo",
        "Fake ProDevice",
        "v2001"
    };
    device_info[0] = fake_device;
    sprintf(text, "EnumeratePIE2, VID: %d, Device_Count: %ld, P: %p, Device_Info: %p", VID, *device_count, device_count, device_info);
    logtext(text);

    sprintf(text, "EnumeratePIE3, Device_Info: %d", device_info[0].PID);
    logtext(text);
}

int SetupInterfaceEx(const long handle) {
    logtext("SetupInterfaceEx");

    if (handle != spoof_handle) {
        logtext("Wrong handle");
        return -1;
    }

    return 0;
}



