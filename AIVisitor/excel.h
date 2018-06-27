#pragma once
#include <iostream>
#include <fstream>
#include <xlnt/xlnt.hpp>
#include <string>
#include <locale>
#include <codecvt>
std::string convert_wstring_to_utf8_string(const std::wstring &wstr);
std::wstring covert_string_to_wstring(const std::string &str);
void create_result_excel();
bool copy_and_save_file(const std::wstring &dst);
void open_excel_and_add_result(const std::pair<std::string, std::string> rst);