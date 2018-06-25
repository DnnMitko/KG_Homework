#include "XML_Wrapper.h"

XML_Wrapper::XML_Wrapper() {
    if( false == Init() ) {
        exit(-1);
    }
}

XML_Wrapper::~XML_Wrapper() {
    Deinit();
}

int XML_Wrapper::ReadInt( string node ) const {
    return settingsFile->first_child().child( node.c_str() ).text().as_int();
}

int XML_Wrapper::ReadInt( string nodeParent, string nodeChild ) const {
    return settingsFile->first_child().child( nodeParent.c_str() ).child( nodeChild.c_str() ).text().as_int();
}

string XML_Wrapper::ReadString( string node ) const {
    return settingsFile->first_child().child( node.c_str() ).text().as_string();
}

string XML_Wrapper::ReadString( string nodeParent, string nodeChild ) const {
    return settingsFile->first_child().child( nodeParent.c_str() ).child( nodeChild.c_str() ).text().as_string();
}

bool XML_Wrapper::Init() {
    bool hasProblem = false;

    settingsFile = new pugi::xml_document();
    if( NULL == settingsFile->load_file( "constants/Constants.xml" ) ) {
        printf( "Couldn't load constants from xml!\n" );
        hasProblem = true;
    }

    return hasProblem;
}

void XML_Wrapper::Deinit() {
    delete settingsFile;
    settingsFile = NULL;
}

