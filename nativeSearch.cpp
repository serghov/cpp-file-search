#include "SearchWorker.h"

//#include <nan.h>
#include "node_modules/nan/nan.h"
#include <functional>
#include <iostream>
#include <cmath>


void RunCallback(const Nan::FunctionCallbackInfo<v8::Value> &info)
{
    Local <v8::Object> params = info[0]->ToObject();

    if (!params->Has(Nan::New("root").ToLocalChecked()))
        Nan::ThrowTypeError("No root directory is provided.");

    v8::String::Utf8Value param0(params->Get(Nan::New("root").ToLocalChecked())->ToString());

    if (!params->Has(Nan::New("searchTerm").ToLocalChecked()))
        Nan::ThrowTypeError("No search term is provided.");

    v8::String::Utf8Value param1(params->Get(Nan::New("searchTerm").ToLocalChecked())->ToString());

    std::wstring pathWStr = utf8ToWstring(std::string(*param0));
    std::wstring regWStr = utf8ToWstring(std::string(*param1));

    int limit = -1;


    bool caseSensitive = true, isRegex = true, isMultiline = false;

    if (params->Get(Nan::New("caseSensitive").ToLocalChecked())->IsBoolean())
        caseSensitive = params->Get(Nan::New("caseSensitive").ToLocalChecked())->IsTrue();

    if (params->Get(Nan::New("resultLimit").ToLocalChecked())->IsNumber())
        limit = params->Get(Nan::New("resultLimit").ToLocalChecked())->NumberValue();

    if (params->Get(Nan::New("isRegex").ToLocalChecked())->IsBoolean())
        isRegex = params->Get(Nan::New("isRegex").ToLocalChecked())->IsTrue();

    if (params->Get(Nan::New("multiline").ToLocalChecked())->IsBoolean())
        isMultiline = params->Get(Nan::New("multiline").ToLocalChecked())->IsTrue();

    Callback *callback;
    callback = new Callback(info[1].As<Function>());

    AsyncQueueWorker(new SearchWorker(callback, pathWStr, regWStr, limit, caseSensitive, isRegex));
}

void Init(v8::Local <v8::Object> exports, v8::Local <v8::Object> module)
{
    exports->Set(Nan::New("find").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(RunCallback)->GetFunction());
    //Nan::SetMethod(module, "exports", RunCallback);
}


NODE_MODULE(addon, Init
)