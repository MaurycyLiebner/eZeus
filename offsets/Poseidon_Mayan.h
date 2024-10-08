#include <vector>
#include <utility>

const auto ePoseidon_MayanOffset = std::vector<std::pair<int, int>>{
   {21, 52},
   {14, 50},
   {15, 49},
   {17, 49},
   {15, 49},
   {24, 50},
   {19, 52},
   {19, 52},
   {21, 52},
   {14, 50},
   {15, 49},
   {17, 49},
   {14, 49},
   {24, 50},
   {19, 52},
   {18, 53},
   {19, 52},
   {13, 51},
   {15, 50},
   {18, 49},
   {12, 50},
   {24, 51},
   {20, 52},
   {19, 53},
   {18, 52},
   {11, 51},
   {15, 50},
   {19, 49},
   {13, 50},
   {23, 51},
   {21, 52},
   {19, 52},
   {17, 51},
   {11, 51},
   {15, 50},
   {19, 49},
   {15, 50},
   {20, 51},
   {22, 51},
   {20, 53},
   {15, 51},
   {11, 50},
   {17, 49},
   {19, 49},
   {17, 49},
   {18, 50},
   {21, 51},
   {20, 52},
   {15, 51},
   {12, 50},
   {17, 49},
   {19, 48},
   {17, 49},
   {18, 50},
   {21, 51},
   {20, 52},
   {15, 51},
   {12, 50},
   {17, 49},
   {19, 49},
   {17, 49},
   {18, 50},
   {21, 51},
   {20, 52},
   {17, 51},
   {11, 51},
   {15, 50},
   {19, 49},
   {15, 50},
   {20, 51},
   {22, 51},
   {20, 53},
   {18, 52},
   {11, 51},
   {15, 50},
   {19, 49},
   {13, 50},
   {23, 51},
   {21, 52},
   {20, 52},
   {19, 52},
   {11, 51},
   {15, 50},
   {18, 49},
   {12, 50},
   {24, 51},
   {20, 52},
   {20, 53},
   {21, 52},
   {13, 50},
   {15, 49},
   {17, 49},
   {14, 49},
   {24, 50},
   {19, 52},
   {19, 53},
   {21, 48},
   {20, 52},
   {21, 50},
   {20, 43},
   {20, 44},
   {18, 44},
   {18, 42},
   {18, 38},
   {28, 45},
   {24, 47},
   {19, 48},
   {13, 49},
   {18, 48},
   {15, 47},
   {17, 45},
   {18, 44},
   {16, 46},
   {19, 48},
   {22, 50},
   {17, 49},
   {16, 50},
   {17, 48},
   {12, 46},
   {23, 47},
   {22, 48},
   {13, 46},
   {11, 45},
   {16, 43},
   {16, 45},
   {14, 46},
   {17, 48},
   {21, 50},
   {23, 48},
   {17, 46},
   {8, 43},
   {13, 42},
   {25, 43},
   {31, 46},
   {20, 48},
   {20, 50},
   {22, 48},
   {17, 46},
   {9, 43},
   {15, 42},
   {23, 43},
   {35, 46},
   {27, 48},
   {20, 50},
   {22, 48},
   {16, 46},
   {9, 44},
   {19, 42},
   {15, 44},
   {38, 46},
   {39, 48},
   {21, 49},
   {22, 48},
   {13, 46},
   {11, 45},
   {25, 43},
   {16, 45},
   {32, 46},
   {40, 48},
   {21, 52},
   {20, 50},
   {9, 47},
   {12, 46},
   {22, 45},
   {17, 46},
   {16, 47},
   {24, 50},
   {22, 57},
   {18, 51},
   {9, 49},
   {15, 48},
   {19, 49},
   {16, 48},
   {16, 49},
   {14, 51},
   {23, 52},
   {15, 47},
   {12, 50},
   {17, 53},
   {18, 51},
   {16, 53},
   {17, 50},
   {12, 47},
   {22, 46},
   {22, 46},
   {19, 48},
   {18, 52},
   {16, 50},
   {18, 52},
   {16, 48},
   {15, 46},
   {20, 45},
   {27, 45},
   {24, 47},
   {18, 48},
   {14, 49},
   {18, 48},
   {15, 47},
   {17, 45},
   {19, 44},
   {25, 54},
   {26, 52},
   {15, 51},
   {19, 51},
   {22, 51},
   {15, 52},
   {17, 54},
   {23, 54},
   {25, 54},
   {25, 52},
   {15, 51},
   {19, 51},
   {22, 51},
   {16, 52},
   {16, 54},
   {23, 55},
   {24, 54},
   {22, 53},
   {16, 52},
   {19, 52},
   {23, 52},
   {17, 53},
   {15, 54},
   {22, 55},
   {23, 54},
   {18, 53},
   {16, 52},
   {19, 52},
   {23, 52},
   {19, 53},
   {14, 54},
   {20, 54},
   {20, 53},
   {15, 53},
   {15, 52},
   {19, 51},
   {23, 52},
   {21, 53},
   {12, 53},
   {18, 55},
   {17, 53},
   {15, 52},
   {16, 51},
   {19, 51},
   {23, 51},
   {21, 52},
   {11, 53},
   {17, 54},
   {16, 53},
   {15, 52},
   {17, 51},
   {20, 51},
   {23, 51},
   {22, 52},
   {10, 53},
   {17, 54},
   {17, 53},
   {15, 52},
   {16, 51},
   {19, 51},
   {23, 51},
   {21, 52},
   {11, 53},
   {18, 54},
   {20, 53},
   {15, 53},
   {14, 52},
   {19, 51},
   {23, 52},
   {21, 53},
   {12, 53},
   {18, 55},
   {23, 54},
   {18, 53},
   {14, 52},
   {19, 52},
   {23, 52},
   {19, 53},
   {14, 54},
   {20, 54},
   {25, 54},
   {22, 53},
   {14, 52},
   {19, 52},
   {23, 52},
   {17, 53},
   {15, 54},
   {22, 55},
   {25, 54},
   {25, 52},
   {15, 51},
   {19, 51},
   {22, 51},
   {16, 52},
   {16, 54},
   {23, 55},
   {25, 53},
   {22, 56},
   {18, 54},
   {13, 48},
   {11, 49},
   {10, 48},
   {18, 46},
   {18, 42},
   {16, 53},
   {16, 54},
   {12, 54},
   {16, 55},
   {19, 54},
   {21, 54},
   {14, 53},
   {15, 53},
   {15, 53},
   {17, 54},
   {17, 54},
   {17, 54},
   {17, 54},
   {20, 54},
   {13, 53},
   {15, 53},
   {15, 53},
   {14, 54},
   {28, 53},
   {33, 53},
   {17, 53},
   {19, 54},
   {17, 53},
   {15, 52},
   {14, 53},
   {14, 52},
   {18, 53},
   {30, 54},
   {19, 53},
   {20, 52},
   {25, 53},
   {15, 52},
   {15, 52},
   {14, 52},
   {21, 53},
   {19, 53},
   {20, 53},
   {20, 52},
   {16, 52},
   {13, 52},
   {16, 49},
   {15, 51},
   {16, 52},
   {28, 54},
   {14, 52},
   {19, 51},
   {26, 49},
   {14, 50},
   {15, 48},
   {18, 47},
   {16, 51},
   {19, 54},
   {12, 51},
   {25, 47},
   {29, 48},
   {8, 56},
   {14, 55},
   {19, 49},
   {18, 50},
   {17, 54},
   {16, 50},
   {23, 49},
   {18, 55},
   {6, 57},
   {15, 52},
   {20, 48},
   {19, 51},
   {17, 54},
   {14, 51},
   {22, 48},
   {18, 52},
   {6, 55},
   {16, 49},
   {19, 48},
   {18, 52},
   {16, 55},
   {16, 52},
   {21, 48},
   {19, 49},
   {8, 54},
   {17, 49},
   {17, 51},
   {15, 53},
   {16, 55},
   {18, 53},
   {20, 51},
   {19, 49},
   {11, 51},
   {17, 51},
   {16, 53},
   {13, 55},
   {18, 55},
   {20, 55},
   {21, 53},
   {16, 51},
   {13, 52},
   {0, 0},
};