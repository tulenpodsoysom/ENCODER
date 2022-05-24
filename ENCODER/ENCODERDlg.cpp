
// ENCODERDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "ENCODER.h"
#include "ENCODERDlg.h"
#include "afxdialogex.h"

#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CENCODERDlg



CENCODERDlg::CENCODERDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENCODER_DIALOG, pParent)
	, strOutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CENCODERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITINPUT, strInput);
	DDX_Text(pDX, IDC_EDITOUTPUT, strOutput);
}

BEGIN_MESSAGE_MAP(CENCODERDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONOPEN, &CENCODERDlg::OnBnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTONENCODE, &CENCODERDlg::OnBnClickedButtonencode)
	ON_BN_CLICKED(IDC_BUTTONDECODE, &CENCODERDlg::OnBnClickedButtondecode)
END_MESSAGE_MAP()


// Обработчики сообщений CENCODERDlg

BOOL CENCODERDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CENCODERDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CENCODERDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CENCODERDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CENCODERDlg::OnBnClickedButtonopen()
{
	CFileDialog dialog(1);
	CFile file;
	int size;
	char* buffer;

	dialog.DoModal();
	filepath_input = dialog.GetPathName();

	file.Open(filepath_input, file.modeRead);
	size = file.GetLength();
	buffer = new char[size + 1]; buffer[size] = '\0';
	file.Read(buffer, size);
	
	strInput = buffer;
	input = buffer;
	UpdateData(0);
}


void CENCODERDlg::OnBnClickedButtonencode()
{
	string output = Encode(input, codeTable);
	strOutput = output.c_str();
	UpdateData(0);

	CFileDialog dialog(0);
	CFile file;

	dialog.DoModal();

	file.Open(dialog.GetPathName(), file.modeCreate | file.modeReadWrite);
	file.Write(output.c_str(), output.size());
}


void CENCODERDlg::OnBnClickedButtondecode()
{
	CFileDialog dialog(1);
	CFile file;

	dialog.DoModal();
	filepath_output = dialog.GetPathName();

	file.Open(filepath_output, file.modeRead);
	int size = file.GetLength();
	char* buffer = new char[size + 1]; buffer[size] = '\0';
	file.Read(buffer, size);

	strInput = buffer;

	output = Decode(buffer);
	strOutput = output.c_str();

	UpdateData(0);
}

std::string CENCODERDlg::Encode(std::string arr, std::map<char, std::string>& codeTable)
{

	/*Таблица частотностей символов*/
	std::map<char, int> sizemap;
	for (auto& i : arr)
	{
		sizemap[i]++;
	}

	codeTable.clear();
	for (auto& i : sizemap)
	{
		codeTable[i.first] = "";
	}

	/*бинарное дерево узлов и список свободных узлов*/
	vector<node> nodes;
	vector<node> primary_nodes;
	for (auto& i : sizemap)
	{
		node _node;
		_node.data.first = i.first;
		_node.data.second = i.second;

		primary_nodes.push_back(_node);
		nodes.push_back(_node);
	}

	/*Построение дерева*/
	while (primary_nodes.size() > 1)
	{
		auto a = GetTwoMin(primary_nodes);
		node _node;
		_node.data.first = a.first.data.first + a.second.data.first;
		_node.data.second = a.first.data.second + a.second.data.second;
		_node.next_1 = a.first.data.first;
		_node.next_2 = a.second.data.first;

		nodes.push_back(_node);
		primary_nodes.push_back(_node);
	}

	/*Поиск по дереву*/
	for (auto& i : sizemap)
	{
		char ch = i.first;
		node _node = *max_element(nodes.begin(),nodes.end(), [](const node n1, const node n2) {return n1.data.second < n2.data.second; });

		string code;
		while ( (_node.next_1 != "") && (_node.next_2 != ""))
		{
			if (_node.next_1.find(i.first) != _node.next_1.npos)
			{
				_node = *find(nodes.begin(), nodes.end(), _node.next_1);
				code += "1";
			}
			else
			{
				_node = *find(nodes.begin(), nodes.end(), _node.next_2);
				code += "0";
			}
		}

		codeTable[ch] = code;
	}

	/*Строка с закодированным сообщением*/
	string decoded;
	for (auto& i : arr)
	{
		decoded += codeTable[i];
	}

	/*Строка с закодированным файлом*/
	string decoded_;

	/*Заглавление файла*/
	decoded_ += (int)sizemap.size();
	decoded_ += (int)    arr.size();
	for (auto& i : codeTable)
	{
		decoded_ += i.second.size();
		decoded_ += i.first;
		decoded_ += strtol(i.second.c_str(), NULL, 2);
	}

	/*Запись сообщения в файл*/
	for (size_t i = 0; i < decoded.size(); i += 8)
	{
		string sub = decoded.substr(i, 8);
		if (sub.size() != 8)
		{
			int n = sub.size();
			for (size_t i = 0; i < 8 - n; i++)
				sub.push_back('0');
			
		}
		decoded_.push_back(strtol(sub.c_str(), NULL, 2));
	}

	return decoded_;
}

/// <summary>
///		Функция находит два наименьших узла и удаляет их из списка.
/// </summary>
std::pair<node, node> CENCODERDlg::GetTwoMin(std::vector<node>& vec)
{
	node a, b;
	auto min1 = min_element(vec.begin(), vec.end(), [](const node n1, const node n2) {return n1.data.second < n2.data.second; });
	a = *min1;
	vec.erase(min1);
	auto min2 = min_element(vec.begin(), vec.end(), [](const node n1, const node n2) {return n1.data.second < n2.data.second; });
	b = *min2;
	vec.erase(min2);

	return { a,b };
}

std::string CENCODERDlg::Decode(char* file)
{
	struct CodeHeader
	{
		char n;
		char a;
		char b;
	};
	vector<CodeHeader> codes;
	int headersize = *file;
	int stringsize = *(file + 1);

	for (size_t i = 0; i < headersize; i++)
	{
		char n = *(file + 2 + i * 3);
		char a = *(file + 2 + i * 3 + 1);
		char b = *(file + 2 + i * 3 + 2);
		codes.push_back({ n,a,b });
	}

	for (auto& i : codes)
	{
		char buf[16];
		_itoa_s(i.b, buf, 2);
		string str = buf;
		if (str.size() != i.n)
		{
			int n = str.size();
			for (size_t j = 0; j < i.n - n; j++)
			{
				str.insert(0, "0");
			}
		}
		codeTable[i.a] = str;
	}

	file = file + headersize * 3 + 2;
	string strcode(file);
	string strcodebin;
	string strout;


	for (auto& i : strcode)
	{
		char buf[32];

		_itoa_s((unsigned char)i, buf, 2);

		string str = buf;
		int n = str.size();
		for (int j = 0; j < 8 - n; j++)
		{
			str.insert(0, "0");
		}
		strcodebin += str;
	}


	int k = 0;
	string str;
	while (stringsize)
	{
		str += strcodebin[k];
		k++; 
		for (auto& i : codeTable)
		{
			if (i.second == str)
			{
				strout += i.first;
				str.clear();
				strcodebin.erase(0, k);
				k = 0; stringsize--;
				break;
			}
		}
	}
	return strout;
}
