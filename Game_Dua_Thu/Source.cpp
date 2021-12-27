#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define SUTU_THOIGIANBATDAU 9
#define THO_THOIGIANBATDAU 8
#define RUA_THOIGIANBATDAU 7

#define SUTU_QUANGDUONGCHAY 210
#define THO_QUANGDUONGCHAY 210
#define RUA_QUANGDUONGCHAY 135

struct ConVat
{
	string MaSo;
	int TocDo, TrangBi;
};
typedef struct ConVat CONVAT;

void NhapConVat(ifstream& FileIn, CONVAT& cv) {
	FileIn >> cv.MaSo >> cv.TocDo >> cv.TrangBi;
}

void XuatConVat(ofstream& FileOut, CONVAT cv) {
	FileOut << cv.MaSo << " " << cv.TocDo << " " << cv.TrangBi;
}

void NhapDanhSach(ifstream& FileIn, vector<CONVAT>& DanhSach) {
	int n;
	FileIn >> n;

	for (int i = 1; i <= n; i++)
	{
		CONVAT cv;
		NhapConVat(FileIn, cv);
		DanhSach.push_back(cv);
	}
}

void XuatDanhSach(ofstream& FileOut, vector<CONVAT> DanhSach) {
	int n = DanhSach.size();

	for (int i = 0; i < n; i++)
	{
		XuatConVat(FileOut, DanhSach[i]);
		FileOut << endl;
	}
}

int TimVanTocThucSu(CONVAT cv) {
	/*if (cv.MaSo[0] == 'L')
	{
		if (cv.TrangBi == 1)
		{
			return cv.TocDo * 2;
		}
	}
	else if (cv.MaSo[0] == 'R')
	{
		if (cv.TrangBi == 1)
		{
			return cv.TocDo + 30;
		}
	}
	else if (cv.MaSo[0] == 'T')
	{
		if (cv.TrangBi == 1)
		{
			return cv.TocDo * 5;
		}
	}*/
	switch (cv.MaSo[0])
	{
	case 'L': return (cv.TrangBi == 1) ? cv.TocDo * 2 : cv.TocDo; break;
	case 'R': return (cv.TrangBi == 1) ? cv.TocDo + 30 : cv.TocDo; break;
	case 'T': return (cv.TrangBi == 1) ? cv.TocDo * 5 : cv.TocDo; break;
	}
}

double TimThoiGianDiHetQuangDuong(CONVAT cv) {
	int tocdothucsu = TimVanTocThucSu(cv);

	switch (cv.MaSo[0])
	{
	case 'L': return (double)SUTU_QUANGDUONGCHAY / tocdothucsu; break;
	case 'R': return (double)THO_QUANGDUONGCHAY / tocdothucsu; break;
	case 'T': return (double)RUA_QUANGDUONGCHAY / tocdothucsu; break;
	}
}

double TimThoiGianVeDich(CONVAT cv) {
	double ThoiGianChay = TimThoiGianDiHetQuangDuong(cv);

	switch (cv.MaSo[0])
	{
	case 'L': return (double)SUTU_THOIGIANBATDAU + ThoiGianChay; break;
	case 'R': return (double)THO_THOIGIANBATDAU + ThoiGianChay; break;
	case 'T': return (double)RUA_THOIGIANBATDAU + ThoiGianChay; break;
	}
}

void HoanVi(CONVAT& a, CONVAT& b) {
	CONVAT Temp = a;
	a = b;
	b = Temp;
}

void SapXepDanhSach(vector<CONVAT>& DanhSach) {
	int n = DanhSach.size();
	for (int i = 0; i < n - 1; i++)
	{
		double ThoiGianVeDich_1 = TimThoiGianVeDich(DanhSach[i]);
		for (int j = i + 1; j < n; j++)
		{
			double ThoiGianVeDich_2 = TimThoiGianVeDich(DanhSach[j]);
			if (ThoiGianVeDich_1 > ThoiGianVeDich_2)
			{
				HoanVi(DanhSach[i], DanhSach[j]);
			}
		}
	}
}

int main() {
	ifstream FileIn("INPUT.TXT");

	if (!FileIn)
	{
		cout << "\nKhong tim thay tap tin!!!";
		system("pause");
		return 0;
	}

	vector<CONVAT> DanhSach;

	NhapDanhSach(FileIn, DanhSach);

	FileIn.close();

	ofstream FileOut("OUTPUT.TXT");

	SapXepDanhSach(DanhSach);

	int n = DanhSach.size();
	int dem = 0;
	FileOut << " " << endl;
	for (int i = 0; i < n; i++)
	{
		if (TimThoiGianVeDich(DanhSach[i]) <= 12)
		{
			FileOut << i + 1 << ". ";
			XuatConVat(FileOut, DanhSach[i]);
			FileOut << " => " << TimThoiGianVeDich(DanhSach[i]) <<  endl;
			dem++;
		}
	}

	FileOut.seekp(0, SEEK_SET);
	FileOut << dem << endl;

	FileOut.close();

	system("pause");
	return 0;
}