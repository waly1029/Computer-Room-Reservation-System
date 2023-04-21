#include "teacher.h"

// 默认构造
Teacher::Teacher() {

}

// 有参构造
Teacher::Teacher(int empId, string name, string pwd) {
    this->m_EmpId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;

}

// 菜单界面
void Teacher::operMenu() {
    cout << "欢迎教师：" << this->m_Name << "登录..." << endl;
    cout << "\t\t ----------------------------------------\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                1.查看所有预约          |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                2.审核预约              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                0.注销登录              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t ----------------------------------------\n";
    cout << "请选择操作:  " << endl;
}

// 查看所有预约
void Teacher::showAllOrder() {
    OrderFile of;

    if(of.m_Size==0) {
        cout << "无预约记录..." << endl;
        cout << "按任意键继续..." << endl;
        getchar();
        getchar();
        system("clear");
        return;
    }

    for(int i=0; i<of.m_Size; ++i) {
        cout << i+1 << ". ";
        cout << "学生： " << of.m_orderDate[i]["stuName"];
        cout << "\t学号： " << of.m_orderDate[i]["stuId"];
        cout << "\t预约日期： 周" << of.m_orderDate[i]["date"];
        string s = of.m_orderDate[i]["interval"] == "1" ? "上午":"下午";
        cout << "\t时间段： " << s;
        // cout << "时间段： " << stoi(of.m_orderDate[i]["interval"])==1 ? "上午":"下午";
        cout << "\t机房号：" << of.m_orderDate[i]["roomId"];
        string status = "\t状态：";
        if(of.m_orderDate[i]["status"]=="1")
            status += "审核中";
        else if(of.m_orderDate[i]["status"]=="2")
            status += "预约成功";
        else if(of.m_orderDate[i]["status"]=="-1")
            status += "审核未通过";
        else
            status += "预约已取消";
        cout << status << endl;
    }

    cout << "请按任意键继续..." << endl;
    getchar();
    getchar();
    system("clear");
}

// 审核预约
void Teacher::validOrder() {
    OrderFile of;

    if(of.m_Size==0) {
        cout << "无预约记录..." << endl;
        cout << "按任意键继续..." << endl;
        getchar();
        getchar();
        system("clear");
        return;
    }

    cout << "待审核的预约记录如下：" << endl;
    vector<int> vOrderIndex;
    int index = 1;
    for(int i=0; i<of.m_Size; ++i) {
        if(of.m_orderDate[i]["status"]=="1") {
            vOrderIndex.push_back(i);
            cout << index++ << ": ";
            cout << "  学生姓名： " << of.m_orderDate[i]["stuName"];
            cout << " 学号： " << of.m_orderDate[i]["stuId"];
            cout << " 机房：" << of.m_orderDate[i]["roomId"];
            cout << " 预约日期： 周" << of.m_orderDate[i]["date"];
            string s = stoi(of.m_orderDate[i]["interval"])==1?"上午":"下午";
            cout << " 时间段： " << s;
            string status = " 状态： 审核中";
            cout << status << endl;
        }
    }
    cout << "请输入审核的预约记录，0代表返回..." << endl;
    int select = 0;
    int ret = 0; //接受预约结果记录

    while (true)
    {
        cin >> select;
        if(select>=0 && select<=vOrderIndex.size()) {
            if(select==0)
                break;
            else {
                cout << "请输入审核结果..." << endl;
                cout << "1. 通过" << endl;
                cout << "2. 不通过" << endl;
                cin >> ret;
                if(ret==1) {
                    of.m_orderDate[vOrderIndex[select-1]]["status"] = "2";
                } else {
                    of.m_orderDate[vOrderIndex[select-1]]["status"] = "-1";
                }
                of.updateOrder();
                cout << "审核完毕..." << endl;
                break;
            }
        }
        cout << "输入有误,请重新输入..." << endl;
    }
    cout << "按任意键返回上一层..." << endl;
    getchar();
    getchar();
    system("clear");
}