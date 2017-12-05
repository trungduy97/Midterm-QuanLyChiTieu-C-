// QuanLyChiTieu_1512064.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QuanLyChiTieu_1512064.h"
#include "DSChiTieu.h"
#include <string>
#include <Shellapi.h>
#include <windowsX.h>
#include <winuser.h>
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
using namespace std;

#define MAX_LOADSTRING 100

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);

//*****************************************************
void createCol();
void loadListView();
void createNote(HWND hWnd, HDC hdc, PAINTSTRUCT ps); //Tạo ghi chú
void chartPaint(HWND hWnd);
void loadRate();
bool KiemTra(WCHAR* buffer,int length);

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_QUANLYCHITIEU1512064, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUANLYCHITIEU1512064));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(236, 236, 236));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_QUANLYCHITIEU1512064);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
      300, 100, 1030, 560, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

HWND lvDanhSachChi;
HWND comboBoxLoaiChiTieu;
HWND txtNoiDungChi, txtSoTien, txtTongTien;
DSChiTieu DanhSachChiTieu;
////
HWND AnUong, DiChuyen, XeCo, NhaCua, NhuYeuPham, DichVu;


BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	RECT main; 
	GetWindowRect(hWnd, &main);
	InitCommonControls();
	
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);


	HWND title = CreateWindowEx(0,L"BUTTON",L"QUẢN LÝ CHI TIÊU CÁ NHÂN", WS_CHILD | WS_VISIBLE | SS_LEFT,400, 20, 160, 20,hWnd, NULL,hInst,NULL);
	SendMessage(title, WM_SETFONT, WPARAM(hFont), TRUE);

	
	
	HWND boxNhap = CreateWindowEx(0,L"BUTTON",L"THÊM VÀO DANH SÁCH", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,50, 60, 350, 220,hWnd, NULL,hInst,NULL);
	SendMessage(boxNhap, WM_SETFONT, WPARAM(hFont), TRUE);

	HWND hwnd = CreateWindowEx(0, L"STATIC", L"Loại chi tiêu:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 50, 100, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	//Tao combobox va cac thuoc tinh
	comboBoxLoaiChiTieu = CreateWindowEx(0, WC_COMBOBOX, TEXT(""),CBS_DROPDOWNLIST |  WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 150, 50, 150, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(comboBoxLoaiChiTieu, WM_SETFONT, WPARAM(hFont), TRUE);
	const TCHAR* ComboBoxLoaiChiTieu[6] = { _T("Ăn uống"), _T("Di chuyển"), _T("Nhà cửa"),_T("Xe cộ"), _T("Nhu yếu phẩm"), _T("Dịch vụ") };
	for(int i=0;i<6;i++)
	{
		SendMessage(comboBoxLoaiChiTieu, CB_INSERTSTRING, i, (LPARAM)ComboBoxLoaiChiTieu[i]);
	}



	SendMessage(comboBoxLoaiChiTieu, CB_SETCURSEL, 0, 0);
	hwnd = CreateWindowEx(0, L"STATIC", L"Nội dung chi:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 90, 100, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	txtNoiDungChi = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 150, 90, 150, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(txtNoiDungChi, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Số tiền:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 130, 100, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	txtSoTien = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER| SS_RIGHT| WS_TABSTOP, 150, 130, 150, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(txtSoTien, WM_SETFONT, WPARAM(hFont), TRUE);

	HWND boxList = CreateWindowEx(0,L"BUTTON",L"DANH SÁCH CÁC KHOẢN CHI TIÊU", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,450, 60, 515, 220,hWnd, NULL,hInst,NULL);
	SendMessage(boxList, WM_SETFONT, WPARAM(hFont), TRUE);
	//tao listview
	lvDanhSachChi = CreateWindowEx(0, WC_LISTVIEW, L"Danh sách chi", WS_CHILD | WS_VISIBLE | WS_VSCROLL,10,20, 500, 175,boxList, NULL,hInst,NULL);
	SendMessage(lvDanhSachChi, WM_SETFONT, WPARAM(hFont), TRUE);
	
	SetWindowLong(lvDanhSachChi, GWL_STYLE, GetWindowLong(lvDanhSachChi, GWL_STYLE) | LVS_REPORT);
	createCol();

	hwnd = CreateWindowEx(0,L"BUTTON",L"THÊM", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,173, 230, 120, 30,hWnd, (HMENU)IDC_BTNTHEM,hInst,NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	HWND boxDraw = CreateWindowEx(0,L"BUTTON",L"THỐNG KÊ CÁC LOẠI CHI TIÊU (%)", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,50, 290, 915, 190,hWnd, NULL,hInst,NULL);
	SendMessage(boxDraw, WM_SETFONT, WPARAM(hFont), TRUE);
	
	hwnd = CreateWindowEx(0, L"STATIC", L"<<>> Tổng tiền (VNĐ)", WS_CHILD | WS_VISIBLE | SS_LEFT, 10, 53, 130, 20, boxDraw, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txtTongTien = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT, 120, 50, 100, 20, boxDraw, NULL, hInst, NULL);
	SendMessage(txtTongTien, WM_SETFONT, WPARAM(hFont), TRUE);

	

	/////////////////
	AnUong = CreateWindowEx(0, L"STATIC", L"Ăn uống", WS_CHILD | WS_VISIBLE | SS_LEFT, 380, 303, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(AnUong, WM_SETFONT, WPARAM(hFont), TRUE);

	DiChuyen = CreateWindowEx(0, L"STATIC", L"Di chuyển", WS_CHILD | WS_VISIBLE | SS_LEFT, 580, 303, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(DiChuyen, WM_SETFONT, WPARAM(hFont), TRUE);

	NhaCua = CreateWindowEx(0, L"STATIC", L"Nhà cửa", WS_CHILD | WS_VISIBLE | SS_LEFT, 780, 303, 100, 20,  hWnd, NULL, hInst, NULL);
	SendMessage(NhaCua, WM_SETFONT, WPARAM(hFont), TRUE);

	XeCo = CreateWindowEx(0, L"STATIC", L"Xe cộ", WS_CHILD | WS_VISIBLE | SS_LEFT, 380, 353, 100, 20,  hWnd, NULL, hInst, NULL);
	SendMessage(XeCo, WM_SETFONT, WPARAM(hFont), TRUE);

	NhuYeuPham = CreateWindowEx(0, L"STATIC", L"Nhu yếu phẩm", WS_CHILD | WS_VISIBLE | SS_LEFT, 580, 353, 150, 20, hWnd, NULL, hInst, NULL);
	SendMessage(NhuYeuPham, WM_SETFONT, WPARAM(hFont), TRUE);

	DichVu = CreateWindowEx(0, L"STATIC", L"Dịch vụ", WS_CHILD | WS_VISIBLE | SS_LEFT, 780, 353, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(DichVu, WM_SETFONT, WPARAM(hFont), TRUE);

	DanhSachChiTieu.getDSChiTieu("DSChiTieu.txt");
	loadListView();
	loadRate();
	return true;
}


void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	int stSoTien = 0;
	int stNoiDung = 0;
	int stLoai = 0;

	WCHAR* buffNoiDung =NULL;
	WCHAR* buffLoai =NULL;
	WCHAR* buffSoTien = NULL;
	WCHAR* buffTongTien = NULL;

	wstring NoiDung;
	wstring loai;
	long valSoTien = 0;

	ChiTieu chiTieu;

	switch(id)
	{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case IDC_BTNTHEM:
			stSoTien = GetWindowTextLength(txtSoTien);
			buffSoTien = new WCHAR[stSoTien+1];
			GetWindowText(txtSoTien, buffSoTien, stSoTien+1);
			valSoTien = _wtol(buffSoTien);

			if(!KiemTra(buffSoTien,stSoTien) || valSoTien <= 0|| valSoTien==NULL)
			{
				MessageBox(hWnd,L"Số tiền nhập không hợp lệ",L"Lỗi",MB_OK | MB_ICONERROR);
				return;
			}

			stNoiDung = GetWindowTextLength(txtNoiDungChi);
			buffNoiDung = new WCHAR[stNoiDung+1];
			GetWindowText(txtNoiDungChi, buffNoiDung, stNoiDung+1);
			
			if(stNoiDung == 0)
			{
				int i = MessageBox(hWnd,L"Hãy nhập nội dung chi tiêu",L"Thông báo",MB_YESNO | MB_ICONQUESTION);
				if(i == IDNO)
				{
					return;
				}
			}


			stLoai = GetWindowTextLength(comboBoxLoaiChiTieu);
			buffLoai = new WCHAR[stLoai+1];
			GetWindowText(comboBoxLoaiChiTieu,buffLoai,stLoai+1);


			LV_ITEM lv;
			lv.mask = LVIF_TEXT;
			lv.iItem = DanhSachChiTieu.getCountItem()+1;
			lv.iSubItem = 0;
			lv.pszText = buffLoai;
			ListView_InsertItem(lvDanhSachChi, &lv);
			ListView_SetItemText(lvDanhSachChi, DanhSachChiTieu.getCountItem(), 1, buffNoiDung);
			ListView_SetItemText(lvDanhSachChi, DanhSachChiTieu.getCountItem(), 2, buffSoTien);
			

			loai = wstring(buffLoai);
			NoiDung = wstring(buffNoiDung);
			chiTieu = ChiTieu(loai,NoiDung,valSoTien);

			DanhSachChiTieu.them(chiTieu);
			buffTongTien = new WCHAR[20];
			swprintf(buffTongTien,20,L"%ld",DanhSachChiTieu.getTongTien());
			SetWindowText(txtTongTien,buffTongTien);
			chartPaint(hWnd);
			loadRate();

			break;
	}
	if(!buffLoai)
		delete[]buffLoai;
	if(!buffNoiDung)
		delete[]buffNoiDung;
	if(!buffSoTien)
		delete[]buffSoTien;
	return;
}

bool KiemTra(WCHAR* buffer, int length)
{
	if (buffer == NULL && length == 0)
		return true;
	for (int i = 0; i<length; i++)
	{
		if (buffer[i] == '\0')
			break;
		if (buffer[i] < '0' || buffer[i] > '9')
		{
			return false;
		}

	}
	return true;
}

void loadListView()
{
	LV_ITEM lv;
	lv.mask =LVIF_TEXT;
	lv.iItem = DanhSachChiTieu.getCountItem();
	WCHAR* buffSoTien = new WCHAR[20];
	WCHAR* buffNoiDung = new WCHAR[20];
	WCHAR* buffLoai = new WCHAR[20];
	for(int i=0;i<DanhSachChiTieu.getCountItem();i++)
	{
		ChiTieu chiTieu = DanhSachChiTieu.getChiTieu(i);
		lv.iSubItem = 0;
		chiTieu.getNoiDung().c_str();
		swprintf(buffLoai,20,L"%s",chiTieu.getLoai().c_str());
		lv.pszText = buffLoai;
		ListView_InsertItem(lvDanhSachChi, &lv);
		swprintf(buffNoiDung,20,L"%s",chiTieu.getNoiDung().c_str());
		ListView_SetItemText(lvDanhSachChi, i, 1,buffNoiDung);
		swprintf(buffSoTien,20,L"%ld",chiTieu.getSoTien());
		ListView_SetItemText(lvDanhSachChi, i, 2, buffSoTien);
	}

	swprintf(buffSoTien,20,L"%ld",DanhSachChiTieu.getTongTien());
	SetWindowText(txtTongTien,buffSoTien);
	if(!buffLoai)
		delete[]buffLoai;
	if(!buffNoiDung)
		delete[]buffNoiDung;
	if(!buffSoTien)
		delete[]buffSoTien;

}

void OnPaint(HWND hWnd)
{
	int length = 890;
	int lengthDiChuyen = length * DanhSachChiTieu.getTiLe(1);
	int lengthNhaCua = length * DanhSachChiTieu.getTiLe(2);
	int lengthXeCo = length * DanhSachChiTieu.getTiLe(3);
	int lengthNhuYeuPham = length * DanhSachChiTieu.getTiLe(4);
	int lengthDichVu = length * DanhSachChiTieu.getTiLe(5);
	int lengthAnUong = length - lengthDiChuyen - lengthDichVu - lengthNhaCua - lengthNhuYeuPham - lengthXeCo;
	HDC hdc;

	int nLength = 60;
	int pLength = 60;

	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);

	nLength+=lengthAnUong;
	HRGN anUong = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbAnUong = CreateSolidBrush(RGB(56, 21, 253));
	FillRgn(hdc,anUong,hbAnUong);

	

	pLength = nLength;
	nLength += lengthNhaCua;
	HRGN nhaCua = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbNhaCua = CreateSolidBrush(RGB(240,255, 100));	
	FillRgn(hdc,nhaCua,hbNhaCua);

	pLength = nLength;
	nLength += lengthXeCo;
	HRGN xeCo = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbXeCo = CreateSolidBrush(RGB(85,250, 60));	
	FillRgn(hdc,xeCo,hbXeCo);

	pLength = nLength;
	nLength += lengthNhuYeuPham;
	HRGN nhuYeuPham = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbNhuYeuPham = CreateSolidBrush(RGB(0, 0, 0));	
	FillRgn(hdc,nhuYeuPham,hbNhuYeuPham);

	pLength = nLength;
	nLength += lengthDiChuyen;
	HRGN diChuyen = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbDiChuyen = CreateSolidBrush(RGB(242, 34, 4));
	FillRgn(hdc, diChuyen, hbDiChuyen);

	pLength = nLength;
	nLength += lengthDichVu;
	HRGN dichVu = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbDichVu = CreateSolidBrush(RGB(247, 0, 247));
	FillRgn(hdc,dichVu,hbDichVu);

	createNote(hWnd,hdc,ps);
	EndPaint(hWnd, &ps);
	return;
}
#define MAX_CHAR 30
void loadRate()
{
	WCHAR* buffer = new WCHAR[MAX_CHAR];
	float tiLe = 100;
	float tiLeDiChuyen = 100*DanhSachChiTieu.getTiLe(1);
	float tiLeNhaCua = 100*DanhSachChiTieu.getTiLe(2);
	float tiLeXeCo = 100*DanhSachChiTieu.getTiLe(3);
	float tiLeNhuYeuPham = 100*DanhSachChiTieu.getTiLe(4);
	float tiLeDichVu = 100*DanhSachChiTieu.getTiLe(5);
	float tiLeAnUong = tiLe - tiLeDiChuyen - tiLeDichVu - tiLeNhaCua - tiLeNhuYeuPham - tiLeXeCo;
	swprintf(buffer,MAX_CHAR,L"Ăn uống: %.2f%%",tiLeAnUong);
	SetWindowText(AnUong,buffer);

	swprintf(buffer,MAX_CHAR,L"Di chuyển: %.2f%%",tiLeDiChuyen);
	SetWindowText(DiChuyen,buffer);

	swprintf(buffer,MAX_CHAR,L"Nhà cửa: %.2f%%",tiLeNhaCua);
	SetWindowText(NhaCua,buffer);

	swprintf(buffer,MAX_CHAR,L"Xe cộ: %.2f%%",tiLeXeCo);
	SetWindowText(XeCo,buffer);

	swprintf(buffer,MAX_CHAR,L"Nhu yếu phẩm: %.2f%%",tiLeNhuYeuPham);
	SetWindowText(NhuYeuPham,buffer);

	swprintf(buffer,MAX_CHAR,L"Dịch vụ: %.2f%%",tiLeDichVu);
	SetWindowText(DichVu,buffer);
}

void createNote(HWND hWnd, HDC hdc, PAINTSTRUCT ps)
{

	HRGN anUong = CreateRectRgn(350, 300, 370, 320);
	HBRUSH hbrushAnUong = CreateSolidBrush(RGB(56, 21, 253));
	FillRgn(hdc, anUong, hbrushAnUong);

	HRGN diChuyen = CreateRectRgn(550, 300, 570, 320);
	HBRUSH hbrushDiChuyen = CreateSolidBrush(RGB(242, 34, 4));
	FillRgn(hdc, diChuyen, hbrushDiChuyen);

	HRGN nhaCua = CreateRectRgn(750, 300, 770, 320);
	HBRUSH hbrushnhaCua = CreateSolidBrush(RGB(240, 255, 100));
	FillRgn(hdc, nhaCua, hbrushnhaCua);

	HRGN xeCo = CreateRectRgn(350, 350, 370, 370);
	HBRUSH hbrushxeCo = CreateSolidBrush(RGB(85, 250, 60));
	FillRgn(hdc, xeCo, hbrushxeCo);

	HRGN nhuYeuPham = CreateRectRgn(550, 350, 570, 370);
	HBRUSH hbrushnhuYeuPham = CreateSolidBrush(RGB(0, 0, 0));
	FillRgn(hdc, nhuYeuPham, hbrushnhuYeuPham);

	HRGN dichVu = CreateRectRgn(750, 350, 770, 370);
	HBRUSH hbrushdichVu = CreateSolidBrush(RGB(247, 0, 247));
	FillRgn(hdc, dichVu, hbrushdichVu);


}

void chartPaint(HWND hWnd)
{
	int length = 890;
	int lDiChuyen = length * DanhSachChiTieu.getTiLe(1);
	int lNhaCua = length * DanhSachChiTieu.getTiLe(2);
	int lXeCo = length * DanhSachChiTieu.getTiLe(3);
	int lNhuYeuPham = length * DanhSachChiTieu.getTiLe(4);
	int lDichVu = length * DanhSachChiTieu.getTiLe(5);
	int lAnUong = length - lDiChuyen - lDichVu - lNhaCua - lNhuYeuPham - lXeCo;
	HDC hdc;

	int nLength = 60;
	int pLength = 60;

	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);

	nLength+=lAnUong;
	HRGN anUong = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbrushAnUong = CreateSolidBrush(RGB(56, 21, 253));
	FillRgn(hdc,anUong,hbrushAnUong);

	

	pLength = nLength;
	nLength += lNhaCua;
	HRGN nhaCua = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbrushnhaCua = CreateSolidBrush(RGB(240,255, 100));	
	FillRgn(hdc,nhaCua,hbrushnhaCua);

	pLength = nLength;
	nLength += lXeCo;
	HRGN xeCo = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbrushxeCo = CreateSolidBrush(RGB(85,250, 60));	
	FillRgn(hdc,xeCo,hbrushxeCo);

	pLength = nLength;
	nLength += lNhuYeuPham;
	HRGN nhuYeuPham = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbrushnhuYeuPham = CreateSolidBrush(RGB(0, 0, 0));	
	FillRgn(hdc,nhuYeuPham,hbrushnhuYeuPham);

	pLength = nLength;
	nLength += lDiChuyen;
	HRGN diChuyen = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbrushDiChuyen = CreateSolidBrush(RGB(242, 34, 4));
	FillRgn(hdc, diChuyen, hbrushDiChuyen);

	pLength = nLength;
	nLength += lDichVu;
	HRGN dichVu = CreateRectRgn(pLength, 400, nLength, 450);
	HBRUSH hbrushdichVu = CreateSolidBrush(RGB(247, 0, 247));
	FillRgn(hdc,dichVu,hbrushdichVu);

	InvalidateRgn(hWnd,anUong,TRUE);
	InvalidateRgn(hWnd,diChuyen,TRUE);
	InvalidateRgn(hWnd,dichVu,TRUE);
	InvalidateRgn(hWnd,xeCo,TRUE);
	InvalidateRgn(hWnd,nhuYeuPham,TRUE);
	InvalidateRgn(hWnd,nhaCua,TRUE);

	createNote(hWnd,hdc,ps);
	EndPaint(hWnd, &ps);
	return;
}


void OnDestroy(HWND hwnd)
{
	DanhSachChiTieu.setDSChiTieu("DSChiTieu.txt");
	PostQuitMessage(0);
	return;
}

void createCol()
{
	LVCOLUMN lvCol;

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt=LVCFMT_LEFT;
	lvCol.cx = 200;
	lvCol.pszText = _T("Nội dung");
	ListView_InsertColumn(lvDanhSachChi, 1, &lvCol);
	

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 150;
	lvCol.pszText = _T("Loại chi tiêu");
	ListView_InsertColumn(lvDanhSachChi, 0, &lvCol);


	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 130;
	lvCol.pszText = _T("Số tiền (VNĐ)");
	ListView_InsertColumn(lvDanhSachChi, 2, &lvCol);
}

