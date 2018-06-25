#ifndef __XML_WRAPPER_H__
#define __XML_WRAPPER_H__

#include "pugixml.hpp"
#include "string"

using std::string;

class XML_Wrapper {
public:
    XML_Wrapper();
    ~XML_Wrapper();
public:
    int ReadInt( string ) const;
    int ReadInt( string, string ) const;
    string ReadString( string ) const;
    string ReadString( string, string ) const;
private:
    bool Init();
    void Deinit();
private:
    pugi::xml_document* global.GetSettings()File;
};

#endif //__XML_WRAPPER_H__