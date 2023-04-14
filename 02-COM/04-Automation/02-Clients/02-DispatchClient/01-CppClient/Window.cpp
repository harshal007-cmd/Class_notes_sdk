//header files
#include<windows.h>
#include"AutomationServerWithRegFile.h"
#include"Window.h"



//global function declaration
LRESULT CALLBACK WndProg(HWND, UINT, WPARAM, LPARAM);

//global variable declaration

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[]=TEXT("WINDEV");

	//code
	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProg;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	//wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	
	//registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	//creating window
	hwnd = CreateWindow(szAppName,
		TEXT("HVS:Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,NULL,
		hInstance,
		NULL);

	//show window
	ShowWindow(hwnd,iCmdShow);

	//update the window
	UpdateWindow(hwnd);

	//Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProg(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variable declarations
	IDispatch* pIDispatch = NULL;
	HRESULT hr;
	int num1, num2, sum,sub;
	TCHAR str[255];
	OLECHAR* szFunName1 = L"SumOfTwoIntergers"; // L = ole char literal
	OLECHAR* szFunName2 = L"SubtractionOfTwoIntergers"; 
	VARIANT vArg[2];
	VARIANT vResult;
	DISPID dispid;
	DISPPARAMS params;
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoInitialize(NULL);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("COInitialize failed"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pIDispatch);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("CoCreateInstance failed to get IDispatch Inteface"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		num1 = 275;
		num2 = 225;
		//Get ID of SumofTwoIntergers 
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunName1,
			1,
			GetUserDefaultLCID(),
			&dispid);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("GetIDsOfNames() failed to get ID of SumofTwoIntergers()"), TEXT("ERROR"), MB_OK);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		//call SumofTwoIntergers by passing its ID to Invoke()
		VariantInit(vArg);
		vArg[0].vt = VT_INT;
		vArg[0].intVal = num2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = num1;
		VariantInit(&vResult);

		params.rgvarg = vArg;
		params.cArgs = 2;
		params.rgdispidNamedArgs = NULL;
		params.cNamedArgs = 0;

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD, &params,
			&vResult,
			NULL, NULL);

		sum = vResult.lVal;

		wsprintf(str, TEXT("Sum of %d and %d is :%d"), num1, num2, sum);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);
		
		//Get ID of SubtractionofTwoIntergers 
		hr = pIDispatch->GetIDsOfNames(IID_NULL,
			&szFunName2,
			1,
			GetUserDefaultLCID(),
			&dispid);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("GetIDsOfNames() failed to get ID of SubtractionofTwoIntergers()"), TEXT("ERROR"), MB_OK);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		//call SubtractionofTwoIntergers by passing its ID to Invoke()
		VariantInit(vArg);
		vArg[0].vt = VT_INT;
		vArg[0].intVal = num2;
		vArg[1].vt = VT_INT;
		vArg[1].intVal = num1;
		VariantInit(&vResult);

		params.rgvarg = vArg;
		params.cArgs = 2;
		params.rgdispidNamedArgs = NULL;
		params.cNamedArgs = 0;

		hr = pIDispatch->Invoke(dispid,
			IID_NULL,
			GetUserDefaultLCID(),
			DISPATCH_METHOD, &params,
			&vResult,
			NULL, NULL);

		sub = vResult.lVal;
		wsprintf(str, TEXT("Subtraction of %d and %d is :%d"), num1, num2, sub);
		MessageBox(hwnd, str, TEXT("Sub"), MB_OK);
		
		VariantClear(&vResult);
		VariantClear(vArg);
		pIDispatch->Release();
		pIDispatch = NULL;

		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		CoUninitialize();
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

