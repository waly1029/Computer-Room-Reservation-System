#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include "globalFile.h"
using namespace std;

class OrderFile {
public:
    // 构造函数
    OrderFile();

    // 更新预约记录
    void updateOrder();

    // 记录的容器 key-记录条数 value-记录键对值（每行信息）
    map<int, map<string, string>> m_orderDate;

    int m_Size = 0;
};