// st_vcom_enable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// st_vcom_reset.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>   
#include <setupapi.h>   
#include <tchar.h>   
#include <stdio.h>   
#include <iostream>

#pragma comment(lib,"setupapi.lib") 

#include <iostream>

// ST Virtual COM
// 定义串口设备类的GUID
DEFINE_GUID(GUID_DEVCLASS_PORTS, 0x4D36E978, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
//IN LPTSTR HardwareId = (LPTSTR) "USB\\VID_0483&PID_5740&REV_0200";
// 设备硬件ID，用于识别目标设备
IN LPTSTR HardwareId1 = (LPTSTR)"VID_0483";
IN LPTSTR HardwareId2 = (LPTSTR)"VID_04D8";

std::string device_type = "ST Virtual COM\n";

// 声明接口使能函数
BOOL EnableNetInterfaces();

int main()
{
	// 调用接口使能函数，禁用再启用接口，间隔2000ms
	EnableNetInterfaces();
}

// 使能虚拟串口设备接口
BOOL EnableNetInterfaces()
{
	// 设置设备新状态为启用
	DWORD NewState = DICS_ENABLE;

	DWORD i, err;

	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA spDevInfoData;

	GUID guid = GUID_DEVCLASS_PORTS;
	// 获取当前系统中所有串口设备信息
	hDevInfo = SetupDiGetClassDevs((LPGUID)&guid, NULL, NULL, DIGCF_PRESENT);

	// 检查设备信息句柄是否有效
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		printf("Error getting %s devices\n", device_type.c_str());
		return false;
	}

	spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	// 枚举所有串口设备
	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
	{
		DWORD DataT;
		LPTSTR p, buffer = NULL;
		DWORD buffersize = 0;

		BOOL Found = false;

		// 获取设备的硬件ID属性
		while (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&spDevInfoData,
			SPDRP_HARDWAREID,
			&DataT,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() == ERROR_INVALID_DATA)
			{
				break;
			}
			else if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer)
					LocalFree(buffer);
				buffer = (LPTSTR)LocalAlloc(LPTR, buffersize);
			}
			else
			{
				goto cleanup_DeviceInfo;
			}
		}

		if (GetLastError() == ERROR_INVALID_DATA)
			continue;

		// 检查硬件ID是否匹配目标设备
		for (p = buffer; *p && (p < &buffer[buffersize]); p += lstrlen(p) + sizeof(TCHAR))
		{
			if (strstr((const char*)p, HardwareId1) || strstr((const char*)p, HardwareId2))
			{
				Found = TRUE;
				break;
			}
		}

		if (buffer)
			LocalFree(buffer);

		if (Found)
		{
			// 构造属性更改参数，准备启用设备
			SP_PROPCHANGE_PARAMS spPropChangeParams;
			spPropChangeParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
			spPropChangeParams.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
			spPropChangeParams.Scope = DICS_FLAG_GLOBAL;
			spPropChangeParams.StateChange = NewState;

			// 设置设备属性更改参数
			if (!SetupDiSetClassInstallParams(hDevInfo, &spDevInfoData, (SP_CLASSINSTALL_HEADER*)&spPropChangeParams, sizeof(spPropChangeParams)))
			{
				DWORD errorcode = GetLastError();
			}

			// 调用类安装器以更改设备状态（启用/禁用）
			if (!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, hDevInfo, &spDevInfoData))
			{
				DWORD errorcode = GetLastError();
			}

			//Sleep(2000);

			// 获取设备友好名称（如 COM 端口号）
			BYTE friendlyName[300] = { 0 };
			int port = 0;
			SetupDiGetDeviceRegistryProperty(hDevInfo, &spDevInfoData, SPDRP_FRIENDLYNAME,
				&DataT, friendlyName, sizeof(friendlyName), NULL);
			{
				const char* pstr;
				if (pstr = strstr((const char*)friendlyName, "(COM"))
				{
					sscanf_s(pstr + 4, "%d", &port);
				}
			}

			// 根据新状态输出结果
			switch (NewState)
			{
			case DICS_DISABLE:
				printf("Disable COM %d\n", port);
				break;
			case DICS_ENABLE:
				printf("Enable COM %d\n", port);
				break;
			default: break;
			}
		}
	}

cleanup_DeviceInfo:
	// 清理设备信息列表并恢复错误码
	err = GetLastError();
	SetupDiDestroyDeviceInfoList(hDevInfo);
	SetLastError(err);

	return true;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file