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

// {441B1396-A9C5-4515-8615-243577C8350B}
const CLSID CLSID_SumSubtract = { 0x441b1396, 0xa9c5, 0x4515, 0x86, 0x15, 0x24, 0x35, 0x77, 0xc8, 0x35, 0xb };

const IID IID_ISum = { 0x6cd56b3d, 0xc9e6, 0x4ffd, 0xb7, 0x17, 0xfd, 0xf, 0xf2, 0x54, 0xff, 0x37 };

// {204F806F-A1AF-44FB-8E7D-B2ADFD420FA1}
const IID IID_ISubtract = { 0x204f806f, 0xa1af, 0x44fb, 0x8e, 0x7d, 0xb2, 0xad, 0xfd, 0x42, 0xf, 0xa1 };

// {47BA3945-97AB-415C-8310-0E4565983164}
const IID IID_IMultiplication = { 0x47ba3945, 0x97ab, 0x415c, 0x83, 0x10, 0xe, 0x45, 0x65, 0x98, 0x31, 0x64 };


// {E19A535B-8F80-4B7F-A4F7-BD90D82C0729}
const IID IID_IDivision = { 0xe19a535b, 0x8f80, 0x4b7f, 0xa4, 0xf7, 0xbd, 0x90, 0xd8, 0x2c, 0x7, 0x29 };




