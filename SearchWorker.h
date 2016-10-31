//
// Created by serg on 10/26/16.
//

#ifndef RODIN_FILE_SEARCH_SEARCHWORKER_H
#define RODIN_FILE_SEARCH_SEARCHWORKER_H

#pragma once

#include <nan.h>
#include <functional>
#include <iostream>
#include <cmath>
#include <string>

#include "cppFileSearch.h"

using namespace Nan;
using namespace std;
using namespace v8;

class SearchWorker : public AsyncWorker
{
    wstring searchRoot, regexWStr;
    vector<occurrence> res;
    std::string error;
    int searchLimit;
    bool caseSensitive;
    bool isRegex;
	bool isMultiline;
public:
    SearchWorker(Callback *callback, wstring searchRoot, wstring regexWStr, int searchLimit,
                 bool caseSensitive = true, bool isRegex = true, bool isMultiline = false);

    ~SearchWorker();

    void Execute();

    void HandleOKCallback();
};


#endif //RODIN_FILE_SEARCH_SEARCHWORKER_H
