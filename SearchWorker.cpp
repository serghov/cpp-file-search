//
// Created by serg on 10/26/16.
//

#include "SearchWorker.h"

SearchWorker::SearchWorker(Callback *callback, wstring searchRoot, wstring regexWStr, int searchLimit,
                           bool caseSensitive, bool isRegex)
        : AsyncWorker(callback), searchRoot(searchRoot), regexWStr(regexWStr), error(), searchLimit(searchLimit),
          caseSensitive(caseSensitive), isRegex(isRegex) {}

SearchWorker::~SearchWorker() {}

void SearchWorker::Execute()
{
    try
    {
        const bf::path myPath = this->searchRoot;

        auto regex_type = std::regex_constants::ECMAScript;
        if (!this->caseSensitive)
            regex_type |= std::regex_constants::icase;
        if (!this->isRegex)
            this->regexWStr = escapeRegex(regexWStr);
        wregex reg(this->regexWStr, regex_type);
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

					 curObj->Set(Nan::New("fileName").ToLocalChecked(),
								 Nan::New(wstringToUtf8(value.fileName).c_str()).ToLocalChecked());

					 curObj->Set(Nan::New("lineText").ToLocalChecked(),
								 Nan::New(wstringToUtf8(value.lineText).c_str()).ToLocalChecked());

					 curObj->Set(Nan::New("Text").ToLocalChecked(),
								 Nan::New(wstringToUtf8(value.Text).c_str()).ToLocalChecked());

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
