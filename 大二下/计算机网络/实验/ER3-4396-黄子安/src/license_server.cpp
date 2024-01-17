#include <iostream>
#include <cstdio>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <map>
#include <chrono>
#include <string>
#include <thread>
using namespace std;
#pragma comment(lib,"Ws2_32.lib")

string get_license(char account[],char password[],char type[])
{
    //todo:����Ϣ�������ݿ�
    //todo:�����֤���л�ȡһ�����֤�����������������
    int license = rand() + 1000000000;
    return to_string(license);
}
const int PORT = 6666;

string time_now()
{
    std::time_t now = std::time(nullptr);

    // ��ʱ���ת��Ϊ����ʱ��
    std::tm* localTime = std::localtime(&now);

    // ��ʽ��ʱ���ַ���
    char timeStr[80];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
    return (string)timeStr;
}


int main()
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressLength = sizeof(clientAddress);

    // ��ʼ�� Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "��ʼ�� Winsock ʧ��" << std::endl;
        return -1;
    }

    // �����׽���
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "�����׽���ʧ��" << std::endl;
        return -1;
    }

    // ���÷�������ַ�Ͷ˿�
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // ���׽��ֵ���������ַ�Ͷ˿�
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cerr << "���׽���ʧ��" << std::endl;
        return -1;
    }

    // ��������
    if (listen(serverSocket, 5) == SOCKET_ERROR)
    {
        std::cerr << "����ʧ��" << std::endl;
        return -1;
    }

    std::cout << "�ȴ��ͻ�������..." << std::endl;

    while (true)
    {
        // ���ܿͻ�������
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "��������ʧ��" << std::endl;
            continue;
        }
        char account[80], password[80], type[80];
        if (recv(clientSocket, account, 1024, 0) < 0)
        {
            cerr << "��������ʧ��" << endl;
        }

        if (recv(clientSocket, password, 1024, 0) < 0)
        {
            cerr << "��������ʧ��" << endl;
        }

        if (recv(clientSocket, type, 1024, 0) < 0)
        {
            cerr << "��������ʧ��" << endl;
        }

        string license=get_license(account,password,type);
        cout << time_now() << " �û���" << account << "���룬���������֤" << license << endl;
        send(clientSocket, license.c_str(), license.size() + 1, 0);
    }

    closesocket(clientSocket);

    // �رշ������׽���
    closesocket(serverSocket);

    // ���� Winsock
    WSACleanup();

    return 0;
}