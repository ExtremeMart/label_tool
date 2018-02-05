
// ImageMarkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageMark.h"
#include "ImageMarkDlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include "CvvImage.h"
#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <vector>
using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
string listpath;
string dataloc, dataloc2;
ifstream unlabeldata;
float rate_rect;
bool first_open = 1;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageMarkDlg �Ի���



CImageMarkDlg::CImageMarkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGEMARK_DIALOG, pParent)
	, labelednum(0)
	, Alldatanum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageMarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, labelednum);
	DDX_Text(pDX, IDC_EDIT1, Alldatanum);
}

BEGIN_MESSAGE_MAP(CImageMarkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CImageMarkDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CImageMarkDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CImageMarkDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK1, &CImageMarkDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CImageMarkDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CImageMarkDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CImageMarkDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CImageMarkDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK22, &CImageMarkDlg::OnBnClickedCheck22)
	ON_BN_CLICKED(IDC_CHECK23, &CImageMarkDlg::OnBnClickedCheck23)
	ON_BN_CLICKED(IDC_CHECK24, &CImageMarkDlg::OnBnClickedCheck24)
	ON_BN_CLICKED(IDC_CHECK25, &CImageMarkDlg::OnBnClickedCheck25)
	ON_BN_CLICKED(IDC_CHECK26, &CImageMarkDlg::OnBnClickedCheck26)
	ON_BN_CLICKED(IDC_CHECK27, &CImageMarkDlg::OnBnClickedCheck27)
	ON_BN_CLICKED(IDC_CHECK28, &CImageMarkDlg::OnBnClickedCheck28)
	ON_BN_CLICKED(IDC_CHECK29, &CImageMarkDlg::OnBnClickedCheck29)
	ON_BN_CLICKED(IDC_CHECK6, &CImageMarkDlg::OnBnClickedCheck6)
END_MESSAGE_MAP()


// CImageMarkDlg ��Ϣ�������

BOOL CImageMarkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CImageMarkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CImageMarkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CImageMarkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageMarkDlg::Delete_lastline(){

int pos = listpath.find("ImageList.txt");
dataloc2 = listpath.substr(0, pos);

ifstream label_line(dataloc2 + "all_label.txt");//�ҵ�label�ļ�
vector<string> label_lines;
string templine;
while (getline(label_line,templine))
{
	label_lines.push_back(templine);
}
label_line.close();
ofstream label_line2(dataloc2 + "all_label.txt", ios::trunc);//�ҵ�label�ļ�
for (size_t i = 0; i < label_lines.size()-1; i++)
{
	label_line2 << label_lines[i] << endl;
}
	
}

vector<string>  CImageMarkDlg::get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				string tempstr = fd.cFileName;
				int posw = tempstr.find(".txt");
				if (posw == string::npos) { names.push_back(fd.cFileName); }				
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}


/*************��ʵʱ�ɼ�ͼ����ʾ��MFC��picture�ؼ���******************/
void CImageMarkDlg::Display(cv::Mat strimg)
{

	CDC* pDC = GetDlgItem(IDC_showimg)->GetDC();//�����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(IDC_showimg)->GetClientRect(&rect);
	int y = rect.Height();
	int x = rect.Width();
	rate_rect = (float)y / x;

	int width_img = strimg.cols;
	int height_img = strimg.rows;
	float rate_img = (float)height_img / width_img;
	Mat show_image;
	int wid_tep=((float)y / height_img)*width_img;


	if (rate_img > rate_rect)//��Ƭ����
	{
		Mat desImg(height_img, ((float)x/y )* height_img, CV_8UC3, Scalar(255, 255, 255));//����һ��ȫ�׵�ͼƬ
		for (size_t i = 0; i < strimg.rows; i++)
		{
			for (size_t t = 0; t < strimg.cols; t++)
			{
				desImg.at<Vec3b>(i, t)[0]= strimg.at<Vec3b>(i, t)[0];
				desImg.at<Vec3b>(i, t)[1] = strimg.at<Vec3b>(i, t)[1];
				desImg.at<Vec3b>(i, t)[2] = strimg.at<Vec3b>(i, t)[2];
			}

		}
		resize(desImg, show_image, cv::Size(x, y), (0, 0), (0, 0), cv::INTER_LINEAR);
	}
	if (rate_img < rate_rect)//��Ƭ����
	{
		Mat desImg(((float)y / x) *width_img, width_img, CV_8UC3, Scalar(255, 255, 255));//����һ��ȫ�׵�ͼƬ
		for (size_t i = 0; i < strimg.rows; i++)
		{
			for (size_t t = 0; t < strimg.cols; t++)
			{
				desImg.at<Vec3b>(i, t)[0] = strimg.at<Vec3b>(i, t)[0];
				desImg.at<Vec3b>(i, t)[1] = strimg.at<Vec3b>(i, t)[1];
				desImg.at<Vec3b>(i, t)[2] = strimg.at<Vec3b>(i, t)[2];
			}

		}
		resize(desImg, show_image, cv::Size(x, y), (0, 0), (0, 0), cv::INTER_LINEAR);
	}

	IplImage *img = &IplImage(show_image);
	CvvImage mfcimg;
	mfcimg.CopyOf(img);// ����ͼƬ
	mfcimg.DrawToHDC(hDC, &rect);//��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
								 

}

void CImageMarkDlg::OnBnClickedOk()  //��ʼ
{
	CFileDialog dlg(
		true, _T("*.bmp;*.jpg;*.tif*.png"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image?files?All?Files?(*.*)?|*.*||"), NULL

		);
	dlg.m_ofn.lpstrTitle = _T("��LIST�б�");
	if (dlg.DoModal() == IDOK)
	{

		if (dlg.GetFileExt() != "txt" )
		{
			AfxMessageBox(_T("��ѡ��txt�б��ʽ��"), MB_OK);
			return;
		}

		CString mPath = dlg.GetPathName();
		USES_CONVERSION;
		listpath = _T(mPath);//W2A(mPath);


	}
	 unlabeldata.open(listpath);

	
	int pos = listpath.find("ImageList.txt");
	if (pos == string::npos) { MessageBox(_T("���ImageList.txt�ļ���")); exit(0); }
	dataloc2 = listpath.substr(0,pos);


	ifstream countmgnum(listpath);//�ҵ�label�ļ�
	string buffforcount;
	Alldatanum = 0;
	while (getline(countmgnum, buffforcount))
	{
		Alldatanum++;
		
	}

	//////////////
	ifstream all_label2(dataloc2 + "all_label.txt", ios::app);//�ҵ�label�ļ�
	if (first_open)
	{
		first_open = 0;
		string temp;
		int line_length = 0;
		while (getline(all_label2, temp))
		{

			cout << temp;
			line_length++;
		}
		labelednum = line_length;
		while (line_length--) {
			getline(unlabeldata, dataloc);
		}
	}
	
/////////////
	getline(unlabeldata, dataloc);

	dataloc2 = dataloc2 + dataloc;
	cv::Mat Strimg = cv::imread(dataloc2);
	
	Display(Strimg);
	
	UpdateData(false);
	//CDialogEx::OnOK();

}


void CImageMarkDlg::OnBnClickedButton1()//��һ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*try
	{

	}
	catch (const std::exception&)
	{

	}*/

	int pos = listpath.find("ImageList.txt");
	dataloc2 = listpath.substr(0, pos);

	ofstream all_label(dataloc2 + "all_label.txt", ios::app);//�ҵ�label�ļ�
	std::streampos pos_lines = unlabeldata.tellg();
	

	all_label << dataloc;



	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1))
	{
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK1));
		pBtn->SetCheck(0);
		all_label << " 0";
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK2))
	{
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK2));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK3))
	{
		all_label << " 2";
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK3));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK4))
	{
		all_label << " 3";
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK4));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK5))
	{
		all_label << " 4";
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK5));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK6))
	{
		all_label << " 5";
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK6));
		pBtn->SetCheck(0);
	}
	else
	{
		//char* p = "Please select the face type!";
		MessageBox(_T("��ѡ��ͼ�����"));
		unlabeldata.seekg(pos_lines);
		//Delete_lastline(unlabeldata);
		//throw 1.0;
		all_label << endl;
		Delete_lastline();
		return ;
		//exit(1);
	}

	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK22))
	{
		all_label << " 0" << endl;
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK22));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK23))
	{
		all_label << " 1" << endl;
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK23));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK24))
	{
		all_label << " 2" << endl;
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK24));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK25))
	{
		all_label << " 3" << endl;
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK25));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK26))
	{
		all_label << " 4" << endl;
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK26));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK27))
	{
		all_label << " 5" << endl;
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK27));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK28))
	{
		all_label << " 6" << endl;
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK28));
		pBtn->SetCheck(0);
	}
	else if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK29))
	{
		all_label << " 7" << endl;
		CButton *pBtn = (CButton*)(GetDlgItem(IDC_CHECK29));
		pBtn->SetCheck(0);
	}
	else
	{
		//char* p = "Please select the eyes type��";
		MessageBox(_T("��ѡ���װ���Σ�"));
		unlabeldata.seekg(pos_lines);
		all_label << endl;
		Delete_lastline();
		return;
	}


	getline(unlabeldata, dataloc);
	if (dataloc == "")
	{
		MessageBox(_T("����ͼƬ�ѱ����ϣ�"));
		exit(1);
	}
	dataloc2 = dataloc2 + dataloc;
	

	cv::Mat Strimg = cv::imread(dataloc2);


	Display(Strimg);
	labelednum++;
	UpdateData(false);
}


void CImageMarkDlg::OnBnClickedButton2()//�����б��ļ�
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(
		true, _T("*.bmp;*.jpg;*.tif*.png"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image?files?All?Files?(*.*)?|*.*||"), NULL

		);
	dlg.m_ofn.lpstrTitle = _T("��ͼƬ�б�");
	if (dlg.DoModal() == IDOK)
	{
		string ext = dlg.GetFileExt();
		if ((ext == "jpg")  || (ext == "png"))
		{
			
		}
		else {
			AfxMessageBox(_T("��ѡ��jpg��png�б��ʽ��"), MB_OK);
			return;
		}

		CString mPath = dlg.GetPathName();
		USES_CONVERSION;
		listpath = _T(mPath);

		int pos = listpath.find_last_of("\\");
		string alllistpath = listpath.substr(0, pos+1);

		vector <string> allimgpath=get_all_files_names_within_folder(alllistpath);
		ofstream all_label3(alllistpath +"ImageList.txt");//�ҵ�label�ļ�
		for (size_t i = 0; i < allimgpath.size(); i++)
		{
			all_label3<<allimgpath[i] << endl;
		}
	}

}


void CImageMarkDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(_T("�����¼���"));
	//CButton *pBtn1 = (CButton*)(GetDlgItem(IDC_CHECK1));
	//pBtn1->SetCheck(0);
	CButton *pBtn2 = (CButton*)(GetDlgItem(IDC_CHECK2));
	pBtn2->SetCheck(0);
	CButton *pBtn3 = (CButton*)(GetDlgItem(IDC_CHECK3));
	pBtn3->SetCheck(0);
	CButton *pBtn4 = (CButton*)(GetDlgItem(IDC_CHECK4));
	pBtn4->SetCheck(0);
	CButton *pBtn5 = (CButton*)(GetDlgItem(IDC_CHECK5));
	pBtn5->SetCheck(0);
	CButton *pBtn6 = (CButton*)(GetDlgItem(IDC_CHECK6));
	pBtn6->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck2()
{
	CButton *pBtn1 = (CButton*)(GetDlgItem(IDC_CHECK1));
	pBtn1->SetCheck(0);
	//CButton *pBtn2 = (CButton*)(GetDlgItem(IDC_CHECK2));
	//pBtn2->SetCheck(0);
	CButton *pBtn3 = (CButton*)(GetDlgItem(IDC_CHECK3));
	pBtn3->SetCheck(0);
	CButton *pBtn4 = (CButton*)(GetDlgItem(IDC_CHECK4));
	pBtn4->SetCheck(0);
	CButton *pBtn5 = (CButton*)(GetDlgItem(IDC_CHECK5));
	pBtn5->SetCheck(0);
	CButton *pBtn6 = (CButton*)(GetDlgItem(IDC_CHECK6));
	pBtn6->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck3()
{
	CButton *pBtn1 = (CButton*)(GetDlgItem(IDC_CHECK1));
	pBtn1->SetCheck(0);
	CButton *pBtn2 = (CButton*)(GetDlgItem(IDC_CHECK2));
	pBtn2->SetCheck(0);
	//CButton *pBtn3 = (CButton*)(GetDlgItem(IDC_CHECK3));
	//pBtn3->SetCheck(0);
	CButton *pBtn4 = (CButton*)(GetDlgItem(IDC_CHECK4));
	pBtn4->SetCheck(0);
	CButton *pBtn5 = (CButton*)(GetDlgItem(IDC_CHECK5));
	pBtn5->SetCheck(0);
	CButton *pBtn6 = (CButton*)(GetDlgItem(IDC_CHECK6));
	pBtn6->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck4()
{
	CButton *pBtn1 = (CButton*)(GetDlgItem(IDC_CHECK1));
	pBtn1->SetCheck(0);
	CButton *pBtn2 = (CButton*)(GetDlgItem(IDC_CHECK2));
	pBtn2->SetCheck(0);
	CButton *pBtn3 = (CButton*)(GetDlgItem(IDC_CHECK3));
	pBtn3->SetCheck(0);
	//CButton *pBtn4 = (CButton*)(GetDlgItem(IDC_CHECK4));
	//pBtn4->SetCheck(0);
	CButton *pBtn5 = (CButton*)(GetDlgItem(IDC_CHECK5));
	pBtn5->SetCheck(0);
	CButton *pBtn6 = (CButton*)(GetDlgItem(IDC_CHECK6));
	pBtn6->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck5()
{
	CButton *pBtn1 = (CButton*)(GetDlgItem(IDC_CHECK1));
	pBtn1->SetCheck(0);
	CButton *pBtn2 = (CButton*)(GetDlgItem(IDC_CHECK2));
	pBtn2->SetCheck(0);
	CButton *pBtn3 = (CButton*)(GetDlgItem(IDC_CHECK3));
	pBtn3->SetCheck(0);
	CButton *pBtn4 = (CButton*)(GetDlgItem(IDC_CHECK4));
	pBtn4->SetCheck(0);
	//CButton *pBtn5 = (CButton*)(GetDlgItem(IDC_CHECK5));
	//pBtn5->SetCheck(0);
	CButton *pBtn6 = (CButton*)(GetDlgItem(IDC_CHECK6));
	pBtn6->SetCheck(0);
}

void CImageMarkDlg::OnBnClickedCheck6()
{
	CButton *pBtn1 = (CButton*)(GetDlgItem(IDC_CHECK1));
	pBtn1->SetCheck(0);
	CButton *pBtn2 = (CButton*)(GetDlgItem(IDC_CHECK2));
	pBtn2->SetCheck(0);
	CButton *pBtn3 = (CButton*)(GetDlgItem(IDC_CHECK3));
	pBtn3->SetCheck(0);
	CButton *pBtn4 = (CButton*)(GetDlgItem(IDC_CHECK4));
	pBtn4->SetCheck(0);
	CButton *pBtn5 = (CButton*)(GetDlgItem(IDC_CHECK5));
	pBtn5->SetCheck(0);
	//CButton *pBtn6 = (CButton*)(GetDlgItem(IDC_CHECK6));
	//pBtn6->SetCheck(0);
}

void CImageMarkDlg::OnBnClickedCheck22()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CButton *pBtn22 = (CButton*)(GetDlgItem(IDC_CHECK22));
	//pBtn22->SetCheck(0);
	CButton *pBtn23 = (CButton*)(GetDlgItem(IDC_CHECK23));
	pBtn23->SetCheck(0);
	CButton *pBtn24 = (CButton*)(GetDlgItem(IDC_CHECK24));
	pBtn24->SetCheck(0);
	CButton *pBtn25 = (CButton*)(GetDlgItem(IDC_CHECK25));
	pBtn25->SetCheck(0);
	CButton *pBtn26 = (CButton*)(GetDlgItem(IDC_CHECK26));
	pBtn26->SetCheck(0);
	CButton *pBtn27 = (CButton*)(GetDlgItem(IDC_CHECK27));
	pBtn27->SetCheck(0);
	CButton *pBtn28 = (CButton*)(GetDlgItem(IDC_CHECK28));
	pBtn28->SetCheck(0);
	CButton *pBtn29 = (CButton*)(GetDlgItem(IDC_CHECK29));
	pBtn29->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck23()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *pBtn22 = (CButton*)(GetDlgItem(IDC_CHECK22));
	pBtn22->SetCheck(0);
	//CButton *pBtn23 = (CButton*)(GetDlgItem(IDC_CHECK23));
	//pBtn23->SetCheck(0);
	CButton *pBtn24 = (CButton*)(GetDlgItem(IDC_CHECK24));
	pBtn24->SetCheck(0);
	CButton *pBtn25 = (CButton*)(GetDlgItem(IDC_CHECK25));
	pBtn25->SetCheck(0);
	CButton *pBtn26 = (CButton*)(GetDlgItem(IDC_CHECK26));
	pBtn26->SetCheck(0);
	CButton *pBtn27 = (CButton*)(GetDlgItem(IDC_CHECK27));
	pBtn27->SetCheck(0);
	CButton *pBtn28 = (CButton*)(GetDlgItem(IDC_CHECK28));
	pBtn28->SetCheck(0);
	CButton *pBtn29 = (CButton*)(GetDlgItem(IDC_CHECK29));
	pBtn29->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck24()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *pBtn22 = (CButton*)(GetDlgItem(IDC_CHECK22));
	pBtn22->SetCheck(0);
	CButton *pBtn23 = (CButton*)(GetDlgItem(IDC_CHECK23));
	pBtn23->SetCheck(0);
	//CButton *pBtn24 = (CButton*)(GetDlgItem(IDC_CHECK24));
	//pBtn24->SetCheck(0);
	CButton *pBtn25 = (CButton*)(GetDlgItem(IDC_CHECK25));
	pBtn25->SetCheck(0);
	CButton *pBtn26 = (CButton*)(GetDlgItem(IDC_CHECK26));
	pBtn26->SetCheck(0);
	CButton *pBtn27 = (CButton*)(GetDlgItem(IDC_CHECK27));
	pBtn27->SetCheck(0);
	CButton *pBtn28 = (CButton*)(GetDlgItem(IDC_CHECK28));
	pBtn28->SetCheck(0);
	CButton *pBtn29 = (CButton*)(GetDlgItem(IDC_CHECK29));
	pBtn29->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck25()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *pBtn22 = (CButton*)(GetDlgItem(IDC_CHECK22));
	pBtn22->SetCheck(0);
	CButton *pBtn23 = (CButton*)(GetDlgItem(IDC_CHECK23));
	pBtn23->SetCheck(0);
	CButton *pBtn24 = (CButton*)(GetDlgItem(IDC_CHECK24));
	pBtn24->SetCheck(0);
	//CButton *pBtn25 = (CButton*)(GetDlgItem(IDC_CHECK25));
	//pBtn25->SetCheck(0);
	CButton *pBtn26 = (CButton*)(GetDlgItem(IDC_CHECK26));
	pBtn26->SetCheck(0);
	CButton *pBtn27 = (CButton*)(GetDlgItem(IDC_CHECK27));
	pBtn27->SetCheck(0);
	CButton *pBtn28 = (CButton*)(GetDlgItem(IDC_CHECK28));
	pBtn28->SetCheck(0);
	CButton *pBtn29 = (CButton*)(GetDlgItem(IDC_CHECK29));
	pBtn29->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck26()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *pBtn22 = (CButton*)(GetDlgItem(IDC_CHECK22));
	pBtn22->SetCheck(0);
	CButton *pBtn23 = (CButton*)(GetDlgItem(IDC_CHECK23));
	pBtn23->SetCheck(0);
	CButton *pBtn24 = (CButton*)(GetDlgItem(IDC_CHECK24));
	pBtn24->SetCheck(0);
	CButton *pBtn25 = (CButton*)(GetDlgItem(IDC_CHECK25));
	pBtn25->SetCheck(0);
	//CButton *pBtn26 = (CButton*)(GetDlgItem(IDC_CHECK26));
	//pBtn26->SetCheck(0);
	CButton *pBtn27 = (CButton*)(GetDlgItem(IDC_CHECK27));
	pBtn27->SetCheck(0);
	CButton *pBtn28 = (CButton*)(GetDlgItem(IDC_CHECK28));
	pBtn28->SetCheck(0);
	CButton *pBtn29 = (CButton*)(GetDlgItem(IDC_CHECK29));
	pBtn29->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck27()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *pBtn22 = (CButton*)(GetDlgItem(IDC_CHECK22));
	pBtn22->SetCheck(0);
	CButton *pBtn23 = (CButton*)(GetDlgItem(IDC_CHECK23));
	pBtn23->SetCheck(0);
	CButton *pBtn24 = (CButton*)(GetDlgItem(IDC_CHECK24));
	pBtn24->SetCheck(0);
	CButton *pBtn25 = (CButton*)(GetDlgItem(IDC_CHECK25));
	pBtn25->SetCheck(0);
	CButton *pBtn26 = (CButton*)(GetDlgItem(IDC_CHECK26));
	pBtn26->SetCheck(0);
	//CButton *pBtn27 = (CButton*)(GetDlgItem(IDC_CHECK27));
	//pBtn27->SetCheck(0);
	CButton *pBtn28 = (CButton*)(GetDlgItem(IDC_CHECK28));
	pBtn28->SetCheck(0);
	CButton *pBtn29 = (CButton*)(GetDlgItem(IDC_CHECK29));
	pBtn29->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck28()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *pBtn22 = (CButton*)(GetDlgItem(IDC_CHECK22));
	pBtn22->SetCheck(0);
	CButton *pBtn23 = (CButton*)(GetDlgItem(IDC_CHECK23));
	pBtn23->SetCheck(0);
	CButton *pBtn24 = (CButton*)(GetDlgItem(IDC_CHECK24));
	pBtn24->SetCheck(0);
	CButton *pBtn25 = (CButton*)(GetDlgItem(IDC_CHECK25));
	pBtn25->SetCheck(0);
	CButton *pBtn26 = (CButton*)(GetDlgItem(IDC_CHECK26));
	pBtn26->SetCheck(0);
	CButton *pBtn27 = (CButton*)(GetDlgItem(IDC_CHECK27));
	pBtn27->SetCheck(0);
	//CButton *pBtn28 = (CButton*)(GetDlgItem(IDC_CHECK28));
	//pBtn28->SetCheck(0);
	CButton *pBtn29 = (CButton*)(GetDlgItem(IDC_CHECK29));
	pBtn29->SetCheck(0);
}


void CImageMarkDlg::OnBnClickedCheck29()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton *pBtn22 = (CButton*)(GetDlgItem(IDC_CHECK22));
	pBtn22->SetCheck(0);
	CButton *pBtn23 = (CButton*)(GetDlgItem(IDC_CHECK23));
	pBtn23->SetCheck(0);
	CButton *pBtn24 = (CButton*)(GetDlgItem(IDC_CHECK24));
	pBtn24->SetCheck(0);
	CButton *pBtn25 = (CButton*)(GetDlgItem(IDC_CHECK25));
	pBtn25->SetCheck(0);
	CButton *pBtn26 = (CButton*)(GetDlgItem(IDC_CHECK26));
	pBtn26->SetCheck(0);
	CButton *pBtn27 = (CButton*)(GetDlgItem(IDC_CHECK27));
	pBtn27->SetCheck(0);
	CButton *pBtn28 = (CButton*)(GetDlgItem(IDC_CHECK28));
	pBtn28->SetCheck(0);
	//CButton *pBtn29 = (CButton*)(GetDlgItem(IDC_CHECK29));
	//pBtn29->SetCheck(0);
}

