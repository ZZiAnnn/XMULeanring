#include <iostream>
#include <cstring>
#include <WS2tcpip.h>
#include <winsock2.h>
#include <Windows.h>
#include <time.h>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

const int PORT = 8888;
const char* SERVER_IP = "127.0.0.1";

const int REPORT_INTERVAL = 30 * 60;  // ״̬������ʱ�䣬��λΪ�루30���ӣ�

bool stopFlag = false;  // �߳�ֹͣ��־

void SendStatusReport(SOCKET clientSocket)
{
    while (!stopFlag)
    {
        // ����״̬���浽������
        string report = "status report";
        if (send(clientSocket, report.c_str(), report.size() + 1, 0) < 0) 
        {
            cerr << "����״̬����ʧ��" << std::endl;
        }
        this_thread::sleep_for(chrono::seconds(1800));       
    }
}
void softwareA()
{
    cout << "ʹ�����A�У���������������Aʹ��" << endl;
    getchar();
    getchar();
}
string get_license(const char account[],const char password[],const char type[])
{
    WSADATA wsaData;
    SOCKET clientSocket2;
    struct sockaddr_in serverAddress2;
    // ��ʼ�� Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
    {
        std::cerr << "��ʼ�� Winsock ʧ��" << std::endl;
        exit(-1);
    }
    // �����׽���
    clientSocket2 = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket2 == INVALID_SOCKET) {
        std::cerr << "�����׽���ʧ��" << std::endl;
        exit(-1);
    }

    // ���÷�������ַ�Ͷ˿�
    serverAddress2.sin_family = AF_INET;
    serverAddress2.sin_port = htons(6666);
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress2.sin_addr)) <= 0) {
        std::cerr << "��Ч�ķ�������ַ" << std::endl;
        exit(-1);
    }

    // ���ӷ�����
    if (connect(clientSocket2, (struct sockaddr*)&serverAddress2, sizeof(serverAddress2)) < 0) {
        std::cerr << "���ӷ�����ʧ��" << std::endl;
        exit(-1);
    }

    if (send(clientSocket2, account,strlen(account) + 1, 0) < 0) {
        std::cerr << "������Ϣʧ��" << std::endl;
        exit(-1);
    }
    Sleep(1);
    if (send(clientSocket2, password, strlen(password) + 1, 0) < 0) {
        std::cerr << "������Ϣʧ��" << std::endl;
        exit(-1);
    }
    Sleep(1);
    if (send(clientSocket2, type, strlen(type) + 1, 0) < 0) {
        std::cerr << "������Ϣʧ��" << std::endl;
        exit(-1);
    }
    char buffer[1024] = { 0 };
    if (recv(clientSocket2, buffer, 1024, 0) < 0) {
        std::cerr << "������Ӧʧ��" << std::endl;
        exit(-1);
    }
    // �ر��׽���

    closesocket(clientSocket2);

    // ���� Winsock
    WSACleanup();
    return (string)buffer;
}
int main() 
{
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddress;
    cout << "�Ѿ�ӵ�����֤��[Y/n]:";
    char c = getchar();
    if (c == 'N' || c == 'n')
    {
        string account, password, type;
        cout << "����������û�����";
        cin >> account;
        cout << "������������룺";
        cin >> password;
        cout << "����������û����ͣ�";
        cin >> type;
        cout << "�������֤Ϊ:" << get_license(account.c_str(), password.c_str(), type.c_str())<<"������μ�" << endl << endl;
    }

    // ��ʼ�� Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "��ʼ�� Winsock ʧ��" << std::endl;
        return -1;
    }

    // �����׽���
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "�����׽���ʧ��" << std::endl;
        return -1;
    }

    // ���÷�������ַ�Ͷ˿�
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "��Ч�ķ�������ַ" << std::endl;
        return -1;
    }

    // ���ӷ�����
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "���ӷ�����ʧ��" << std::endl;
        return -1;
    }

    // �������ݵ�������
    string license;
    cout << "������10λ���֤��";
    while (cin >> license && license.size() != 10) cout << " ���֤���Ϸ������������룺";
    if (send(clientSocket, license.c_str(), license.size() + 1, 0) < 0) {
        std::cerr << "������Ϣʧ��" << std::endl;
        return -1;
    }

    // ���շ���������Ӧ
    char buffer[1024] = { 0 };
    if (recv(clientSocket, buffer, 1024, 0) < 0) {
        std::cerr << "������Ӧʧ��" << std::endl;
        return -1;
    }
    string s = buffer;
    if (s == "ACCEPT")
    {
        cout << "����ʹ��" << endl;
        stopFlag = false;
        thread t(SendStatusReport, clientSocket);
        //ʹ�����A
        softwareA();
        stopFlag = true;
        t.detach();
    }
    else if (s == "REJECT")
    {
        cout << "��ǰ���֤�û����������Ժ��ٳ���";
        Sleep(10);
    }


    // �ر��׽���

    closesocket(clientSocket);

    // ���� Winsock
    WSACleanup();

    return 0;
}
