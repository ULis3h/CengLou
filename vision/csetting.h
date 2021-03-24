#ifndef CSETTING_H
#define CSETTING_H

#include <opencv2/core/core.hpp>
#include <string>

using namespace cv;


class csetting
{
public:
    csetting(const std::string &filename);

    void read(const FileStorage&fileSet);
    void write(FileStorage &fs)const;
public:
    int c_mode;       /*0 nothing 1 getface 2 other*/
    int c_saveResult;

};

#endif // CSETTING_H
