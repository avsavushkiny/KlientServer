#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Инициализация Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    // Создание сокета
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Настройка адреса
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    // Привязка сокета
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // Прослушивание порта
    listen(serverSocket, SOMAXCONN);
    
    std::cout << "Server listening on port 8080..." << std::endl;
    
    // Принятие подключения
    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
    
    std::cout << "Client connected!" << std::endl;
    
    // Обмен данными
    char buffer[256];
    while (true) {
        // Получение сообщения
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;
        
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << std::endl;
        
        // Эхо-ответ
        send(clientSocket, buffer, bytesReceived, 0);
        std::cout << "Echo sent" << std::endl;
    }
    
    // Закрытие сокетов
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    
    return 0;
}