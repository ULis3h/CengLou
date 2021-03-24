#include "csetting.h"

csetting::csetting(const std::string &filename)
{
    FileStorage setting_fs(filename,FileStorage::READ);
    read(setting_fs);
    setting_fs.release();
}

void csetting::read(const FileStorage &fileSet)
{
    fileSet["mode"] >> c_mode;
    fileSet["c_saveResult"] >> c_saveResult;
}

void csetting::write(FileStorage &fs)const
{
    cvWriteComment(*fs, "\n BASE Config",0);
    fs <<"c_mode" << c_mode;
    fs << "c_saveResult" << c_saveResult;
}
