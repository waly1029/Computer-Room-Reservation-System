#include <iostream>
#include <fstream>
#include <string>
#include "Identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
using namespace std;

// 进入管理员子菜单界面
void managerMenu(Identity* &manager) {
    while (true)
    {
        // 调用管理员子菜单
        manager->operMenu();

        // 父类指针 转换为子类指针
        Manager* man = (Manager*) manager;

        int select = 0;
        cin >> select;

        switch (select)
        {
        // 添加账号
        case 1:
            cout << "添加账号" << endl;
            man->addPerson();
            break;
        // 查看账号
        case 2:
            cout << "查看账号" << endl;
            man->showPerson();
            break;
        // 查看机房
        case 3:
            cout << "查看机房" << endl;
            man->showComputer();
            break;
        // 清空文件
        case 4:
            cout << "清空预约" << endl;
            man->clearFile();
            break;
        // 注销
        case 0:
            // 销毁堆区对象
            delete man;
            cout << "注销成功" << endl;
            cout << "按任意键继续..." << endl;
            getchar();
            getchar();
            system("clear");
            return;
        }
    }
    
}

// 登录功能
void Login(string fileName, int type) {

    Identity* person = nullptr;

    ifstream ifs;
    ifs.open(fileName, ios::in);

    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    // 接受用户信息
    int id = 0;
    string name;
    string pwd;

    // 判断身份
    if(type==1) {
        cout << "请输入学号:" << endl;

        // 判断是否为数字，防止意外发生
        while(!(cin>>id)) {
            cout << "输入有误，请重新输入学号:" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //忽略无效输入
        }
    } else if (type==2) {
        cout << "请输入职工号:" << endl;
        
        // 判断是否为数字，防止意外发生
        while(!(cin>>id)) {
            cout << "输入有误，请重新输入职工号:" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //忽略无效输入
        }
    }

    cout << "请输入用户名:" << endl;
    cin >> name;
    cout << "请输入密码:" << endl;
    cin >> pwd;

    if(type==1) {
        // 学生身份验证

        // 文件中获取信息
        int fId;
        string fName;
        string fPwd;

        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            // cout << fId << endl;
            // cout << fName << endl;
            // cout << fPwd << endl;
            // cout << endl;
            if(fId==id && fName==name && fPwd==pwd) {
                cout << "登录验证成功..." << endl;
                getchar();
                getchar();
                system("clear");
                person = new Student(id, name, pwd);
                // person = new Student(fId, fName, fPwd);

                // 进入学生身份子菜单

                return;
            }
        }
        

    } else if(type==2) {
        // 老师身份验证

        // 文件中获取信息
        int fId;
        string fName;
        string fPwd;

        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            // cout << fId << endl;
            // cout << fName << endl;
            // cout << fPwd << endl;
            // cout << endl;
            if(fId==id && fName==name && fPwd==pwd) {
                cout << "登录验证成功..." << endl;
                getchar();
                getchar();
                system("clear");
                person = new Teacher(id, name, pwd);
                // person = new Teacher(fId, fName, fPwd);

                // 进入教师子菜单

                return;
            }
        }

    } else if(type==3) {
        // 管理员身份验证

        string fName;
        string fPwd;

        while (ifs >> fName && ifs >> fPwd)
        {
            // cout << fId << endl;
            // cout << fName << endl;
            // cout << fPwd << endl;
            // cout << endl;
            if(fName==name && fPwd==pwd) {
                cout << "登录验证成功..." << endl;
                cout << "按任意键继续..." << endl;
                getchar();
                getchar();
                system("clear");
                person = new Manager(name, pwd);
                // person = new Teacher(fId, fName, fPwd);

                // 进入管理员菜单
                managerMenu(person);

                return;
            }
        }
    }

    cout << "验证登录失败！" << endl;
    cout << "按任意键继续..." << endl;

    getchar();
    getchar();
    system("clear");
    return;
    
}

int main() {

    // 接收选择
    int select = 0;

    while(true) {
        cout << "====================    欢迎来到机房预约系统    ====================" << endl;
        cout << endl;
        cout << endl << "请输入您的身份" << endl;
        cout << "\t\t  ------------------------------\n";
        cout << "\t\t |                              |\n";
        cout << "\t\t |          1.学生代表          |\n";
        cout << "\t\t |                              |\n";
        cout << "\t\t |          2.老   师           |\n";
        cout << "\t\t |                              |\n";
        cout << "\t\t |          3.管 理 员          |\n";
        cout << "\t\t |                              |\n";
        cout << "\t\t |          0.退   出           |\n";
        cout << "\t\t |                              |\n";
        cout << "\t\t  ------------------------------\n";
        cout << "输入您的选择：";

        cin >> select;

        switch (select)
        {
        // 退出系统
        case 0:
            cout << "👏🏻欢迎下次使用" << endl;
            getchar();
            getchar();
            return 0;
            break;
        // 学生身份
        case 1:
            Login(STUDENT_FILE, 1);
            break;
        // 老师身份
        case 2:
            Login(TEACHER_FILE, 2);
            break;
        // 管理员身份
        case 3:
            Login(ADMIN_FILE, 3);
            break;
        // 输入有误
        default:
            cout << "输入错误，请重新选择！" << endl;
            getchar();
            getchar();
            system("clear");
            break;
        }
    }

    cin.get();

    return 0;
}