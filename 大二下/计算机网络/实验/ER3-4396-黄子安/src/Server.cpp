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

const int max_license = 5;
std::map<std::string, int> license;
const int PORT = 8888;
string time_now()
{
    std::time_t now = std::time(nullptr);

    // ��ʱ���ת��Ϊ����ʱ��
    std::tm* localTime = std::localtime(&now);

    // ��ʽ��ʱ���ַ���
    char timeStr[80];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localTime);
    return (string) timeStr;
}
// ����ͻ���������̺߳���
void clientThread(SOCKET clientSocket) 
{

    // ��ȡ�ͻ��˵�ַ��Ϣ
    sockaddr_in clientAddr;
    int addrLen = sizeof(clientAddr);
    getpeername(clientSocket, (struct sockaddr*)&clientAddr, &addrLen);

    // ���ͻ��˵�ַת��Ϊ�ַ�����ʽ
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), ip, INET_ADDRSTRLEN);
    char buffer[1024] = { 0 };
    int bytesRead = recv(clientSocket, buffer, 1024, 0);

    if (bytesRead < 0)
    {
        std::cerr << time_now()<<"��������"<<ip<<"����Ϣʧ��" << std::endl;
        return;
    }
    string str = buffer;
    if (license.find(str) == license.end()|| license[str] < max_license)
    {
        string res = "ACCEPT";
        send(clientSocket, res.c_str(), res.size() + 1, 0);
        license[str]++;
        std::cout << time_now() << " �ͻ�����,"<<" ���֤Ϊ" << str << "��IP��ַΪ " << ip <<"�������֤���û�����Ϊ"<<license[str] << std::endl;
        while (true)
        {
            bytesRead = recv(clientSocket, buffer, 1024, 0);
            if (bytesRead > 0)
            {
                cout << time_now() << " ���յ����֤Ϊ" << str << ",ip��ַΪ" << ip << "���û�״̬����" << endl;
            }
            else
            {
                cout << time_now() << " ���֤Ϊ" << str << ",ip��ַΪ" << ip << "���û����˳�" << endl;
                license[str] --;
                return;
            }
        }
    }
    else
    {
        string res = "REJECT";
        std::cout << time_now() << " �ͻ�����," << " ���֤Ϊ" << str << "��IP��ַΪ " << ip << "���������֤���û������������ͻ�����ʧ��" << std::endl;
        send(clientSocket, res.c_str(), res.size() + 1, 0);     
    }
    // �رտͻ�������
    closesocket(clientSocket);
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
        // �����̴߳���ͻ�������
        std::thread clientThreadOBJ(clientThread, clientSocket);
        clientThreadOBJ.detach(); // �����̣߳�ʹ�������������Զ��ͷ���Դ
    }

    // �رշ������׽���
    closesocket(serverSocket);

    // ���� Winsock
    WSACleanup();

    return 0;
}