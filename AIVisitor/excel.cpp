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
void create_result_excel() {
	// 标题1
	std::wstring title1_wstr = L"企业名称";
	const std::string title1_utf8 = convert_wstring_to_utf8_string(title1_wstr);
	// 标题2
	std::wstring title2_wstr = L"企业注册号";
	const std::string title2_utf8 = convert_wstring_to_utf8_string(title2_wstr);
	// 文件名
	// std::wstring filename_wstr = L"网店工商信息图片文字提取.xlsx";
	std::wstring filename_wstr = L"result.xlsx";
	const std::string filename_utf8 = convert_wstring_to_utf8_string(filename_wstr);

	xlnt::workbook wb;
	xlnt::worksheet ws = wb.active_sheet();
	ws.cell("A1").value(title1_utf8.c_str());
	ws.cell("B1").value(title2_utf8.c_str());
	wb.save(filename_utf8.c_str());
}

/**
* 复制result.xlsx到filename中
*/
bool copy_and_save_file(const std::wstring &dst) {
	const std::wstring src = L"result.xlsx";

	std::wifstream ifs(src, std::ios::binary);
	std::wofstream ofs(dst, std::ios::binary);

	if (!ifs.is_open()) { // 源文件
		std::wcout << L"open src file fail: " + src << std::endl;
		return false;
	}

	ofs << ifs.rdbuf();
	ifs.close();
	ofs.close();
	/*
	if (0 != remove(src.c_str()) {
		std::wcerr << L"remove src file fail: " + src << std::endl;
	}*/
	return true;
}

/**
* 将结果保存在result.xlsx
* 前提: resutlt.xlsx存在
*/
void open_excel_and_add_result(const std::pair<std::string, std::string> rst) {
	// 转换为utf8的中文字符串
	std::vector<std::string> vct_utf8;
	vct_utf8.push_back(convert_wstring_to_utf8_string(covert_string_to_wstring(rst.first)));
	vct_utf8.push_back(convert_wstring_to_utf8_string(covert_string_to_wstring(rst.second)));

	// 追加到result.xlsx中
	xlnt::workbook wb;
	wb.load("result.xlsx");
	xlnt::worksheet ws = wb.active_sheet();
	std::cout << ws.highest_row() << std::endl;
	int row_size = ws.highest_row();
	ws.cell(xlnt::cell_reference(1, ++row_size)).value(vct_utf8[0].c_str());
	std::cout << ws.highest_row() << std::endl;
	std::cout << vct_utf8[0].c_str() << std::endl;
	ws.cell(xlnt::cell_reference(2, row_size)).value(vct_utf8[1].c_str());
	wb.save("result.xlsx");
}
/*
int main() {
	// create_result_excel();
	// std::vector<std::string> rst;
	// rst.push_back("百度集团有限公司");
	// rst.push_back("914210236162401254");
	// open_excel_and_add_result(rst);
	const std::string dst("D:\\book\\idea资料\\结果.xlsx");
	copy_and_save_file(dst);
	system("pause");
	return 0;
}
*/