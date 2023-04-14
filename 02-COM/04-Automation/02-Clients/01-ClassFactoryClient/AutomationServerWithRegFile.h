#pragma once
class IMyMath :public IDispatch
{
public:
	virtual HRESULT __stdcall SumOfTwoIntergers(int, int, int*) = 0;

public:
	virtual HRESULT __stdcall SubtractionOfTwoIntergers(int, int, int*) = 0;

};


// {EE8E1D7A-5E78-4078-89C7-8A3B0BA1D954}
const CLSID CLSID_MyMath = { 0xee8e1d7a, 0x5e78, 0x4078, 0x89, 0xc7, 0x8a, 0x3b, 0xb, 0xa1, 0xd9, 0x54 };

// {99FBF79C-4932-43E8-9CE5-44990AD760DE}
const IID IID_IMyMath = { 0x99fbf79c, 0x4932, 0x43e8, 0x9c, 0xe5, 0x44, 0x99, 0xa, 0xd7, 0x60, 0xde };


