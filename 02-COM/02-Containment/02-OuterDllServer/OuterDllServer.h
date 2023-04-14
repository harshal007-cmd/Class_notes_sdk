#pragma once
class ISum :public IUnknown
{
public:virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;

};

class ISubtract :public IUnknown
{
public:virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;

};

// {1D772CE0-A2A5-43F2-B493-A10CE491C826}
const CLSID CLSID_SumSubtract = { 0x1d772ce0, 0xa2a5, 0x43f2, 0xb4, 0x93, 0xa1, 0xc, 0xe4, 0x91, 0xc8, 0x26 };


// {6CD56B3D-C9E6-4FFD-B717-FD0FF254FF37}
const IID IID_ISum = { 0x6cd56b3d, 0xc9e6, 0x4ffd, 0xb7, 0x17, 0xfd, 0xf, 0xf2, 0x54, 0xff, 0x37 };

// {204F806F-A1AF-44FB-8E7D-B2ADFD420FA1}
const IID IID_ISubtract = { 0x204f806f, 0xa1af, 0x44fb, 0x8e, 0x7d, 0xb2, 0xad, 0xfd, 0x42, 0xf, 0xa1 };



