#define UNICODE

#include<windows.h>
#include<stdio.h>
#include"AutomationServerWithRegFile.h"

//CO class- COM's class or concrete class
class CMyMath :public IMyMath
{
private:
	LONG m_cRef;
	ITypeInfo *m_pITypeInfo;
public:
	//Constructor
	CMyMath(void);//for old OS void is there.
	//Destructor
	~CMyMath(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IDispatch methods 
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);


	//ISum method
	HRESULT __stdcall SumOfTwoIntergers(int, int, int*);

	//ISubtract method
	HRESULT __stdcall SubtractionOfTwoIntergers(int, int, int*);

	//custom method
	HRESULT InitInstance(void);

};

//ClassFactory class
class CMyMathClassFactory :public IClassFactory
{
private:
	LONG m_cRef;
public:
	//Construtor and Destructor
	CMyMathClassFactory(void);
	~CMyMathClassFactory(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory methods
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);

};

//Global variables
LONG glNumberOfActiveComponents;
LONG glNumberOfServerLogs;

// {96842FCA-EFFF-4567-8E0D-92A4D10CB6F9}
const GUID LIBID_AutomationServer = { 0x96842fca, 0xefff, 0x4567, 0x8e, 0xd, 0x92, 0xa4, 0xd1, 0xc, 0xb6, 0xf9 };




BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
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

//CMyMath implementation
//Construtor
CMyMath::CMyMath(void)
{
	//code
	m_pITypeInfo = NULL;
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}
//Destructor
CMyMath::~CMyMath(void)
{
	//code
	if (m_pITypeInfo) {
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
	}
	InterlockedDecrement(&glNumberOfActiveComponents);
	
}

//IUnknown Method implementation
HRESULT CMyMath::QueryInterface(REFIID riid, void **ppv)
{
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IMyMath*>(this);

	}
	else if (riid == IID_IDispatch)
	{
		*ppv = static_cast<IMyMath*>(this);
	}
	else if (riid == IID_IMyMath)
	{
		*ppv = static_cast<IMyMath*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CMyMath::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return m_cRef;

}

ULONG CMyMath::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete this;
		return 0;
	}
	
	return m_cRef;
}

//ISum Implementation
HRESULT CMyMath::SumOfTwoIntergers(int num1, int num2, int* pSum)
{
	//code
	*pSum = num1 + num2;
	return S_OK;
}

HRESULT CMyMath::SubtractionOfTwoIntergers(int num1, int num2, int* pSubtract)
{
	//code
	*pSubtract = num1 - num2;
	return S_OK;
}

HRESULT CMyMath::InitInstance(void)
{
	void ComErrorDescriptionString(HWND, HRESULT);
	HRESULT hr;
	ITypeLib* pITypeLib = NULL;

	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, 0x00, &pITypeLib);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return hr;
		}
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return hr;
		}
		pITypeLib->Release();

	}
	return S_OK;
}

//CMyMathClassFactory implemetation
//Constructor 
CMyMathClassFactory::CMyMathClassFactory(void)
{
	//code
	m_cRef = 1;
}

//Destructor
CMyMathClassFactory::~CMyMathClassFactory(void)
{
	//code
	
}

//IUnknown method implementation
HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory*>(this);
	
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CMyMathClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return m_cRef;

}

ULONG CMyMathClassFactory::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete this;
		return 0;
	}
	else {
		return m_cRef;
	}
}

//IClassFactory method implementation
HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variables 
	CMyMath* pCMyMath = NULL;
	HRESULT hr;
	
	//code
	if (pUnkOuter != NULL)
	{
		return CLASS_E_NOAGGREGATION;
	}
	pCMyMath = new CMyMath;
	if (pCMyMath == NULL)
	{
		return E_OUTOFMEMORY;
	}
	pCMyMath->InitInstance();

	hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return hr;
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
{
	if (fLock)  
	{
		InterlockedIncrement(&glNumberOfServerLogs);

	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLogs);
	}
	return S_OK;
}

//IDispatch method Implementations
HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo)
{
	*pCountTypeInfo = 1;
	return S_OK;
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, 
	ITypeInfo** ppITypeInfo)
{
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0)
	{
		return(DISP_E_BADINDEX);
	}
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return(S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames,
	UINT cName, LCID lcid, DISPID* rgDispId)
{
	return(DispGetIDsOfNames(m_pITypeInfo, rgszNames, cName, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlag, DISPPARAMS* pDispParams, VARIANT* pVarResult, 
						EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	HRESULT hr;
	//Code
	hr = DispInvoke(this,
		m_pITypeInfo,
		dispIdMember,
		wFlag,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr);

	return hr;
}

//Exportable COM dll method
extern "C" HRESULT  __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//variable 
	CMyMathClassFactory* pCMyMathClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_MyMath)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL)
	{
		return E_OUTOFMEMORY;
	}
	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release();
	return hr;

}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	//code
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLogs == 0)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}

}

void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255]={};
	//code

	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&szErrorMessage, 0, NULL) != 0)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		swprintf_s(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);

	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}

