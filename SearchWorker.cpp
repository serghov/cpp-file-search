//
// Created by serg on 10/26/16.
//

#include "SearchWorker.h"

SearchWorker::SearchWorker(Callback *callback, wstring searchRoot, wstring regexWStr, int searchLimit, bool caseSensitive)
        : AsyncWorker(callback), searchRoot(searchRoot), regexWStr(regexWStr), error(), searchLimit(searchLimit), caseSensitive(caseSensitive) {}

SearchWorker::~SearchWorker() {}

void SearchWorker::Execute()
{
    const path myPath = this->searchRoot;

    wregex reg(this->regexWStr, (!this->caseSensitive)?std::regex_constants::icase|std::regex_constants::ECMAScript : std::regex_constants::ECMAScript);
    //implement this better somehow
    try
    {
        findInFiles(myPath, reg, this->res, this->searchLimit);
    }
    catch (std::exception const &e)
    {
        this->error = e.what();
    }
}

void SearchWorker::HandleOKCallback()
{
    Nan::HandleScope scope;

    v8::Local <v8::Array> results = New<v8::Array>(this->res.size());

    int i = 0;
    if (!this->error.size())
        for_each(this->res.begin(), this->res.end(),
                 [&](occurrence &value)
                 {
                     Local <Object> curObj = Nan::New<v8::Object>();
                     {
                         std::string tmp(value.fileName.begin(), value.fileName.end());
                         curObj->Set(Nan::New("fileName").ToLocalChecked(),
                                     Nan::New(tmp.c_str()).ToLocalChecked());
                     }
                     {
                         std::string tmp(res[i].lineText.begin(), res[i].lineText.end());
                         curObj->Set(Nan::New("lineText").ToLocalChecked(),
                                     Nan::New(tmp.c_str()).ToLocalChecked());
                     }
                     {
                         std::string tmp(res[i].Text.begin(), res[i].Text.end());
                         curObj->Set(Nan::New("Text").ToLocalChecked(),
                                     Nan::New(tmp.c_str()).ToLocalChecked());
                     }

                     curObj->Set(Nan::New("line").ToLocalChecked(),
                                 Nan::New(value.line));

                     curObj->Set(Nan::New("position").ToLocalChecked(),
                                 Nan::New(value.position));

                     Nan::Set(results, i, curObj);
                     i++;
                 });

    Local <Value> argv[] = {
            Null(),
            results
    };
    if (this->error.size())
        argv[0] = Nan::New(this->error.c_str()).ToLocalChecked();

    callback->Call(2, argv);
}
