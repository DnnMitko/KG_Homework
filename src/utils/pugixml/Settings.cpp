#include "Settings.h"

XML_Wrapper* Settings::singleton = NULL;

Settings::Settings() {
}

Settings::~Settings() {
}

XML_Wrapper* Settings::getInstance() {
    if( NULL == singleton ) {
        singleton = new XML_Wrapper();
    }

    return singleton;
}