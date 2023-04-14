#include<windows.h>

BOOL WINAPI DllMain (HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{

	//code
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return TRUE;
}

__declspec(dllexport) int MakeCube(int num)
{
	//code
	return num * num * num;
}

