#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "XML_Wrapper.h"

class Settings {
public:
    Settings();
    ~Settings();
public:
    static XML_Wrapper* getInstance();
private:
    static XML_Wrapper* singleton;
};

#endif //__SETTINGS_H__