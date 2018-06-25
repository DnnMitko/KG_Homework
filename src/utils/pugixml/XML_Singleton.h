#ifndef __XML_SINGLETON_H__
#define __XML_SINGLETON_H__

#include "XML_Wrapper.h"

class XML_Singleton {
public:
    XML_Singleton();
    ~XML_Singleton();
public:
    static XML_Wrapper* getSettings();
private:
    static XML_Wrapper* Settings;
}

#endif //__XML_SINGLETON_H__