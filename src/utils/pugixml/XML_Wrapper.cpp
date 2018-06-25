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
    return global.GetSettings()File->first_child().child( node.c_str() ).text().as_int();
}

int XML_Wrapper::ReadInt( string nodeParent, string nodeChild ) const {
    return global.GetSettings()File->first_child().child( nodeParent.c_str() ).child( nodeChild.c_str() ).text().as_int();
}

string XML_Wrapper::ReadString( string node ) const {
    return global.GetSettings()File->first_child().child( node.c_str() ).text().as_string();
}

string XML_Wrapper::ReadString( string nodeParent, string nodeChild ) const {
    return global.GetSettings()File->first_child().child( nodeParent.c_str() ).child( nodeChild.c_str() ).text().as_string();
}

bool XML_Wrapper::Init() {
    bool hasProblem = false;

    global.GetSettings()File = new pugi::xml_document();
    if( 0 == global.GetSettings()File->load_file( "../../../constants/Constants.xml" ) ) {
        printf( "Couldn't load constants from xml!\n" );
        hasProblem = true;
    }

    return hasProblem;
}

void XML_Wrapper::Deinit() {
    delete global.GetSettings()File;
    global.GetSettings()File = NULL;
}