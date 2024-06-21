#ifndef EPATHBOARD_H
#define EPATHBOARD_H

#include <vector>

class ePathBoard {
public:
    ePathBoard() {}
    ePathBoard(const int x, const int y,
               const int w, const int h);

    bool getAbsValue(const int x, const int y, int** value);
    bool getAbsValue(const int x, const int y, int& value) const;
private:
    bool getDAbsValue(const int x, const int y, int** value);
    bool getDAbsValue(const int x, const int y, int& value) const;

    int mX;
    int mY;
    int mW;
    int mH;
    std::vector<std::vector<int>> mData;
};

#endif // EPATHBOARD_H
