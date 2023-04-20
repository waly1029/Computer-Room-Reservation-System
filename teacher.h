#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Identity.h"
#include<iostream>
using namespace std;

class Teacher: public Identity {
public:
    // 默认构造
    Teacher();

    // 有参构造
    Teacher(int empId, string name, string pwd);

    // 菜单界面
    virtual void operMenu();

    // 查看所有预约
    void showAllOrder();

    // 审核预约
    void validOrder();

    int m_EmpId;
};
