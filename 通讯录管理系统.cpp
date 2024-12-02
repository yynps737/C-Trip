#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

// 通讯录最大容量常量
const int MAX = 500;

// 定义联系人结构体
struct Lxr {
    string name;     // 联系人姓名
    char num[11];    // 电话号码
    string address;  // 地址
};

// 创建联系人数组和计数变量
Lxr txl[MAX];
int n = 0;
//ewd
// 显示菜单
void menu() {
    cout << "*********通讯录********" << endl;
    cout << "*****1.添加联系人******" << endl;
    cout << "*****2.显示联系人******" << endl;
    cout << "*****3.删除联系人******" << endl;
    cout << "*****4.查找联系人******" << endl;
    cout << "*****5.修改联系人******" << endl;
    cout << "*****6.清空联系人******" << endl;
    cout << "*****7.通讯录清重******" << endl;
    cout << "*****8.返回菜单页******" << endl;
    cout << "*****0.退出通讯录******" << endl;
}

// 从文件加载联系人
void loadContacts() {
    ifstream infile("contacts.txt");
    if (!infile) {
        cout << "暂无文件(或无法打开)" << endl;
        return;
    }
    n = 0;
    while (infile >> txl[n].name >> txl[n].num >> txl[n].address) {
        n++;
    }
    cout << "加载成功" << endl;
    infile.close();
}

// 将联系人保存到文件
void saveContacts() {
    ofstream outfile("contacts.txt");
    for (int i = 0; i < n; i++) {
        outfile << txl[i].name << " " << txl[i].num << " " << txl[i].address << endl;
    }
    cout << "保存成功" << endl;
    outfile.close();
}

// 检查手机号是否重复
bool isPhoneNumberDuplicate(const char* num) {
    for (int i = 0; i < n; i++) {
        if (strcmp(txl[i].num, num) == 0) {
            return true;
        }
    }
    return false;
}

// 1.添加联系人
void addLxr() {
    if (n >= MAX) {
        cout << "通讯录已满，无法继续添加，请删除多余联系人后再次尝试添加" << endl;
        return;
    }
    Lxr newLxr;
    cout << "请输入联系人姓名：" << endl;
    cin >> newLxr.name;
    while (true) {
        cout << "请输入联系人电话（11位）：" << endl;
        cin >> newLxr.num;
        if (strlen(newLxr.num) != 11) {
            cout << "电话号码必须为11位，请重新输入。" << endl;
            continue;
        }
        if (isPhoneNumberDuplicate(newLxr.num)) {
            cout << "电话号码已存在，请重新输入。" << endl;
            continue;
        }
        break;
    }
    cout << "请输入联系人地址：" << endl;
    cin >> newLxr.address;
    txl[n] = newLxr;
    n++;
    saveContacts();
    cout << "输入(8)再次显示菜单,输入(0)退出程序" << endl;
}

// 2.显示联系人
void txlShow() {
    if (n == 0) {
        cout << "通讯录为空" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << "第[" << i + 1 << "]位联系人："
            << "姓名：" << txl[i].name
            << " 电话：" << txl[i].num
            << " 地址：" << txl[i].address << endl;
    }
    cout << "共有 " << n << " 位联系人" << endl;
    cout << "输入(8)再次显示菜单,输入(0)退出程序" << endl;
}

// 3.删除联系人
void delLxr() {
    if (n == 0) {
        cout << "通讯录为空" << endl;
        return;
    }
    cout << "请输入要删除的联系人编号：" << endl;
    int num = 0;
    cin >> num;
    if (cin.fail() || num < 1 || num > n) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "输入错误，请输入 1~" << n << " 之间的数字" << endl;
        return;
    }
    cout << "请确认是否删除以下联系人：" << endl;
    cout << "姓名：" << txl[num - 1].name
        << " 电话：" << txl[num - 1].num
        << " 地址：" << txl[num - 1].address << endl;
    cout << "确认删除请输入 (1)，输入任意数字取消删除" << endl;
    int select = 0;
    cin >> select;
    if (select == 1) {
        for (int i = num - 1; i < n - 1; i++) {
            txl[i] = txl[i + 1];
        }
        n--;
        saveContacts();
        cout << "删除成功" << endl;
        cout << "输入(8)再次显示菜单,输入(0)退出程序" << endl;
    }
}

// 4.查找联系人
void findLxr() {
    if (n == 0) {
        cout << "通讯录为空" << endl;
        return;
    }
    cout << "请输入要查找联系人的姓名：" << endl;
    string name;
    cin >> name;
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (txl[i].name == name) {
            cout << "编号：[" << i + 1 << "] "
                << "姓名：" << txl[i].name
                << " 电话：" << txl[i].num
                << " 地址：" << txl[i].address << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "查无此人" << endl;
    }
    cout << "输入(8)再次显示菜单,输入(0)退出程序" << endl;
}

// 5.修改联系人
void modifyLxr() {
    if (n == 0) {
        cout << "通讯录为空" << endl;
        return;
    }
    cout << "请输入你要修改联系人的姓名：" << endl;
    string name;
    cin >> name;
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (txl[i].name == name) {
            cout << "请输入新的联系人姓名：" << endl;
            cin >> txl[i].name;
            while (true) {
                cout << "请输入新的联系人电话（11位）：" << endl;
                cin >> txl[i].num;
                if (strlen(txl[i].num) != 11) {
                    cout << "电话号码必须为11位，请重新输入。" << endl;
                    continue;
                }
                if (isPhoneNumberDuplicate(txl[i].num)) {
                    cout << "电话号码已存在，请重新输入。" << endl;
                    continue;
                }
                break;
            }
            cout << "请输入新的联系人地址：" << endl;
            cin >> txl[i].address;
            saveContacts();
            cout << "修改成功" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "查无此人" << endl;
    }
    cout << "输入(8)再次显示菜单,输入(0)退出程序" << endl;
}

// 6.清空联系人
void clearLxr() {
    if (n == 0) {
        cout << "通讯录为空" << endl;
        return;
    }
    cout << "请确认是否清空通讯录" << endl;
    cout << "确认清空请输入 (1)，输入任意数字取消清空" << endl;
    int select = 0;
    cin >> select;
    if (select == 1) {
        n = 0;
        saveContacts();
        cout << "清空成功" << endl;
    }
    cout << "输入(8)再次显示菜单,输入(0)退出程序" << endl;
}

// 7.清除重复联系人
void removeDuplicates() {
    if (n == 0) {
        cout << "通讯录为空" << endl;
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (txl[i].name == txl[j].name && strcmp(txl[i].num, txl[j].num) == 0) {
                for (int k = j; k < n - 1; k++) {
                    txl[k] = txl[k + 1];
                }
                n--;
                j--; // 重新检查当前索引
            }
        }
    }
    saveContacts();
    cout << "重复联系人已清除" << endl;
    cout << "输入(8)再次显示菜单,输入(0)退出程序" << endl;
}

// 主函数
int main() {
    loadContacts();
    menu();
    while (true) {
        int select = 0;
        cin >> select;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "输入错误，请输入 0~8 号数字，（8）再次显示菜单，（0）退出程序" << endl;
            continue;
        }
        switch (select) {
        case 1:
            addLxr();
            break;
        case 2:
            txlShow();
            break;
        case 3:
            delLxr();
            break;
        case 4:
            findLxr();
            break;
        case 5:
            modifyLxr();
            break;
        case 6:
            clearLxr();
            break;
        case 7:
            removeDuplicates();
            break;
        case 8:
            menu();
            break;
        case 0:
            cout << "程序已退出，再见！" << endl;
            return 0;
        default:
            cout << "输入错误，请输入 0~8 号数字，（8）再次显示菜单，（0）退出程序" << endl;
            break;
        }
    }
    return 0;
}

