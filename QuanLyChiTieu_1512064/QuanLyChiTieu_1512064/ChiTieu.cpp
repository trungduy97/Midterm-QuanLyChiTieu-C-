#include "stdafx.h"
#include "ChiTieu.h"


ChiTieu::ChiTieu()
{
	buffLoai.clear();
	buffNoiDung.clear();
	lSoTien = 0;
}

ChiTieu::ChiTieu(wstring loai, wstring noiDung, long soTien)
{
	buffLoai = loai;
	buffNoiDung = noiDung;
	this->lSoTien = soTien;
}


//set
void ChiTieu:: setLoai(wstring loai)
{
	buffLoai = loai;
}


void ChiTieu::setSoTien(long soTien)
{
	this->lSoTien = soTien;
}


void ChiTieu::setNoiDung(wstring noiDung)
{
	buffNoiDung = noiDung;
}


//get
wstring ChiTieu::getLoai()
{
	return this->buffLoai;
}

wstring ChiTieu::getNoiDung()
{
	return this->buffNoiDung;
}

long ChiTieu::getSoTien()
{
	return this->lSoTien;
}