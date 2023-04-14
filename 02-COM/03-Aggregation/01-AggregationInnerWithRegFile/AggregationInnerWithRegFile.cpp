#include<windows.h>
#include"AggregationInnerWithRegFile.h"

//Interface declarations
interface INoAggregationIUnknown
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

//CO class- COM's class or concrete class
class CMultiplicationDivision :public INoAggregationIUnknown, IMultiplication, IDivision
{
private:
	LONG m_cRef;
	IUnknown* m_pIUnknownOuter;
public:
	//Constructor
	CMultiplicationDivision(IUnknown*);
	//Destructor
	~CMultiplicationDivision(void);

	//IUnknown methods
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);


	//Aggregation IUnkown methods 

	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);
   
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
CMultiplicationDivision::CMultiplicationDivision(IUnknown *pIUnlknownOuter)
{
	//code

	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
	if (pIUnlknownOuter != NULL)
		m_pIUnknownOuter = pIUnlknownOuter;
	else
		m_pIUnknownOuter = reinterpret_cast<IUnknown*>
		(static_cast<INoAggregationIUnknown*>(this));
}
//Destructor
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//Aggregarion supporting IUnknown Method implementation 
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	return(m_pIUnknownOuter->QueryInterface(riid, ppv));
}
ULONG CMultiplicationDivision::AddRef(void)
{
	return(m_pIUnknownOuter->AddRef());
}
ULONG CMultiplicationDivision::Release()
{
	return(m_pIUnknownOuter->Release());
}

//Aggregation IUnknown Non-Supporting methods for Qr, Ar, Rr
HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
{
	//code
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<INoAggregationIUnknown*>(this);

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

ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return m_cRef;

}

ULONG CMultiplicationDivision::Release_NoAggregation(void)
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
	if ((pUnkOuter != NULL) && (riid!=IID_IUnknown))
	{
		return CLASS_E_NOAGGREGATION;
	}
	pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);
	if (pCMultiplicationDivision == NULL)
	{
		return E_OUTOFMEMORY;
	}
	hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);
	pCMultiplicationDivision->Release_NoAggregation();
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

