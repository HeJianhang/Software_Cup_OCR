#include "excel.h"

/**
* 将wstring装换为utf8字符串, 用于处理含有中文字符的字符串
*/
std::string convert_wstring_to_utf8_string(const std::wstring &wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	std::string utf8_string = converter.to_bytes(wstr);
	return utf8_string;
}

/**
* 将string装换为wstring
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
* 创建result.xlsx保存输出结果
*/
void create_result_excel(const std::wstring& filename_wstr, const QStandardItemModel* model) {
	// 标题1
	std::wstring title1_wstr = L"企业名称";
	const std::string title1_utf8 = convert_wstring_to_utf8_string(title1_wstr);
	// 标题2
	std::wstring title2_wstr = L"企业注册号";
	const std::string title2_utf8 = convert_wstring_to_utf8_string(title2_wstr);
	// 文件名
	const std::string filename_utf8 = convert_wstring_to_utf8_string(filename_wstr);

	xlnt::workbook wb;
	xlnt::worksheet ws = wb.active_sheet();
	ws.cell("A1").value(title1_utf8.c_str());
	ws.cell("B1").value(title2_utf8.c_str());
	
	
	// 追加到result.xlsx中
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


