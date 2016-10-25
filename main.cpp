#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/optional.hpp>
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

void findInFile(boost::filesystem::wifstream &stream, wstring filename, wregex &reg, vector<occurrence> &res)
{
    //vector<occurrence> res{};
    res = vector<occurrence>();
    wstring line;
    int lineNum = 0;
    std::wsregex_iterator(line.begin(), line.end(), reg);



    while (std::getline(stream, line))
    {
        for (auto it = std::wsregex_iterator(line.begin(), line.end(), reg);
             it != std::wsregex_iterator(); ++it)
        {

            res.push_back(occurrence(filename, line, it->str(), lineNum, it->position()));
            //cout << it->str() << endl;
            //index_matches.push_back(it->position());
        }
        lineNum++;

    }
    //cout <<"here"<<endl;
}

optional<path> findInFiles(const path &dir_path, wregex &reg, vector<occurrence> &res)
{
    const recursive_directory_iterator end;
    const auto it = find_if(recursive_directory_iterator(dir_path), end,
                            [&reg, &res](const directory_entry &e)
                            {
                                cout << e.path().string() << endl;
                                boost::filesystem::wifstream fin(e.path());
                                vector<occurrence> cur{};
                                findInFile(fin, e.path().wstring(), reg, cur);
                                /*for (int i = 0; i < cur.size(); i++) {
                                    cout << cur[i].fileName << endl;
                                    cout << cur[i].toString() << endl;
                                }*/

                                res.insert(res.end(), cur.begin(), cur.end());

                                return false;
                            });
    return it == end ? optional<path>() : it->path();
}

int main()
{

    const path myPath = L"/home/serg/cpp";
    wregex reg(L"include");
    vector<occurrence> res{};
    findInFiles(myPath, reg, res);

    for (int i = 0; i < res.size(); i++)
    {
        cout << "filename: " << res[i].fileName << endl;
        cout << "line text: " << res[i].lineText << endl;
        cout << "found text: " << res[i].Text << endl;
        cout << "line number: " << res[i].line << endl;
        cout << "position: " << res[i].position << endl;

        cout << endl;
    }
    cout << "overall " << res.size() << endl;
    /*wstring str = L"տէստ տէստ ";
    wregex rx(L"ստ");

    vector<int> index_matches; // results saved here
    // (should be {2, 8}, but always get only {2})


    for (auto it = std::wcregex_iterator(str.c_str(), str.c_str() + sizeof(wchar_t) * str.size(), rx);
         it != std::wcregex_iterator();
         ++it) {
        cout << it->str() << endl;
        index_matches.push_back(it->position());
    }
    for (int i = 0; i < index_matches.size(); i++)
        cout << index_matches[i] << " ";
    cout << endl;*/



}