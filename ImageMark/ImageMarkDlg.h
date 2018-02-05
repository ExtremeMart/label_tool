
// ImageMarkDlg.h : 头文件
//

#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
// CImageMarkDlg 对话框
class CImageMarkDlg : public CDialogEx
{
// 构造
public:
	CImageMarkDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEMARK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void Display(cv::Mat strimg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void CImageMarkDlg::Delete_lastline();
	afx_msg std::vector<std::string>  CImageMarkDlg::get_all_files_names_within_folder(std::string folder);
	long labelednum;
	long Alldatanum;	
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedleixing1();
	afx_msg void OnBnClickedleixing2();
	afx_msg void OnBnClickedleixing3();
	afx_msg void OnBnClickedleixing4();
	afx_msg void OnBnClickedleixing5();
	afx_msg void OnBnClickedleixing6();
	afx_msg void OnBnClickedleixing7();
	afx_msg void OnBnClickedleixing8();	
	afx_msg void OnBnClickedleixing9();	
	afx_msg void OnBnClickedleixing10();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClickedchunbu_5();
	afx_msg void OnBnClicked1();
};
