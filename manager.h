#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "student.h"
#include "teacher.h"
#include "globalFile.h"
#include "Identity.h"
#include "computerRoom.h"
using namespace std;

class Manager: public Identity{
public:
    // 默认构造
    Manager();

    // 有参构造 姓名 密码
    Manager(string name, string pwd);

    // 选择菜单
    virtual void operMenu();

    // 添加账号
    void addPerson();

    // 查看账号
    void showPerson();

    // 查看机房信息
    void showComputer();

    // 清空预约记录
    void clearFile();

    // 初始化容器
    void initVector();
    // 学生容器
    vector<Student> vStu;
    // 教师容器
    vector<Teacher> vTea;

    // 检测重复 type 学生 教师
    bool checkRepeat(int id, int type);

    // 机房信息
    vector<ComputerRoom> vComR;
};