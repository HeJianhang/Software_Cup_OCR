#include "excel.h"

/**
* ��wstringװ��Ϊutf8�ַ���, ���ڴ����������ַ����ַ���
*/
std::string convert_wstring_to_utf8_string(const std::wstring &wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	std::string utf8_string = converter.to_bytes(wstr);
	return utf8_string;
}

/**
* ��stringװ��Ϊwstring
*/
std::wstring covert_string_to_wstring(const std::string &str) {
	size_t i;
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs");
	const char* _source = str.c_str();
	size_t _dsize = str.size() + 1;
	wchar_t* _dest = new wchar_t[_dsize];
	wmemset(_dest, 0x0, _dsize);
	mbstowcs_s(&i, _dest, _dsize, _source, _dsize);
	std::wstring wstr = _dest;
	delete[] _dest;
	setlocale(LC_ALL, curLocale.c_str());
	return wstr;
}

/**
* ����result.xlsx����������
*/
void create_result_excel(const std::wstring& filename_wstr, const QStandardItemModel* model) {
	// ����1
	std::wstring title1_wstr = L"��ҵ����";
	const std::string title1_utf8 = convert_wstring_to_utf8_string(title1_wstr);
	// ����2
	std::wstring title2_wstr = L"��ҵע���";
	const std::string title2_utf8 = convert_wstring_to_utf8_string(title2_wstr);
	// �ļ���
	const std::string filename_utf8 = convert_wstring_to_utf8_string(filename_wstr);

	xlnt::workbook wb;
	xlnt::worksheet ws = wb.active_sheet();
	ws.cell("A1").value(title1_utf8.c_str());
	ws.cell("B1").value(title2_utf8.c_str());
	
	
	// ׷�ӵ�result.xlsx��
	for (int i = 0; i < model->rowCount(); ++i)
	{
		QString name = model->data(model->index(i, 0)).toString();
		QString num = model->data(model->index(i, 1)).toString();

		std::string wsName = convert_wstring_to_utf8_string(name.toStdWString());
		std::string wsNum = convert_wstring_to_utf8_string(num.toStdWString());

		ws.cell(xlnt::cell_reference(1, i + 2)).value(wsName.c_str());
		ws.cell(xlnt::cell_reference(2, i + 2)).number_format(xlnt::number_format::text());
		ws.cell(xlnt::cell_reference(2, i + 2)).value(wsNum.c_str());
	}


	wb.save(filename_utf8.c_str());
}


