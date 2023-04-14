#include<windows.h>
#include"InnerDllServer.h"

//CO class- COM's class or concrete class
class CMultiplicationDivision :public IMultiplication, IDivision
{
private:
	LONG m_cRef;
public:
	//Constructor
	CMultiplicationDivision(void);//for old OS void is there.
	//Destructor
	~CMultiplicationDivision(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IMultiplication method
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);

	//IDivision method
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

};

//ClassFactory class
class CMultiplicationDivisionClassFactory :public IClassFactory
{
private:
	LONG m_cRef;
public:
	//Construtor and Destructor
	CMultiplicationDivisionClassFactory(void);
	~CMultiplicationDivisionClassFactory(void);

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

//CMultiplicationDivision implementation
//Construtor
CMultiplicationDivision::CMultiplicationDivision(void)
{
	//code
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}
//Destructor
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//IUnknown Method implementation
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IMultiplication*>(this);

	}
	else if (riid == IID_IMultiplication)
	{
		*ppv = static_cast<IMultiplication*>(this);
	}
	else if (riid == IID_IDivision)
	{
		*ppv = static_cast<IDivision*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CMultiplicationDivision::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return m_cRef;

}

ULONG CMultiplicationDivision::Release(void)
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

//IMultiplication Implementation
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int* pMultiply)
{
	//code
	*pMultiply = num1 * num2;
	return S_OK;
}

HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int* pDivision)
{
	//code
	*pDivision = num1 / num2;
	return S_OK;
}

//CMultiplicationDivisionClassFactory implemetation
//Constructor 
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	//code
	m_cRef = 1;
}

//Destructor
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	//code
	
}

//IUnknown method implementation
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return m_cRef;

}

ULONG CMultiplicationDivisionClassFactory::Release(void)
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
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variables 
	CMultiplicationDivision* pCMultiplicationDivision = NULL;
	HRESULT hr;
	
	//code
	if (pUnkOuter != NULL)
	{
		return CLASS_E_NOAGGREGATION;
	}
	pCMultiplicationDivision = new CMultiplicationDivision;
	if (pCMultiplicationDivision == NULL)
	{
		return E_OUTOFMEMORY;
	}
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();
	return hr;
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
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

//Exportable COM dll method
extern "C" HRESULT  __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//variable 
	CMultiplicationDivisionClassFactory* pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_MultiplicationDivision)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL)
	{
		return E_OUTOFMEMORY;
	}
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();
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

