#pragma once
class ISum :public IUnknown
{
public:virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

};

class ISubtract :public IUnknown
{
public:virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;

};

// {F32D4137-C724-4339-AE7B-8F94C3A7B070}
const CLSID CLSID_SumSubtract = { 0xf32d4137, 0xc724, 0x4339, 0xae, 0x7b, 0x8f, 0x94, 0xc3, 0xa7, 0xb0, 0x70 };


// {04B50E1E-2BC5-4A25-AD04-ADC77A546A6C}
const IID IID_ISum = { 0x4b50e1e, 0x2bc5, 0x4a25, 0xad, 0x4, 0xad, 0xc7, 0x7a, 0x54, 0x6a, 0x6c };

// {2BA9527D-39BB-4C4F-A13B-9523C006E4F2}
const IID IID_ISubtract = { 0x2ba9527d, 0x39bb, 0x4c4f, 0xa1, 0x3b, 0x95, 0x23, 0xc0, 0x6, 0xe4, 0xf2 };



