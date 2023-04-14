//header files
#include<windows.h>
#include"Window.h"
#include"HeaserForClientOfAggregation.h"


//global function declaration
LRESULT CALLBACK WndProg(HWND, UINT, WPARAM, LPARAM);

//global variable declaration
ISum *pISum = NULL;
ISubtract *pISubtract = NULL;
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;
//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[]=TEXT("WINDEV");
	HRESULT hr;

	//COM library initialization
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM initialization failed"), TEXT("ERROR"), MB_OK);
		exit(0);
	}
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

	//COM Uninitialization
	CoUninitialize();
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProg(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variable declarations
	HRESULT hr;
	int n1, n2, sum, sub, Multiply,Division;
	TCHAR str[255];
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		/*
		 HRESULT __stdcall CoCreateInstanse(REFCLSID rclsid, LPIUNKOWN pUnkOuter, DWORD dwClsCOntext,REFIID riid, void **ppv)
		{
			//Variables	
			IClassFactory pIClassFactory=NULL;
			HRESULT hr;
		
			//code
			hr=CoGetClassObject(rclsid,dwClsContext,NULL,IID_IClassFactory,(void**)%pIClassFactory);
			if(SUCCEEDED(hr))
			{
				pIClassFacotry->CreateInstance(pUnkOuter,riid,ppv);
				pIClassFacotry->Release();
			}
			return hr;
			}
		*/
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum cannot be obtain"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		n1 = 55;
		n2 = 45;
		pISum->SumOfTwoIntegers(n1, n2, &sum);
		wsprintf(str, TEXT("Sum of %d and %d is %d"), n1, n2, sum);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);

		pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		pISubtract->SubtractionOfTwoIntegers(n1, n2, &sub);
		wsprintf(str, TEXT("Subtraction of %d and %d is %d"), n1, n2, sub);
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);

		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication cannot be obtain"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		n1 = 30;
		n2 = 25;
		pIMultiplication->MultiplicationOfTwoIntegers(n1, n2, &Multiply);
		wsprintf(str, TEXT("Multiplication of %d and %d is %d"), n1, n2, Multiply);
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);

		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision cannot be obtain"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		n1 = 200;
		n2 = 25;
		pIDivision->DivisionOfTwoIntegers(n1, n2, &Division);
		wsprintf(str, TEXT("Division of %d and %d is %d"), n1, n2, Division);
		MessageBox(hwnd, str, TEXT("Subtraction"), MB_OK);

		//Safe release
		if (pIDivision)
		{
			pIDivision->Release();
			pIDivision = NULL;
		}
		if (pIMultiplication)
		{
			pIMultiplication->Release();
			pIMultiplication = NULL;
		}

		if (pISubtract)
		{
			pISubtract->Release();
			pISubtract = NULL;
		}
		if (pISum)
		{
			pISum->Release();
			pISum = NULL;
		}
		
		DestroyWindow(hwnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}



