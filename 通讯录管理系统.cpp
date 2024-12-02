#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

// ͨѶ¼�����������
const int MAX = 500;

// ������ϵ�˽ṹ��
struct Lxr {
    string name;     // ��ϵ������
    char num[11];    // �绰����
    string address;  // ��ַ
};

// ������ϵ������ͼ�������
Lxr txl[MAX];
int n = 0;
//ewd
// ��ʾ�˵�
void menu() {
    cout << "*********ͨѶ¼********" << endl;
    cout << "*****1.�����ϵ��******" << endl;
    cout << "*****2.��ʾ��ϵ��******" << endl;
    cout << "*****3.ɾ����ϵ��******" << endl;
    cout << "*****4.������ϵ��******" << endl;
    cout << "*****5.�޸���ϵ��******" << endl;
    cout << "*****6.�����ϵ��******" << endl;
    cout << "*****7.ͨѶ¼����******" << endl;
    cout << "*****8.���ز˵�ҳ******" << endl;
    cout << "*****0.�˳�ͨѶ¼******" << endl;
}

// ���ļ�������ϵ��
void loadContacts() {
    ifstream infile("contacts.txt");
    if (!infile) {
        cout << "�����ļ�(���޷���)" << endl;
        return;
    }
    n = 0;
    while (infile >> txl[n].name >> txl[n].num >> txl[n].address) {
        n++;
    }
    cout << "���سɹ�" << endl;
    infile.close();
}

// ����ϵ�˱��浽�ļ�
void saveContacts() {
    ofstream outfile("contacts.txt");
    for (int i = 0; i < n; i++) {
        outfile << txl[i].name << " " << txl[i].num << " " << txl[i].address << endl;
    }
    cout << "����ɹ�" << endl;
    outfile.close();
}

// ����ֻ����Ƿ��ظ�
bool isPhoneNumberDuplicate(const char* num) {
    for (int i = 0; i < n; i++) {
        if (strcmp(txl[i].num, num) == 0) {
            return true;
        }
    }
    return false;
}

// 1.�����ϵ��
void addLxr() {
    if (n >= MAX) {
        cout << "ͨѶ¼�������޷�������ӣ���ɾ��������ϵ�˺��ٴγ������" << endl;
        return;
    }
    Lxr newLxr;
    cout << "��������ϵ��������" << endl;
    cin >> newLxr.name;
    while (true) {
        cout << "��������ϵ�˵绰��11λ����" << endl;
        cin >> newLxr.num;
        if (strlen(newLxr.num) != 11) {
            cout << "�绰�������Ϊ11λ�����������롣" << endl;
            continue;
        }
        if (isPhoneNumberDuplicate(newLxr.num)) {
            cout << "�绰�����Ѵ��ڣ����������롣" << endl;
            continue;
        }
        break;
    }
    cout << "��������ϵ�˵�ַ��" << endl;
    cin >> newLxr.address;
    txl[n] = newLxr;
    n++;
    saveContacts();
    cout << "����(8)�ٴ���ʾ�˵�,����(0)�˳�����" << endl;
}

// 2.��ʾ��ϵ��
void txlShow() {
    if (n == 0) {
        cout << "ͨѶ¼Ϊ��" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << "��[" << i + 1 << "]λ��ϵ�ˣ�"
            << "������" << txl[i].name
            << " �绰��" << txl[i].num
            << " ��ַ��" << txl[i].address << endl;
    }
    cout << "���� " << n << " λ��ϵ��" << endl;
    cout << "����(8)�ٴ���ʾ�˵�,����(0)�˳�����" << endl;
}

// 3.ɾ����ϵ��
void delLxr() {
    if (n == 0) {
        cout << "ͨѶ¼Ϊ��" << endl;
        return;
    }
    cout << "������Ҫɾ������ϵ�˱�ţ�" << endl;
    int num = 0;
    cin >> num;
    if (cin.fail() || num < 1 || num > n) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "������������� 1~" << n << " ֮�������" << endl;
        return;
    }
    cout << "��ȷ���Ƿ�ɾ��������ϵ�ˣ�" << endl;
    cout << "������" << txl[num - 1].name
        << " �绰��" << txl[num - 1].num
        << " ��ַ��" << txl[num - 1].address << endl;
    cout << "ȷ��ɾ�������� (1)��������������ȡ��ɾ��" << endl;
    int select = 0;
    cin >> select;
    if (select == 1) {
        for (int i = num - 1; i < n - 1; i++) {
            txl[i] = txl[i + 1];
        }
        n--;
        saveContacts();
        cout << "ɾ���ɹ�" << endl;
        cout << "����(8)�ٴ���ʾ�˵�,����(0)�˳�����" << endl;
    }
}

// 4.������ϵ��
void findLxr() {
    if (n == 0) {
        cout << "ͨѶ¼Ϊ��" << endl;
        return;
    }
    cout << "������Ҫ������ϵ�˵�������" << endl;
    string name;
    cin >> name;
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (txl[i].name == name) {
            cout << "��ţ�[" << i + 1 << "] "
                << "������" << txl[i].name
                << " �绰��" << txl[i].num
                << " ��ַ��" << txl[i].address << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "���޴���" << endl;
    }
    cout << "����(8)�ٴ���ʾ�˵�,����(0)�˳�����" << endl;
}

// 5.�޸���ϵ��
void modifyLxr() {
    if (n == 0) {
        cout << "ͨѶ¼Ϊ��" << endl;
        return;
    }
    cout << "��������Ҫ�޸���ϵ�˵�������" << endl;
    string name;
    cin >> name;
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (txl[i].name == name) {
            cout << "�������µ���ϵ��������" << endl;
            cin >> txl[i].name;
            while (true) {
                cout << "�������µ���ϵ�˵绰��11λ����" << endl;
                cin >> txl[i].num;
                if (strlen(txl[i].num) != 11) {
                    cout << "�绰�������Ϊ11λ�����������롣" << endl;
                    continue;
                }
                if (isPhoneNumberDuplicate(txl[i].num)) {
                    cout << "�绰�����Ѵ��ڣ����������롣" << endl;
                    continue;
                }
                break;
            }
            cout << "�������µ���ϵ�˵�ַ��" << endl;
            cin >> txl[i].address;
            saveContacts();
            cout << "�޸ĳɹ�" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "���޴���" << endl;
    }
    cout << "����(8)�ٴ���ʾ�˵�,����(0)�˳�����" << endl;
}

// 6.�����ϵ��
void clearLxr() {
    if (n == 0) {
        cout << "ͨѶ¼Ϊ��" << endl;
        return;
    }
    cout << "��ȷ���Ƿ����ͨѶ¼" << endl;
    cout << "ȷ����������� (1)��������������ȡ�����" << endl;
    int select = 0;
    cin >> select;
    if (select == 1) {
        n = 0;
        saveContacts();
        cout << "��ճɹ�" << endl;
    }
    cout << "����(8)�ٴ���ʾ�˵�,����(0)�˳�����" << endl;
}

// 7.����ظ���ϵ��
void removeDuplicates() {
    if (n == 0) {
        cout << "ͨѶ¼Ϊ��" << endl;
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (txl[i].name == txl[j].name && strcmp(txl[i].num, txl[j].num) == 0) {
                for (int k = j; k < n - 1; k++) {
                    txl[k] = txl[k + 1];
                }
                n--;
                j--; // ���¼�鵱ǰ����
            }
        }
    }
    saveContacts();
    cout << "�ظ���ϵ�������" << endl;
    cout << "����(8)�ٴ���ʾ�˵�,����(0)�˳�����" << endl;
}

// ������
int main() {
    loadContacts();
    menu();
    while (true) {
        int select = 0;
        cin >> select;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "������������� 0~8 �����֣���8���ٴ���ʾ�˵�����0���˳�����" << endl;
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
            cout << "�������˳����ټ���" << endl;
            return 0;
        default:
            cout << "������������� 0~8 �����֣���8���ٴ���ʾ�˵�����0���˳�����" << endl;
            break;
        }
    }
    return 0;
}

