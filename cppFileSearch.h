//
// Created by serg on 10/25/16.
//

#ifndef RODIN_FILE_SEARCH_CPP_FILE_SEARCH_H
#define RODIN_FILE_SEARCH_CPP_FILE_SEARCH_H
#endif //RODIN_FILE_SEARCH_CPP_FILE_SEARCH_H

#pragma once

#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <string>
#include <regex>
#include <fstream>
#include <locale>
#include <codecvt>

using namespace std;
namespace bf = boost::filesystem;

struct occurrence
{
    int line, position;
    wstring fileName, lineText, Text;

    occurrence() {}

    occurrence(wstring fileName, wstring lineText, wstring Text, int line, int position)
            :
            line(line), position(position), fileName(fileName), lineText(lineText), Text(Text) {}

    wstring toString()
    {
        return L"filename: " + fileName + L" , line text: " + lineText + L" , actual text: " + Text
               + L" , line number: " + std::to_wstring(line) + L" , position: " + std::to_wstring(position);
    }
};

enum
{
    max_file_size = 50 * 1024 * 1024
};//make accessible from js somehow

void findInFile(std::wifstream &stream, const wstring filename, const wregex &reg, vector<occurrence> &res,
                bool multiline = false);

int findInFiles(const bf::path &dir_path, const wregex &reg, vector<occurrence> &res, int limit);

wstring escapeRegex(const wstring &str);

wstring utf8ToWstring(const string &str);

string wstringToUtf8 (const wstring& str);
