//
// Created by serg on 10/25/16.
//

#include "cppFileSearch.h"

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

int findInFiles(const path &dir_path, wregex &reg, vector<occurrence> &res, int limit)
{
    const recursive_directory_iterator end;
    int files = 0;
    const auto it = find_if(recursive_directory_iterator(dir_path), end,
                            [&reg, &res, &files, limit](const directory_entry &e)
                            {
                                if (limit != -1 && res.size() >= limit)
                                    return true;
                                if (boost::filesystem::is_directory(e.path()))
                                    return false;
                                if (boost::filesystem::file_size(e.path()) > max_file_size)
                                    return false;
                                //cout << boost::filesystem::file_size(e.path()) << endl;
                                boost::filesystem::wifstream fin(e.path());
                                vector<occurrence> cur{};
                                findInFile(fin, e.path().wstring(), reg, cur);
                                res.insert(res.end(), cur.begin(), cur.end());
                                files++;
                                return false;
                            });
    return files;
}