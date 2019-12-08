#ifndef PERSONAL_INFO_HPP
#define PERSONAL_INFO_HPP
#include "qstringlist.h"
#include "qstring.h"

// Configure the data, then rename the file to personal_info
namespace PERSONAL
{
    const QString REMOTE_URL = "AUTOREMOTE_URL";
    const QStringList URLS = {
        "GOOSE", "GOOSE", "GOOSE",
        "GOOSE", "DUCK" , "GOOSE",
        "GOOSE", "GOOSE", "GOOSE"
    };
}

#endif // PERSONAL_INFO_HPP
