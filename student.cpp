#include "student.h"

// 默认构造
Student::Student() {

}

// 有参构造
Student::Student(int id, string name, string pwd) {
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    // 初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    if(!ifs.is_open())
        cout << "文件打开失败..." << endl;
    
    ComputerRoom com;
    while (ifs>>com.m_comId && ifs>>com.m_maxNum)
    {
        m_com.push_back(com);
    }
    ifs.close();
    
}

// 菜单界面 父类的纯虚函数
void Student::operMenu() {
    cout << "欢迎学生代表：" << this->m_Name << "登录..." << endl;
    cout << "\t\t ----------------------------------------\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                1.申请预约              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                2.查看我的预约          |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                3.查看所有预约          |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                4.取消预约              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                0.注销登录              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t ----------------------------------------\n";
    cout << "请选择操作:  " << endl;
}

// 申请预约
void Student::applyOrder() {
    cout << "机房预约时间为周一至周五：" << endl;
    cout << "请输入申请预约时间：" << endl;
    cout << "1. 周一" << endl;
    cout << "2. 周二" << endl;
    cout << "3. 周三" << endl;
    cout << "4. 周四" << endl;
    cout << "5. 周五" << endl;

    int date = 0;
    int interval = 0; // 时间段
    int room = 0; // 机房编号

    while (true)
    {
        cin >> date;
        if(date>=1 && date<=5)
            break;
        else
            cout << "输入有误，请重新输入..." << endl;
    }
    
    cout << "请输入申请预约时间段：" << endl;
    cout << "1. 上午" << endl;
    cout << "2. 下午" << endl;

    while (true)
    {
        cin >> interval;
        if(interval>=1 && interval<=2)
            break;
        else
            cout << "输入时间段有误，请重新输入..." << endl;
    }

    cout << "请选择机房：" << endl;
    for(int i=0; i<m_com.size(); ++i)
        cout << m_com[i].m_comId << "号机房容量为：" << m_com[i].m_maxNum << endl;
    while (true)
    {
        cin >> room;
        if(room>=1 && room<=m_com.size())
            break;
        else
            cout << "输入机房号有误，请重新输入..." << endl;
    }
    
    cout << "预约成功，审核中..." << endl;
    cout << "请按任意键继续..." << endl;

    // 写入order.md文件
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);

    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->m_Id << " ";
    ofs << "stuName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << " " << endl;

    ofs.close();
    getchar();
    getchar();
    system("clear");

}
// 查看自身预约
void Student::showMyOrder() {
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
        if(this->m_Id==stoi(of.m_orderDate[i]["stuId"])){
            cout << "预约日期： 周" << of.m_orderDate[i]["date"];
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
    }

    cout << "请按任意键继续..." << endl;
    getchar();
    getchar();
    system("clear");
    
}
// 查看所有预约
void Student::showAllOrder() {
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
// 取消预约
void Student::cancelOrder() {
    OrderFile of;

    if(of.m_Size==0) {
        cout << "无预约记录..." << endl;
        cout << "按任意键继续..." << endl;
        getchar();
        getchar();
        system("clear");
        return;
    }

    cout << "审核中或预约成功的记录可以取消，请输入取消的记录..." << endl;
    vector<int> vOrderIndex;
    int index = 1;
    for(int i=0; i<of.m_Size; ++i) {
        if(stoi(of.m_orderDate[i]["stuId"]) == this->m_Id) {
            if(of.m_orderDate[i]["status"]=="1" ||of.m_orderDate[i]["status"]=="2") {
                vOrderIndex.push_back(i);
                cout << index++ << ": ";
                cout << "  学生姓名： " << of.m_orderDate[i]["stuName"];
                cout << " 学号： " << of.m_orderDate[i]["stuId"];
                cout << " 机房：" << of.m_orderDate[i]["roomId"];
                cout << " 预约日期： 周" << of.m_orderDate[i]["date"];
                string s = stoi(of.m_orderDate[i]["interval"])==1?"上午":"下午";
                cout << " 时间段： " << s;
                string status = " 状态： ";
                if(of.m_orderDate[i]["status"]=="1")
                    status += "审核中";
                else if(of.m_orderDate[i]["status"]=="2")
                    status += "预约成功";
                cout << status << endl;
            }
        }
    }

    cout << "请输入取消的记录， 0代表返回..." << endl;
    int select = 0;

    while (true)
    {
        cin >> select;
        if(select>=0 && select<=vOrderIndex.size()) {
            if(select==0)
                break;
            else {
                of.m_orderDate[vOrderIndex[select-1]]["status"] = "0";
                of.updateOrder();
                cout << "已取消预约" << endl;
                break;
            }
        }
        else
            cout << "输入有误，请重新输入..." << endl;
    }
    
    cout << "请按任意键继续..." << endl;
    getchar();
    getchar();
    system("clear");

}