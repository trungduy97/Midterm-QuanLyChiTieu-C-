#include "stdafx.h"
#include "DSChiTieu.h"

wstring ComboBoxLoaiChiTieu[6] = { _T("Ăn uống"), _T("Di chuyển"), _T("Nhà cửa"),_T("Xe cộ"), _T("Nhu yếu phẩm"), _T("Dịch vụ") };

DSChiTieu::DSChiTieu()
{
	count = 0;
}

void DSChiTieu::setCountItem(int count)
{
	this->count = count;
}

void DSChiTieu::setDSChiTieu(string path)
{
	wfstream wf;
	wf.open(path, ios::out);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	wf.imbue(loc);
	int count = 0;
	while (count < this->getCountItem() - 1)
	{
		ChiTieu chiTieu = getChiTieu(count);
		wf << chiTieu.getLoai() << L"," << chiTieu.getNoiDung() << L"," << chiTieu.getSoTien();
		wf << endl;
		count++;
	}
	if (count == this->getCountItem() - 1)
	{
		ChiTieu chiTieu = getChiTieu(count);
		wf << chiTieu.getLoai() << L"," << chiTieu.getNoiDung() << L"," << chiTieu.getSoTien();
	}

	wf.close();
}

int DSChiTieu::getCountItem()
{
	return this->count;
}

ChiTieu DSChiTieu::getChiTieu(int pos)
{
	return DanhSachChiTieu[pos];
}

void DSChiTieu::getDSChiTieu(string path)
{
	wfstream fin;
	fin.open(path, ios::in);
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	fin.imbue(loc);

	while (!fin.eof())
	{
		fflush(stdin);
		ChiTieu chiTieu;
		wstring data;
		wstring temp;
		getline(fin, data);
		if (data == L"")
			continue;
		int n = data.find_first_of(',');
		temp = data.substr(0, n);
		chiTieu.setLoai(temp);
		int m = data.find_last_of(',');
		temp = data.substr(n + 1, m - n - 1);
		chiTieu.setNoiDung(temp);
		temp = data.substr(m + 1);
		long soTien = _wtol(temp.c_str());
		chiTieu.setSoTien(soTien);

		them(chiTieu);
	}
	fin.close();
}




void DSChiTieu::them(ChiTieu chiTieu)
{
	DanhSachChiTieu.push_back(chiTieu);
	count++;
}

long DSChiTieu::getTongTien()
{
	long tongtien = 0;
	for(int i=0;i<this->count;i++)
	{
		tongtien += DanhSachChiTieu[i].getSoTien();
	}
	return tongtien;

}

float DSChiTieu::getTiLe(int n)
{
	long tongTien = 0;
	for(int i=0;i<this->count;i++)
	{
		if(DanhSachChiTieu[i].getLoai().compare(ComboBoxLoaiChiTieu[n]) == 0)
		{
			tongTien += DanhSachChiTieu[i].getSoTien();
		}
	}
	return 1.0*tongTien /getTongTien();
}


