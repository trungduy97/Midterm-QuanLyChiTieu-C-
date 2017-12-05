#pragma once
#include "ChiTieu.h"
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
using namespace std;
class DSChiTieu
{
	vector<ChiTieu> DanhSachChiTieu;
	int count;
public:
	DSChiTieu();
	void setCountItem(int count);
	void setDSChiTieu(string path);


	int getCountItem();
	void them(ChiTieu chiTieu);
	long getTongTien();
	float getTiLe(int n);
	ChiTieu getChiTieu(int pos);
	void getDSChiTieu(string path);
	
};

