#include "orderFile.h"

// 构造函数
OrderFile::OrderFile() {
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);
    if(!ifs.is_open())
        cout << "打开文件失败..." << endl;

    string date;
    string interval;
    string stuId;
    string stuName;
    string roomId;
    string status;

    this->m_Size = 0;

    while (ifs>>date && ifs>>interval && ifs>>stuId && 
            ifs>>stuName && ifs>>roomId && ifs>>status)
    {
        // cout << date << endl;
        // cout << interval << endl;
        // cout << stuId << endl;
        // cout << stuName << endl;
        // cout << roomId << endl;
        // cout << status << endl;
        // cout << endl;

        // date:1
        string key;
        string value;
        map<string, string> m;

        int pos = date.find(":");
        if(pos!=-1) {
            key = date.substr(0, pos);
            value = date.substr(pos+1, date.size()-pos-1);
            m[key] = value;
        }
        pos = interval.find(":");
        if(pos!=-1) {
            key = interval.substr(0, pos);
            value = interval.substr(pos+1, interval.size()-pos-1);
            m[key] = value;
        }
        pos = stuId.find(":");
        if(pos!=-1) {
            key = stuId.substr(0, pos);
            value = stuId.substr(pos+1, stuId.size()-pos-1);
            m[key] = value;
        }
        pos = stuName.find(":");
        if(pos!=-1) {
            key = stuName.substr(0, pos);
            value = stuName.substr(pos+1, stuName.size()-pos-1);
            m[key] = value;
        }
        pos = roomId.find(":");
        if(pos!=-1) {
            key = roomId.substr(0, pos);
            value = roomId.substr(pos+1, roomId.size()-pos-1);
            m[key] = value;
        }
        pos = status.find(":");
        if(pos!=-1) {
            key = status.substr(0, pos);
            value = status.substr(pos+1, status.size()-pos-1);
            m[key] = value;
        }
        
        this->m_orderDate[this->m_Size] = m;
        this->m_Size++;
    }
    
    ifs.close();

    // 测试
    // for(auto it=m_orderDate.begin(); it!=m_orderDate.end(); ++it) {
    //     for(auto i=it->second.begin(); i!=it->second.end(); ++i) {
    //         cout << "key:" << i->first << "\tvalue:" << i->second << "\t";
    //     }
    //     cout << endl;
    // }
}

// 更新预约记录
void OrderFile::updateOrder() {
    if(this->m_Size==0)
        return;

    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
    for(int i=0; i<this->m_Size; ++i) {
        ofs << "date:" << this->m_orderDate[i]["date"] << " ";
        ofs << "interval:" << this->m_orderDate[i]["interval"] << " ";
        ofs << "stuId:" << this->m_orderDate[i]["stuId"] << " ";
        ofs << "stuName:" << this->m_orderDate[i]["stuName"] << " ";
        ofs << "roomId:" << this->m_orderDate[i]["roomId"] << " ";
        ofs << "status:" << this->m_orderDate[i]["status"] << endl;
    }

    ofs.close();
}