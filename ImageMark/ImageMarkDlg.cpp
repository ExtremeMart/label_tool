
// ImageMarkDlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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
// CImageMarkDlg 对话框
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
	ON_BN_CLICKED(IDCANCEL, &CImageMarkDlg::OnBnClickedCancel)
	ON_BN_CLICKED(leixing1, &CImageMarkDlg::OnBnClickedleixing1)
	ON_BN_CLICKED(leixing2, &CImageMarkDlg::OnBnClickedleixing2)
	ON_BN_CLICKED(leixing3, &CImageMarkDlg::OnBnClickedleixing3)	
	ON_BN_CLICKED(leixing4, &CImageMarkDlg::OnBnClickedleixing4)
	ON_BN_CLICKED(leixing5, &CImageMarkDlg::OnBnClickedleixing5)	
	ON_BN_CLICKED(leixing6, &CImageMarkDlg::OnBnClickedleixing6)
	ON_BN_CLICKED(leixing7, &CImageMarkDlg::OnBnClickedleixing7)
	ON_BN_CLICKED(leixing8, &CImageMarkDlg::OnBnClickedleixing8)
	ON_BN_CLICKED(leixing9, &CImageMarkDlg::OnBnClickedleixing9)
	ON_BN_CLICKED(leixing10, &CImageMarkDlg::OnBnClickedleixing10)
	ON_BN_CLICKED(IDC_BUTTON1, &CImageMarkDlg::OnBnClickedButton1)
	ON_BN_CLICKED(chunbu_5, &CImageMarkDlg::OnBnClickedchunbu_5)
	ON_BN_CLICKED(yanbu_1, &CImageMarkDlg::OnBnClicked1)
END_MESSAGE_MAP()
// CImageMarkDlg 消息处理程序
BOOL CImageMarkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CImageMarkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CImageMarkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CImageMarkDlg::Delete_lastline(){
int pos = listpath.find("ImageList.txt");
dataloc2 = listpath.substr(0, pos);
ifstream label_line(dataloc2 + "all_label.txt");//找到label文件
vector<string> label_lines;
string templine;
while (getline(label_line,templine))
{
	label_lines.push_back(templine);
}
label_line.close();
ofstream label_line2(dataloc2 + "all_label.txt", ios::trunc);//找到label文件
for (size_t i = 0; i < label_lines.size()-1; i++)
{
	label_line2 << label_lines[i] << endl;
}
	
}
//文件夹下的所有文件
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
//将实时采集图像显示在MFC的picture控件上
void CImageMarkDlg::Display(cv::Mat strimg)
{

	CDC* pDC = GetDlgItem(IDC_showimg)->GetDC();//获得显示控件的 DC
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
	if (rate_img > rate_rect)//照片更长
	{
		Mat desImg(height_img, ((float)x/y )* height_img, CV_8UC3, Scalar(255, 255, 255));//创建一个全白的图片
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
	if (rate_img < rate_rect)//照片更宽
	{
		Mat desImg(((float)y / x) *width_img, width_img, CV_8UC3, Scalar(255, 255, 255));//创建一个全白的图片
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
	mfcimg.CopyOf(img);// 复制图片
	mfcimg.DrawToHDC(hDC, &rect);//将图片绘制到显示控件的指定区域内
								 

}
//打开
void CImageMarkDlg::OnBnClickedOk()  //开始
{
	CFileDialog dlg(
		true, _T("*.bmp;*.jpg;*.tif*.png"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image?files?All?Files?(*.*)?|*.*||"), NULL
		);
	dlg.m_ofn.lpstrTitle = _T("打开LIST列表");//对话框名字
	if (dlg.DoModal() == IDOK)	{//工作路径改变为打开文档处的路径
		if (dlg.GetFileExt() != "txt" )		{
			AfxMessageBox(_T("请选择txt列表格式！"), MB_OK);
			return;
		}
		CString mPath = dlg.GetPathName();
		USES_CONVERSION;
		listpath = _T(mPath);//W2A(mPath);
	}
	unlabeldata.open(listpath);	
	int pos = listpath.find("ImageList.txt");
	if (pos == string::npos) { 
		MessageBox(_T("请打开ImageList.txt文件！")); exit(0); 
	}
	dataloc2 = listpath.substr(0,pos);//保存的是路径
	ifstream countmgnum(listpath);//找到label文件
	string buffforcount;
	Alldatanum = 0;
	while (getline(countmgnum, buffforcount))	{
		Alldatanum++;		
	}//////////////
	ifstream all_label2(dataloc2 + "all_label.txt", ios::app);//找到label文件
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
	}/////////////
	getline(unlabeldata, dataloc);
	dataloc2 = dataloc2 + dataloc;
	cv::Mat Strimg = cv::imread(dataloc2);	
	Display(Strimg);	
	UpdateData(false);
}
//生成列表文件
void CImageMarkDlg::OnBnClickedButton2()//生成列表文件
{

	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(
		true, _T("*.bmp;*.jpg;*.tif*.png"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image?files?All?Files?(*.*)?|*.*||"), NULL

		);
	dlg.m_ofn.lpstrTitle = _T("打开图片列表");
	if (dlg.DoModal() == IDOK)
	{
		string ext = dlg.GetFileExt();
		if ((ext == "jpg")  || (ext == "png"))
		{
			
		}
		else {
			AfxMessageBox(_T("请选择jpg或png列表格式！"), MB_OK);
			return;
		}

		CString mPath = dlg.GetPathName();
		USES_CONVERSION;
		listpath = _T(mPath);

		int pos = listpath.find_last_of("\\");
		string alllistpath = listpath.substr(0, pos+1);

		vector <string> allimgpath=get_all_files_names_within_folder(alllistpath);
		ofstream all_label3(alllistpath +"ImageList.txt");//找到label文件
		for (size_t i = 0; i < allimgpath.size(); i++)
		{
			all_label3<<allimgpath[i] << endl;
		}
	}

}
//关闭
void CImageMarkDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
//选择类型
void CImageMarkDlg::OnBnClickedleixing1()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing2));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing3));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing4));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing5));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing6));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing7));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing8));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing9));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing10));
	pBtn22->SetCheck(0);
	// TODO: 在此添加控件通知处理程序代码
}
void CImageMarkDlg::OnBnClickedleixing2()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing3));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing1));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing4));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing5));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing6));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing7));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing8));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing9));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing10));
	pBtn22->SetCheck(0);
	// TODO: 在此添加控件通知处理程序代码
}
void CImageMarkDlg::OnBnClickedleixing3()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing2));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing1));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing4));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing5));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing6));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing7));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing8));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing9));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing10));
	pBtn22->SetCheck(0);// TODO: 在此添加控件通知处理程序代码
}
void CImageMarkDlg::OnBnClickedleixing4()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing2));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing3));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing1));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing5));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing6));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing7));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing8));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing9));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing10));
	pBtn22->SetCheck(0);// TODO: 在此添加控件通知处理程序代码
}
void CImageMarkDlg::OnBnClickedleixing5()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing2));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing3));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing4));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing1));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing6));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing7));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing8));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing9));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing10));
	pBtn22->SetCheck(0);// TODO: 在此添加控件通知处理程序代码
}
void CImageMarkDlg::OnBnClickedleixing6()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing2));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing3));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing4));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing5));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing1));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing7));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing8));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing9));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing10));
	pBtn22->SetCheck(0);// TODO: 在此添加控件通知处理程序代码// TODO: 在此添加控件通知处理程序代码
}
void CImageMarkDlg::OnBnClickedleixing7()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing2));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing3));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing4));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing5));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing6));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing1));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing8));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing9));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing10));
	pBtn22->SetCheck(0);// TODO: 在此添加控件通知处理程序代码// TODO: 在此添加控件通知处理程序代码
}
void CImageMarkDlg::OnBnClickedleixing8()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing2));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing3));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing4));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing5));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing6));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing7));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing1));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing9));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing10));
	pBtn22->SetCheck(0);// TODO: 在此添加控件通知处理程序代码// TODO: 在此添加控件通知处理程序代码
}
void CImageMarkDlg::OnBnClickedleixing9()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing2));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing3));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing4));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing5));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing6));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing7));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing8));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing1));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing10));
	pBtn22->SetCheck(0);// TODO: 在此添加控件通知处理程序代码// TODO: 在此添加控件通知处理程序代码
}
void CImageMarkDlg::OnBnClickedleixing10()
{
	CButton *pBtn22 = (CButton*)(GetDlgItem(leixing2));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing3));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing4));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing5));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing6));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing7));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing8));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing9));
	pBtn22->SetCheck(0);
	pBtn22 = (CButton*)(GetDlgItem(leixing1));
	pBtn22->SetCheck(0);
}// TODO: 在此添加控件通知处理程序代码
//下一张
bool need_exit = false;
void CImageMarkDlg::OnBnClickedButton1()
{
	int pos = listpath.find("ImageList.txt");
	dataloc2 = listpath.substr(0, pos);//路径
	ofstream all_label(dataloc2 + "all_label.txt", ios::app);//找到label文件
	std::streampos pos_lines = unlabeldata.tellg();
	all_label << dataloc;//标记文件存放在all_label.txt中
	
	//额头
	bool etou_labeled = false;
	if (BST_CHECKED == IsDlgButtonChecked(etou_1)) {
		CButton *pBtn = (CButton*)(GetDlgItem(etou_1));
		pBtn->SetCheck(0);
		all_label << " 1";
		etou_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(etou_2)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(etou_2));
		pBtn->SetCheck(0);
		etou_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(etou_3)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(etou_3));
		pBtn->SetCheck(0);
		etou_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(etou_4)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(etou_4));
		pBtn->SetCheck(0);
		etou_labeled = true;
	}
	else {
		all_label << " 0";
	}
	//眉毛
	bool meimao_labeled = false;
	if (BST_CHECKED == IsDlgButtonChecked(meimao_1)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(meimao_1));
		pBtn->SetCheck(0);
		meimao_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(meimao_2)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(meimao_2));
		pBtn->SetCheck(0);
		meimao_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(meimao_3)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(meimao_3));
		pBtn->SetCheck(0);
		meimao_labeled = true;
	}
	else {
		all_label << " 0";
	}
	//眼部
	bool yanbu_labeled = false;
	if (BST_CHECKED == IsDlgButtonChecked(yanbu_1)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(yanbu_1));
		pBtn->SetCheck(0);
		yanbu_labeled = true;
	}
	else {
		all_label << " 0";
	}
	//脸部
	bool lianbu_labeled = false;
	if (BST_CHECKED == IsDlgButtonChecked(lianbu_1)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(lianbu_1));
		pBtn->SetCheck(0);
		lianbu_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(lianbu_2)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(lianbu_2));
		pBtn->SetCheck(0);
		lianbu_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(lianbu_3)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(lianbu_3));
		pBtn->SetCheck(0);
		lianbu_labeled = true;
	}
	else {
		all_label << " 0";
	}
	//鼻子
	bool bizi_labeled = false;
	if (BST_CHECKED == IsDlgButtonChecked(bizi_1)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(bizi_1));
		pBtn->SetCheck(0);
		bizi_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(bizi_2)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(bizi_2));
		pBtn->SetCheck(0);
		bizi_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(bizi_3)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(bizi_3));
		pBtn->SetCheck(0);
		bizi_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(bizi_4)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(bizi_4));
		pBtn->SetCheck(0);
		bizi_labeled = true;
	}
	else {
		all_label << " 0";
	}
	// 唇部
	bool chunbu_labeled = false;
	if (BST_CHECKED == IsDlgButtonChecked(chunbu_1)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(chunbu_1));
		pBtn->SetCheck(0);
		chunbu_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(chunbu_2)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(chunbu_2));
		pBtn->SetCheck(0);
		chunbu_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(chunbu_3)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(chunbu_3));
		pBtn->SetCheck(0);
		chunbu_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(chunbu_4)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(chunbu_4));
		pBtn->SetCheck(0);
		chunbu_labeled = true;
	}
	else {
		all_label << " 0";
	}
	if (BST_CHECKED == IsDlgButtonChecked(chunbu_5)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(chunbu_5));
		pBtn->SetCheck(0);
		chunbu_labeled = true;
	}
	else {
		all_label << " 0";
	}

	//下巴
	bool xiaba_labeled = false;
	if (BST_CHECKED == IsDlgButtonChecked(xiaba_1)) {
		all_label << " 1";
		CButton *pBtn = (CButton*)(GetDlgItem(xiaba_1));
		pBtn->SetCheck(0);
		xiaba_labeled = true;
	}
	else {
		all_label << " 0";
	}	
	//特征//
	bool leixing_labeled = false;
	if (BST_CHECKED == IsDlgButtonChecked(leixing1)) {
		all_label << " 1" ;
		CButton *pBtn = (CButton*)(GetDlgItem(leixing1));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(leixing2)) {
		all_label << " 2" ;
		CButton *pBtn = (CButton*)(GetDlgItem(leixing2));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(leixing3)) {
		all_label << " 3";
		CButton *pBtn = (CButton*)(GetDlgItem(leixing3));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(leixing4)) {
		all_label << " 4";
		CButton *pBtn = (CButton*)(GetDlgItem(leixing4));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(leixing5)) {
		all_label << " 5";
		CButton *pBtn = (CButton*)(GetDlgItem(leixing5));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(leixing6)) {
		all_label << " 6";
		CButton *pBtn = (CButton*)(GetDlgItem(leixing6));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(leixing7)) {
		all_label << " 7";
		CButton *pBtn = (CButton*)(GetDlgItem(leixing7));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(leixing8)) {
		all_label << " 8";
		CButton *pBtn = (CButton*)(GetDlgItem(leixing8));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(leixing9)) {
		all_label << " 9";
		CButton *pBtn = (CButton*)(GetDlgItem(leixing9));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	else if (BST_CHECKED == IsDlgButtonChecked(leixing10)) {
		all_label << " 10";
		CButton *pBtn = (CButton*)(GetDlgItem(leixing10));
		pBtn->SetCheck(0);
		leixing_labeled = true;
	}
	if (false == leixing_labeled) {
		MessageBox(_T("请选择类型！"));
		unlabeldata.seekg(pos_lines);
		all_label << endl;
		Delete_lastline();
		return;
	}
	all_label << endl;
	if (true == need_exit) {
		MessageBox(_T("所有图片已标记完毕！"));
		exit(1);
	}
	getline(unlabeldata, dataloc);
	if (labelednum + 2 == Alldatanum&&need_exit==false)
		need_exit = true;		
	dataloc2 = dataloc2 + dataloc;
	cv::Mat Strimg = cv::imread(dataloc2);
	Display(Strimg);
	labelednum++;
	UpdateData(false);
}
void CImageMarkDlg::OnBnClickedchunbu_5()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CImageMarkDlg::OnBnClicked1()
{
	// TODO: 在此添加控件通知处理程序代码
}
