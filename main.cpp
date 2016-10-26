#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/optional.hpp>
#include <string>
#include <regex>
#include <fstream>
#include "cppFileSearch.h"

using namespace std;
using namespace boost;
using namespace boost::filesystem;

int main()
{

    const path myPath = L"/home/serg/cpp";
    wregex reg(L"include");
    vector<occurrence> res{};
    int k = findInFiles(myPath, reg, res);

    for (int i = 0; i < res.size(); i++)
    {
        cout << "filename: " << res[i].fileName << endl;
        cout << "line text: " << res[i].lineText << endl;
        cout << "found text: " << res[i].Text << endl;
        cout << "line number: " << res[i].line << endl;
        cout << "position: " << res[i].position << endl;

        cout << endl;
    }
    cout << "looked through " << k << " files, found " << res.size() << " occurrences." << endl;
    return 0;
}