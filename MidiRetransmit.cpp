// MidiRetransmit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "pm\portmidi.h"
#include "pm\pmutil.h"
#include "pm\pmwinmm.h"
#include "pm\porttime.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <assert.h>
#include <cstdio>

#define scnaf scanf

#pragma comment(lib,"winmm.lib")

#define MAX_DATA 50000
#define STRING_MAX 256
#define INPUT_BUFFER_SIZE 100
#define OUTPUT_BUFFER_SIZE 0
#define DRIVER_INFO NULL
#define TIME_PROC ((int32_t (*)(void *)) Pt_Time)
#define TIME_INFO NULL
#define ASYNC_KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define KEY_DOWN(VK_NONAME) ((GetKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;

long i;
PmStream * midi;
PmStream * midiout;
PmError status; int length;
PmEvent buffer[1];

struct DEVICE {
	int i;
	int o;
	int trans;
	int latency;
	int check_time;
};

int GetNum(int a, int b) {
	int num;
	scanf("%d", &num);
	if (num >= a && num <= b) {
		return num;
	}
	else {
		printf("Invalid value. This number should be in the range of [%d,%d].\nType again:\n",a,b);
		return GetNum(a, b);
	}
}

void PrintDeivce() {
	int default_in = Pm_GetDefaultInputDeviceID();
	int default_out = Pm_GetDefaultOutputDeviceID();
	for (int i = 0; i < Pm_CountDevices(); i++) {
		char *deflt;
		const PmDeviceInfo *info = Pm_GetDeviceInfo(i);

		printf("%d: %s, %s", i, info->interf, info->name);
		if (info->input) {
			deflt = (i == default_in ? "default " : "");
			printf(" (%sinput)", deflt);
			printf("\n");
		}
		if (info->output) {
			deflt = (i == default_out ? "default " : "");
			printf(" (%soutput)", deflt);
			printf("\n");
		}
	}
}

DEVICE SelDevice() {
	DEVICE dev;
	/*
	int default_in = Pm_GetDefaultInputDeviceID();
	int default_out = Pm_GetDefaultOutputDeviceID();
	for (int i = 0; i < Pm_CountDevices(); i++) {
		char *deflt;
		const PmDeviceInfo *info = Pm_GetDeviceInfo(i);

		printf("%d: %s, %s", i, info->interf, info->name);
		if (info->input) {
			deflt = (i == default_in ? "default " : "");
			printf(" (%sinput)", deflt);
			printf("\n");
		}
		if (info->output) {
			deflt = (i == default_out ? "default " : "");
			printf(" (%soutput)", deflt);
			printf("\n");
		}
	}
	*/
	PrintDeivce();
	int num_device = Pm_CountDevices();
	printf("Type the number of INPUT device:");
	dev.i = GetNum(0, num_device);

	printf("Type the number of OUTPUT device:");
	dev.o = GetNum(0, num_device);

	printf("Type the transpotion value:");
	dev.trans = GetNum(-127, 127);

	printf("Type the transmission latency:");
	dev.latency = GetNum(0, 500000);
	
	freopen("MRTconfig.ini", "w", stdout);
	cout << 1 << " " << dev.i << " " << dev.o << " " << dev.trans << " " << dev.latency;
	freopen("CON", "w", stdout);

	return dev;
}

void OpenDevice(DEVICE dev) {
	i = 0;
	Pt_Start(1, 0, 0);
	Pm_OpenInput(&midi,
		dev.i,
		DRIVER_INFO,
		INPUT_BUFFER_SIZE,
		TIME_PROC,
		TIME_INFO);
	Pm_OpenOutput(&midiout,
		dev.o,
		DRIVER_INFO,
		OUTPUT_BUFFER_SIZE,
		TIME_PROC,
		TIME_INFO,
		dev.latency
	);
	cout << "Device Opened." << endl;
}

void Transpose(DEVICE dev) {
	if (Pm_MessageStatus(buffer[0].message) != 176) {
		buffer[0].message = Pm_Message((long)Pm_MessageStatus(buffer[0].message), (long)Pm_MessageData1(buffer[0].message) + dev.trans, (long)Pm_MessageData2(buffer[0].message));
	}
	return;
}

void RunTransmit(DEVICE dev) {
	Pm_SetFilter(midi, PM_FILT_ACTIVE | PM_FILT_CLOCK);
	i = 0;
	cout << "Press ESC to exit." << endl;
	while (1) {

		/*
		if (KEY_DOWN(27)) {
			cout << "Exiting..." << endl;
			break;
		}
		*/
		if (_kbhit()) {
			if (KEY_DOWN(27)) {
				cout << "Exiting..." << endl;
				break;
			}
		}

		status = Pm_Poll(midi);
		if (status == TRUE) {
			length = Pm_Read(midi, buffer, 1);
			if (length > 0) {
				Transpose(dev);
				Pm_Write(midiout, buffer, 1);
				printf("Got message : time %ld, channel %ld, note %ld, dynamics %ld\n",
					(long)buffer[0].timestamp,
					(long)Pm_MessageStatus(buffer[0].message),
					(long)Pm_MessageData1(buffer[0].message),
					(long)Pm_MessageData2(buffer[0].message));
			}
			else {
				assert(0);
			}
		}
		Sleep(1);
	}
	
	Pm_Close(midi);
	Pm_Close(midiout);
	Pm_Terminate();
	cout << "See you next time." << endl;
	Sleep(500);
	return;
}


int main(int argc){

	if (argc != 1) {
		freopen("MRTdevice.txt", "w", stdout);
		PrintDeivce();
		freopen("CON", "w", stdout);
		return 0;
	}
	


	DEVICE device;
	freopen("MRTconfig.ini", "r", stdin);
	scanf("%ld", &i);
	if (i == 1) {
		scanf("%d%d%d%d", &device.i, &device.o, &device.trans, &device.latency);
		int num_device = Pm_CountDevices();
		if (device.i <= num_device && device.i >= 0 && device.o <= num_device && device.o >= 0 && device.trans >= -127 && device.trans <= 127 && device.latency >= 0 && device.latency <= 500000) {
			cout << "Config file loaded." << endl;
			const PmDeviceInfo *infoin = Pm_GetDeviceInfo(device.i);
			printf("Input: %d: %s, %s \n", device.i, infoin->interf, infoin->name);
			const PmDeviceInfo *infoout = Pm_GetDeviceInfo(device.o);
			printf("Output: %d: %s, %s \n", device.o, infoout->interf, infoout->name);
			cout << "Transpose = " << device.trans << "\nLatency = " << device.latency << "\nPress Enter to continue.\nPress any other key to reselect." << endl;
			int ch = _getch();
			if (ch != 13) {
				freopen("CON", "r", stdin);
				SelDevice();
			}
			else {
				freopen("CON", "r", stdin);
			}
		}
		else {
			cout << "Invalid config file." << endl;
			freopen("CON", "r", stdin);
			device = SelDevice();
		}
	}
	else {
		freopen("CON", "r", stdin);
		device = SelDevice();
	}

	OpenDevice(device);

	RunTransmit(device);
	
	
	return 0;
}

