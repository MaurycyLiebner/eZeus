#ifndef EGAMEDIR_H
#define EGAMEDIR_H

#include <string>

class eGameDir {
public:
    static void initialize();
    static std::string path(const std::string& path);
private:
    static std::string sPath;
};

#endif // EGAMEDIR_H
