#pragma once#include <QDebug>
#include <iostream>
#include <fstream>
#include <xlnt/xlnt.hpp>
#include <string>
#include <locale>
#include <codecvt>
#include <QtWidgets/QWidget>
#include <QStandardItemModel>
std::string convert_wstring_to_utf8_string(const std::wstring &wstr);
std::wstring covert_string_to_wstring(const std::string &str);
void create_result_excel(const std::wstring&,const QStandardItemModel*);
