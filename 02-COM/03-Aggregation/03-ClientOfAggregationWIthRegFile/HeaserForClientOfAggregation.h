#pragma once

class ISum :public IUnknown
{
public:virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

};

class ISubtract :public IUnknown
{
public:virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;

};

class IMultiplication :public IUnknown
{
public:virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;

};

class IDivision :public IUnknown
{
public:virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;

};

// {F32D4137-C724-4339-AE7B-8F94C3A7B070}
const CLSID CLSID_SumSubtract = { 0xf32d4137, 0xc724, 0x4339, 0xae, 0x7b, 0x8f, 0x94, 0xc3, 0xa7, 0xb0, 0x70 };


// {04B50E1E-2BC5-4A25-AD04-ADC77A546A6C}
const IID IID_ISum = { 0x4b50e1e, 0x2bc5, 0x4a25, 0xad, 0x4, 0xad, 0xc7, 0x7a, 0x54, 0x6a, 0x6c };

// {2BA9527D-39BB-4C4F-A13B-9523C006E4F2}
const IID IID_ISubtract = { 0x2ba9527d, 0x39bb, 0x4c4f, 0xa1, 0x3b, 0x95, 0x23, 0xc0, 0x6, 0xe4, 0xf2 };

// {8D6F2ACF-E1DD-4114-9146-B9DE6C04DFFF}
const IID IID_IMultiplication = { 0x8d6f2acf, 0xe1dd, 0x4114, 0x91, 0x46, 0xb9, 0xde, 0x6c, 0x4, 0xdf, 0xff };


// {4DB53B87-C43F-4DDF-A28A-DB0A303CCAEA}
const IID IID_IDivision = { 0x4db53b87, 0xc43f, 0x4ddf, 0xa2, 0x8a, 0xdb, 0xa, 0x30, 0x3c, 0xca, 0xea };





