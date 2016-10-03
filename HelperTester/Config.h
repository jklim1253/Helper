#pragma once

class ConfigImpl;
class _Config : public singleton<_Config> {
    friend class singleton<_Config>;
public :
    int load();
    int save();

    int update(const std::tstring& key, const int& value);
    int& operator[](const std::tstring& key);

private :
    _Config();
    ~_Config();
private :
    ConfigImpl* impl;
};

#define Config (_Config::Reference())