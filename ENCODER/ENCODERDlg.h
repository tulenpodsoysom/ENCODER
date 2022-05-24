
// ENCODERDlg.h: файл заголовка
//

#pragma once
#include <map>
#include <string>
#include <vector>

struct node
{
	std::pair<std::string, int /*string*/> data;
	std::string next_1;
	std::string next_2;
	//node* next_2 = NULL;

	node() {};

	bool operator == (std::string str) { return data.first == str; };
};

// Диалоговое окно CENCODERDlg
class CENCODERDlg : public CDialogEx
{
// Создание
public:
	CENCODERDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENCODER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString strInput;
	CString strOutput;
	CString filepath_input;
	CString filepath_output;

	std::string input;
	std::string output;
	std::map<char, std::string> codeTable;

	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnBnClickedButtonencode();
	afx_msg void OnBnClickedButtondecode();

	std::string Encode(std::string arr,std::map<char,std::string>& codeTable );
	std::string Decode(char* buffer);
	std::pair<node, node> GetTwoMin(std::vector<node>& vec);

};
