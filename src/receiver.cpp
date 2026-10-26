#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

int main() {
    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0) {
        cout << "Winsock initialization failed\n";
        return 1;
    }

    cout << "Winsock initialized successfully\n";
    
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(serverSocket == INVALID_SOCKET) {
        cout << "Socket Creation Failed\n";
        WSACleanup();
        return 1;

    }

    cout << "Socket created Successfully\n";

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5000);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    int bindResult = bind(
        serverSocket, reinterpret_cast<sockaddr*>(&serverAddress),sizeof(serverAddress)
    );

    if (bindResult == SOCKET_ERROR) {
        cout << "Bind Failed. Error:" << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        return 1;
    }

    cout << "Socket bound to port 5000\n";

    int listenResult = listen(serverSocket, SOMAXCONN);

    if(listenResult == SOCKET_ERROR) {
        cout << "Listen Failed. Error: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        return 1;
    }

    cout << "FlashSend receiver is listening on port 5000\n";
    cout << "Waiting for a sender.....\n";

    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

    if (clientSocket == INVALID_SOCKET) {
        cout << "Accept Failed. Error:" << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        return 1;
    }

    cout << "A Sender Connected Successfully!\n";


    closesocket(clientSocket);
    closesocket(serverSocket);

    WSACleanup();
    return 0;
}