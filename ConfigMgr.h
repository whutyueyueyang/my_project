#pragma once
#include"const.h"
//考虑到可能需要在其他的类中去使用该配置文件管理类，
// 故而将其声明为单例。
// 那么在哪我就都能用到这个封装了配置文件的类
struct SectionInfo {
    SectionInfo() {}
    ~SectionInfo() {
        _section_datas.clear();
    }

    SectionInfo(const SectionInfo& src) {
        _section_datas = src._section_datas;
    }

    SectionInfo& operator = (const SectionInfo& src) {
        if (&src == this) {
            return *this;
        }

        this->_section_datas = src._section_datas;
    }

    std::map<std::string, std::string> _section_datas;
    std::string  operator[](const std::string& key) {
        if (_section_datas.find(key) == _section_datas.end()) {
            return "";
        }
        // 这里可以添加一些边界检查  
        return _section_datas[key];
    }
};
class ConfigMgr
{
public:
    ~ConfigMgr() {
        _config_map.clear();
    }
    SectionInfo operator[](const std::string& section) {
        if (_config_map.find(section) == _config_map.end()) {
            return SectionInfo();
        }
        return _config_map[section];
    }


    ConfigMgr& operator=(const ConfigMgr& src) {
        if (&src == this) {
            return *this;
        }

        this->_config_map = src._config_map;
    };

    ConfigMgr(const ConfigMgr& src) {
        this->_config_map = src._config_map;
    }

   static ConfigMgr& Inst() {
        static ConfigMgr cfg_mgr;
        return cfg_mgr;
    }//保证多线程的情况下安全访问一个cfg。
private:
    ConfigMgr();
    // 存储section和key-value对的map  
    std::map<std::string, SectionInfo> _config_map;
};

