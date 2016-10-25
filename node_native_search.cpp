#include <nodejs/src/node.h>
#include <nodejs/deps/v8/include/v8.h>
#include "cpp_file_search.h"
#include <string>

using namespace v8;

std::wstring GetWString(v8::Handle<v8::String> str)
{
    uint16_t *buf = new uint16_t[str->Length() + 1];
    str->Write(buf);
    //str->Write()
    std::wstring value = reinterpret_cast<wchar_t *>(buf);
    delete[] buf;

    return value;
}

void Method(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    v8::Isolate *isolate = args.GetIsolate();
    v8::HandleScope scope(isolate);

    if (args.Length() < 2)
    {
        isolate->ThrowException(v8::Exception::TypeError(
                v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    v8::String::Utf8Value param0(args[0]->ToString());
    v8::String::Utf8Value param1(args[1]->ToString());

    std::string pathStr = std::string(*param0);//16 bit chars wont work reimplement!
    std::string regStr = std::string(*param1);
    std::wstring regWStr = std::wstring(regStr.begin(), regStr.end());//not good reimplement
    //std::wstring pathStr = GetWString(dir);

    const path myPath = pathStr;
    wregex reg(regWStr);
    vector<occurrence> res{};//not good do some v8 stuff or something idk

    findInFiles(myPath, reg, res);


    Handle<Array> resArray = Array::New(isolate, res.size());


    for (int i = 0; i < res.size(); i++)
    {
        Local<Object> curObj = Object::New(isolate);
        {
            std::string tmp(res[i].fileName.begin(), res[i].fileName.end());

            curObj->Set(String::NewFromUtf8(isolate, "fileName"),
                        v8::String::NewFromUtf8(isolate, tmp.c_str()));
        }

        {
            std::string tmp(res[i].lineText.begin(), res[i].lineText.end());
            curObj->Set(String::NewFromUtf8(isolate, "lineText"),
                        v8::String::NewFromUtf8(isolate, tmp.c_str()));
        }
        {
            std::string tmp(res[i].Text.begin(), res[i].Text.end());
            curObj->Set(String::NewFromUtf8(isolate, "Text"),
                        v8::String::NewFromUtf8(isolate, tmp.c_str()));
        }
        curObj->Set(String::NewFromUtf8(isolate, "line"),
                    Number::New(isolate, res[i].line));

        curObj->Set(String::NewFromUtf8(isolate, "position"),
                    Number::New(isolate, res[i].position));

        resArray->Set(Number::New(isolate, i), curObj);
    }

    //resObj->Set(String::NewFromUtf8(isolate, "msg"), args[0]->ToString());

    //args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, data.c_str()));
    args.GetReturnValue().Set(resArray);
}

void init(v8::Local<v8::Object> exports)
{
    NODE_SET_METHOD(exports, "native_file_search", Method);
}

NODE_MODULE(binding, init
);