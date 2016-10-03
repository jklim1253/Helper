#include "stdafx.h"
#include "Config.h"

struct CONFIG {
    int width;
    int height;
};

class ConfigImpl {
public :
    ConfigImpl() : filename(_T("config.ini")) {
    }
    int load() {
        INIHelper ini;
        ini.useFile(_T("config.ini"));
        {
            ini.useSection(_T("window"));
            {
                int cx = ::GetSystemMetrics(SM_CXSCREEN)/2;
                int cy = ::GetSystemMetrics(SM_CYSCREEN)/2;

                config.width = ini.GetValue(_T("width"), cx);
                config.height = ini.GetValue(_T("height"), cy);
            }
        }

        return CONFIG_NO_ERROR;
    }
    int save() {
        INIHelper ini;
        ini.useFile(_T("config.ini"));
        {
            ini.useSection(_T("window"));
            {
                ini.SetValue(_T("width"), config.width);
                ini.SetValue(_T("height"), config.height);
            }
        }

        return CONFIG_NO_ERROR;
    }
    int& operator[](const std::tstring& key) {
        if (key == std::tstring(_T("width"))) {
            return config.width;
        }
        else if (key == std::tstring(_T("height"))) {
            return config.height;
        }

        static int err = 0;

        return err;
    }
private :
    const std::tstring filename;
    CONFIG config;
};

_Config::_Config()
: impl(new ConfigImpl) {
}
_Config::~_Config() {
    if (impl) {
        delete impl;
        impl = 0;
    }
}
int _Config::load() {
    return impl->load();
}
int _Config::save() {
    return impl->save();
}
int _Config::update(const std::tstring& key, const int& value) {
    (*impl)[key] = value;

    return CONFIG_NO_ERROR;
}
int& _Config::operator[](const std::tstring& key) {
    return (*impl)[key];
}
