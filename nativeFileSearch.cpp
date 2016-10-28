#include "SearchWorker.h"

#include <nan.h>
//#include "node_modules/nan/nan.h"
#include <functional>
#include <iostream>
#include <cmath>


void RunCallback(const Nan::FunctionCallbackInfo<v8::Value> &info)
{
    v8::String::Utf8Value param0(info[0]->ToString());
    v8::String::Utf8Value param1(info[1]->ToString());

    std::string pathStr = std::string(*param0);//16 bit chars wont work reimplement!
    std::string regStr = std::string(*param1);

    std::wstring pathWStr = std::wstring(pathStr.begin(), pathStr.end());//not good reimplement
    std::wstring regWStr = std::wstring(regStr.begin(), regStr.end());//not good reimplement

    int limit = -1;
    Callback *callback;

    int lastIndex = 2;
	bool caseSensitive = true;

	if (info[lastIndex]->IsBoolean())
	{
		caseSensitive = info[lastIndex]->IsTrue();
		lastIndex++;
	}
    if (info[lastIndex]->IsNumber())
    {
        limit = info[lastIndex]->NumberValue();
		lastIndex++;
    }

	callback = new Callback(info[lastIndex].As<Function>());

    AsyncQueueWorker(new SearchWorker(callback, pathWStr, regWStr, limit, caseSensitive));
}

void Init(v8::Local <v8::Object> exports, v8::Local <v8::Object> module)
{
    Nan::SetMethod(module, "exports", RunCallback);
}


NODE_MODULE(addon, Init
)