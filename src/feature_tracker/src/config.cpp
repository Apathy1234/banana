#include "feature_tracker/config.h"

shared_ptr<Config> Config::config = nullptr;


Config::Config()
{

}

Config::~Config()
{
    if ( file.isOpened() )
    {
        file.release();
    }
}

void Config::Open_ParameterFile(const string& filename)
{
    if ( config == nullptr )
    {
        config = shared_ptr<Config>(new Config);
    }
    config->file = FileStorage(filename.c_str(), FileStorage::READ);
    if ( config->file.isOpened() == false )
    {
        cerr<<"parameter file "<<filename<<" does not exist."<<endl;
        config->file.release();
        return;
    }
}
