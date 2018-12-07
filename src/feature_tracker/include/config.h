#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "my_include.h"


class Config
{
private:
    static shared_ptr<Config> config;
    cv::FileStorage file;
    Config();
public:
    ~Config();
    // open the parameterfile used 
    static void Open_ParameterFile(const string& filename);
    template <typename T>
    // get the parameter values from file
    static T get(const string& key)
    {
        return T(Config::config->file[key]);
    }
};



#endif 