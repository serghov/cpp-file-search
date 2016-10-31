//
// Created by serg on 10/25/16.
//

#include "cppFileSearch.h"

void
findInFile(std::wifstream &stream, const wstring filename, const wregex &reg, vector<occurrence> &res,
           bool multiline)
{
    //vector<occurrence> res{};
    res = vector<occurrence>();

    auto findAll = [&res, &filename, &reg](wstring &text, int lineNum) //reimplement somehow with default arguments?
    {
        std::wsregex_iterator(text.begin(), text.end(), reg);
        for (auto it = std::wsregex_iterator(text.begin(), text.end(), reg);
             it != std::wsregex_iterator(); ++it)
        {
            res.push_back(occurrence(filename, text, it->str(), lineNum, it->position()));
            //doesnt work well with multiline search
            //maybe we need to include the first line num

        }
    };
    //read bom from files to check type then to processing
    //will probably slow down everything
    //maybe do this with a flag?
    if (multiline)
    {
        /*wstring text;
        string tmp((std::istreambuf_iterator<char>(stream)),
                   std::istreambuf_iterator<char>());
        text = wstring(tmp.begin(), tmp.end());
        findAll(text, -1);*/
    } else
    {
        int lineNum = 0;
        wstring line;
        while (std::getline(stream, line))
        {
            findAll(line, lineNum);
            lineNum++;
        }

    }

    //cout <<"here"<<endl;
}

int findInFiles(const bf::path &dir_path, const wregex &reg, vector<occurrence> &res, int limit)
{
    const bf::recursive_directory_iterator end;
    int files = 0;
    const auto it = find_if(bf::recursive_directory_iterator(dir_path), end,
                            [&reg, &res, &files, limit](const bf::directory_entry &e)
                            {
                                if (limit != -1 && res.size() >= limit)
                                    return true;
                                if (bf::is_directory(e.path()))
                                    return false;
                                uintmax_t fileSize = 0;
                                try
                                {
                                    fileSize = bf::file_size(e.path());
                                }
                                catch (std::exception e)
                                {
                                    return false;
                                }

                                if (fileSize == 0 || fileSize > max_file_size)
                                    return false;
                                //cout << boost::filesystem::file_size(e.path()) << endl;
                                bf::wifstream fin(e.path());//using bf here instead of std to work with path, not the best solution
                                fin.imbue(std::locale("en_US.UTF-8"));
                                vector<occurrence> cur{};
                                findInFile(fin, e.path().wstring(), reg, cur);
                                res.insert(res.end(), cur.begin(), cur.end());
                                files++;
                                return false;
                            });
    return files;
}

wstring escapeRegex(const wstring &str)
{
    static const wregex re_RegexEscape(L"[\\-\\[\\]\\/\\{\\}\\(\\)\\*\\+\\?\\.\\\\\\^\\$\\|]");
    const wstring rep(L"\\&");
    wstring result = regex_replace(str, re_RegexEscape, rep,
                                   std::regex_constants::match_default | std::regex_constants::format_sed);
    return result;
    //write tests for this, not sure if works every time
}

wstring utf8ToWstring(const string &str)
{
    wstring_convert<codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(str);
}

string wstringToUtf8 (const wstring& str)
{
    wstring_convert<codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(str);
}