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

using namespace std;
using namespace boost;
using namespace boost::filesystem;

struct occurrence
{
    int line, position;
    wstring fileName, lineText, Text;

    occurrence() {}

    occurrence(wstring fileName, wstring lineText, wstring Text, int line, int position)
            :
            fileName(fileName), lineText(lineText), Text(Text), line(line), position(position) {}

    wstring toString()
    {
        return L"filename: " + fileName + L" , line text: " + lineText + L" , actual text: " + Text
               + L" , line number: " + std::to_wstring(line) + L" , position: " + std::to_wstring(position);
    }
};

void findInFile(boost::filesystem::wifstream &stream, wstring filename, wregex &reg, vector<occurrence> &res);

int findInFiles(const path &dir_path, wregex &reg, vector<occurrence> &res);