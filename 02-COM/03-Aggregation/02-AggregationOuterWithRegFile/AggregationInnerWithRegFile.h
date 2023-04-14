#pragma once
class IMultiplication :public IUnknown
{
public:virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;

};

class IDivision :public IUnknown
{
public:virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;

};

// {EAF1F3F8-40BD-49CE-B2CD-3D6FAAC20376}
const CLSID CLSID_MultiplicationDivision = { 0xeaf1f3f8, 0x40bd, 0x49ce, 0xb2, 0xcd, 0x3d, 0x6f, 0xaa, 0xc2, 0x3, 0x76 };


// {8D6F2ACF-E1DD-4114-9146-B9DE6C04DFFF}
const IID IID_IMultiplication = { 0x8d6f2acf, 0xe1dd, 0x4114, 0x91, 0x46, 0xb9, 0xde, 0x6c, 0x4, 0xdf, 0xff };


// {4DB53B87-C43F-4DDF-A28A-DB0A303CCAEA}
const IID IID_IDivision = { 0x4db53b87, 0xc43f, 0x4ddf, 0xa2, 0x8a, 0xdb, 0xa, 0x30, 0x3c, 0xca, 0xea };




