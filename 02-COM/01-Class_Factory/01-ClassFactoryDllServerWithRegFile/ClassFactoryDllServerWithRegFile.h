#pragma once
class ISum :public IUnknown
{
public:virtual HRESULT __stdcall SumOfTwoIntergers(int, int, int*) = 0;

};

class ISubtract :public IUnknown
{
public:virtual HRESULT __stdcall SubtractionOfTwoIntergers(int, int, int*) = 0;

};

// {441B1396-A9C5-4515-8615-243577C8350B}
const CLSID CLSID_SumSubtract = { 0x441b1396, 0xa9c5, 0x4515, 0x86, 0x15, 0x24, 0x35, 0x77, 0xc8, 0x35, 0xb };

// {6CD56B3D-C9E6-4FFD-B717-FD0FF254FF37}
const IID IID_ISum = { 0x6cd56b3d, 0xc9e6, 0x4ffd, 0xb7, 0x17, 0xfd, 0xf, 0xf2, 0x54, 0xff, 0x37 };

// {204F806F-A1AF-44FB-8E7D-B2ADFD420FA1}
const IID IID_ISubtract = { 0x204f806f, 0xa1af, 0x44fb, 0x8e, 0x7d, 0xb2, 0xad, 0xfd, 0x42, 0xf, 0xa1 };



