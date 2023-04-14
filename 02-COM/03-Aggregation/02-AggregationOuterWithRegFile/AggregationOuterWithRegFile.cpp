#include<windows.h>
#include"AggregationOuterWithRegFile.h"
#include"AggregationInnerWithRegFile.h"

//CO class- COM's class or concrete class
class CSumSubtract :public ISum, ISubtract
{
private:
	LONG m_cRef;
	IUnknown* m_pIUnknownInner;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;
public:
	//Constructor
	CSumSubtract(void);//for old OS void is there.
	//Destructor
	~CSumSubtract(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);

	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);

	//custom method for inner component
	HRESULT __stdcall InitializeInnerComponent(void);

};

//ClassFactory class
class CSumSubtractClassFactory :public IClassFactory
{
private:
	LONG m_cRef;
public:
	//Construtor and Destructor
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

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

//CSumSubtract implementation
//Construtor
CSumSubtract::CSumSubtract(void)
{
	//code
	m_cRef = 1;
	m_pIUnknownInner = NULL;
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	InterlockedIncrement(&glNumberOfActiveComponents);
}
//Destructor
CSumSubtract::~CSumSubtract(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
	if (m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}

//IUnknown Method implementation
HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<ISum*>(this);

	}
	else if (riid == IID_ISum)
	{
		*ppv = static_cast<ISum*>(this);
	}
	else if (riid == IID_ISubtract)
	{
		*ppv = static_cast<ISubtract*>(this);
	}
	else if (riid == IID_IMultiplication)
	{
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	}
	else if (riid == IID_IDivision)
	{
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG CSumSubtract::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return m_cRef;

}

ULONG CSumSubtract::Release(void)
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

HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int* pSum)
{
	//code
	*pSum = num1 + num2;
	return S_OK;
}
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int* pSubtraction)
{
	//code
	*pSubtraction = num1 - num2;
	return S_OK;
}

HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_MultiplicationDivision, reinterpret_cast<IUnknown*>(this)
		                 , CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&m_pIUnknownInner);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IUnkown interface can not be obtained from inner component "), TEXT("Error"), MB_OK);
		return E_FAIL;
	}

	hr = m_pIUnknownInner->QueryInterface(IID_IMultiplication, (void**)&m_pIMultiplication);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication interface can not be obtained from inner component "), TEXT("Error"), MB_OK);
		return E_FAIL;
	}

	hr = m_pIUnknownInner->QueryInterface(IID_IDivision, (void**)&m_pIDivision);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision interface can not be obtained from inner component "), TEXT("Error"), MB_OK);
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
		return E_FAIL;
	}
	return S_OK;
}


//CSumSubtractClassFactory implemetation
//Constructor 
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	//code
	m_cRef = 1;
}

//Destructor
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	//code
	
}

//IUnknown method implementation
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
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

ULONG CSumSubtractClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return m_cRef;

}

ULONG CSumSubtractClassFactory::Release(void)
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
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variables 
	CSumSubtract* pCSumSubtract = NULL;
	HRESULT hr;
	
	//code
	if (pUnkOuter != NULL)
	{
		return CLASS_E_NOAGGREGATION;
	}
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
	{
		return E_OUTOFMEMORY;
	}

	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Failed to Initialize inner component"), TEXT("Error"), MB_OK);
		pCSumSubtract->Release();
		return hr;
	}
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	return hr;
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractClassFactory* pCSumSubtractClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_SumSubtract)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
	{
		return E_OUTOFMEMORY;
	}
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();
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

