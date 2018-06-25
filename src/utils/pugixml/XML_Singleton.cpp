#include "XML_Singleton.h"

XML_Wrapper* XML_Singleton::Settings = NULL;

XML_Singleton::XML_Singleton() {
}

XML_Singleton::~XML_Singleton() {
}

XML_Wrapper* XML_Singleton::getSettings() {
    if( NULL == Settings ) {
        Settings = new XML_Wrapper();
    }

    return Settings;
}