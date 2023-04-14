#pragma once
class IMultiplication :public IUnknown
{
public:virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;

};

class IDivision :public IUnknown
{
public:virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;

};

// {C7620579-88DB-42A6-B9F0-5691F6590214}
const CLSID CLSID_MultiplicationDivision = { 0xc7620579, 0x88db, 0x42a6, 0xb9, 0xf0, 0x56, 0x91, 0xf6, 0x59, 0x2, 0x14 };


// {47BA3945-97AB-415C-8310-0E4565983164}
const IID IID_IMultiplication = { 0x47ba3945, 0x97ab, 0x415c, 0x83, 0x10, 0xe, 0x45, 0x65, 0x98, 0x31, 0x64 };


// {E19A535B-8F80-4B7F-A4F7-BD90D82C0729}
const IID IID_IDivision = { 0xe19a535b, 0x8f80, 0x4b7f, 0xa4, 0xf7, 0xbd, 0x90, 0xd8, 0x2c, 0x7, 0x29 };




