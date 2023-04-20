#include "manager.h"

// 默认构造
Manager::Manager() {

}

// 有参构造 姓名 密码
Manager::Manager(string name, string pwd) {
    this->m_Name = name;
    this->m_Pwd = pwd;

    // 初始化容器并获取信息
    this->initVector();

    // 初始化 处理机房信息内容
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    if(!ifs.is_open()) {
        cout << "文件打开失败..." << endl;
        return;
    }

    ComputerRoom com;
    while (ifs>>com.m_comId && ifs>>com.m_maxNum)
    {
        vComR.push_back(com);
    }
    ifs.close();
    cout << "机房数量：" << vComR.size() << endl;
    
}

// 选择菜单
void Manager::operMenu() {
    cout << "欢迎管理员：" << this->m_Name << "登录..." << endl;
    cout << "\t\t ----------------------------------------\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                1.添加账号              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                2.查看账户              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                3.查看机房              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                4.清空预约              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t|                0.注销登录              |\n";
    cout << "\t\t|                                        |\n";
    cout << "\t\t ----------------------------------------|\n";
    cout << "请选择操作:  " << endl;
}

// 添加账号
void Manager::addPerson() {
    cout << "请输入添加账号的类型" << endl;
    cout << "1. 添加学生" << endl;
    cout << "2. 添加教师" << endl;

    string fName;
    string tip;    // 提示id号
    string errorTip;    // 重复错误提示

    ofstream ofs;

    // 清空输入缓冲区
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int select = 0;
    cin >> select;

    if(select==1) {
        // 添加学生
        fName = STUDENT_FILE;
        tip = "请输入学号:";
        errorTip = "学号重复，请重新输入";
    }
    else if(select==2) {
        // 添加教师
        fName = TEACHER_FILE;
        tip = "请输入职工号:";
        errorTip = "职工号重复，请重新输入";
    }

    // 利用追加的方式写入文件
    ofs.open(fName, ios::out | ios::app);

    int id;
    string name;
    string pwd;


    // cout << tip << endl;
    // cin >> id;
    cout << tip << endl;
    while (true)
    {
        cin >> id;
        bool ret = checkRepeat(id, select);
        
        if(ret) {
            cout << errorTip << endl;
        } else {
            break;
        }
    }

    cout << "输入姓名：" << endl;
    cin >> name;

    cout << "输入密码：" << endl;
    cin >> pwd;

    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "添加成功..." << endl;

    getchar();
    getchar();
    system("clear");

    ofs.close();

    // 调用初始化容器接口 更新账号信息
    this->initVector();
}

void printStudent(Student& s) {
    cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher& s) {
    cout << "职工号：" << s.m_EmpId << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
// 查看账号
void Manager::showPerson() {
    cout << "请选择查看内容" << endl;
    cout << "1.查看所有学生" << endl;
    cout << "2.查看所有教师" << endl;

    int select = 0;
    cin >> select;

    if(select==1) {
        cout << "所有学生信息如下:" << endl;
        for_each(vStu.begin(), vStu.end(), printStudent);
    } else if(select==2) {
        for_each(vTea.begin(), vTea.end(), printTeacher);
    }

    cout << "请按任意键继续..." << endl;
    getchar();
    getchar();
    system("clear");

    // 最上方更新当前学生 教师人数
    this->initVector();
}

// 查看机房信息
void Manager::showComputer() {
    cout << "机房信息如下：" << endl;

    for(auto it=vComR.begin(); it!=vComR.end(); ++it) {
        cout << "机房编号： " << it->m_comId << " 机房最大机器数量： " << it->m_maxNum << endl;
    }
    cout << "请按任意键继续..." << endl;
    getchar();
    getchar();
    system("clear");
    
}

// 清空预约记录
void Manager::clearFile() {
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "清空成功..." << endl;
    cout << "请按任意键继续..." << endl;
    getchar();
    getchar();
    system("clear");
}

// 初始化容器 防止重复
void Manager::initVector() {
    vStu.clear();
    vTea.clear();

    // 读取信息
    ifstream ifs;
    ifs.open(STUDENT_FILE, ios::in);
    if(!ifs.is_open()) {
        cout << "文件读取失败..." << endl;
        return;
    }
    Student s;
    while(ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Pwd) {
        vStu.push_back(s);
    }
    cout << "当前学生数量:" << vStu.size() << endl;
    ifs.close();

    // 读取信息
    ifs.open(TEACHER_FILE, ios::in);
    if(!ifs.is_open()) {
        cout << "文件读取失败..." << endl;
        return;
    }
    Teacher t;
    while(ifs>>t.m_EmpId && ifs>>t.m_Name && ifs>>t.m_Pwd) {
        vTea.push_back(t);
    }
    cout << "当前教师数量:" << vTea.size() << endl;
    ifs.close();
}

// 检测重复 type 学生 教师
bool Manager::checkRepeat(int id, int type) {
    if(type==1) {
        // 检测学生
        for(auto it = vStu.begin(); it!=vStu.end(); ++it) {
            if(id==it->m_Id)
                return true;
        }
    }
    else if(type==2) {
        // 检测教师
        for(auto it = vTea.begin(); it!=vTea.end(); ++it) {
            if(id==it->m_EmpId)
                return true;
        } 
    }

    return false;
}