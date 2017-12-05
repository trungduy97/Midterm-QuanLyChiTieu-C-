#pragma once
#include<iostream>
#include <string>
using namespace std;


//
class ChiTieu
{
private:
	wstring buffLoai;
	wstring buffNoiDung;
	long lSoTien;
public:
	ChiTieu();
	ChiTieu(wstring loai, wstring noiDung, long soTien);

	//set
	void setLoai(wstring loai);
	void setNoiDung(wstring noiDung);
	void setSoTien(long soTien);
	//get
	wstring getLoai();
	wstring getNoiDung();
	long getSoTien();
};

