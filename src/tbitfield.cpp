// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include <vector>
#include "tbitfield.h"

TBitField::TBitField(int len) :BitLen(len), MemLen(((len - 1) / (sizeof(TELEM)*8)) + 1)
{
	if (len < 0)
		throw("Len is incorrect");
	else
		pMem = new TELEM[MemLen]{ 0 };
}

TBitField::TBitField(const TBitField& bf) :BitLen(bf.BitLen), MemLen(bf.MemLen)   // конструктор копирования
{
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]  pMem;
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen)
		throw("index is incorrect");
	else
		return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)
		throw(" index is incorrect");
	else
		return 1 << (n&31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) || (n < BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else
		throw("num is incorrect");
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) || (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	else
		throw("num is incorrect");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n <= -1) || (n >= BitLen))
		throw("index is incorrect");
	else
		return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf)
	{
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 0;
	return 1;
}
int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 1;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] == bf.pMem[i])
				return 0;
	return 1;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len;
	(bf.BitLen <= BitLen) ? (len = BitLen) : (len = bf.BitLen);
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen;i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int len;
	(bf.BitLen <= BitLen) ? (len = BitLen) : (len = bf.BitLen);
	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < tmp.MemLen - 1; i++)
		tmp.pMem[i] = ~pMem[i];
	for (int i = (tmp.MemLen - 1) * sizeof(TELEM) * 8; i < tmp.BitLen; i++)
	{
		if (GetBit(i))
			tmp.ClrBit(i);
		else
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	string tmp;
	istr >> tmp;
	if (tmp.size() > bf.GetLength())
		throw "Incorrect length";
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (tmp[i] == '0')
			bf.ClrBit(i);
		else if (tmp[i] == '1')
			bf.SetBit(i);
		else
			throw "Incorrect input";
	}
	return istr;
}


ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
			ostr << bf.GetBit(i);
	}
	return ostr;
}
