#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Инициализация Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    // Создание сокета
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Настройка адреса сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Подключение к серверу
    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    
    std::cout << "Connected to server! Type messages:" << std::endl;
    
    // Обмен сообщениями
    char buffer[256];
    std::string message;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, message);
        
        if (message == "exit") break;
        
        // Отправка сообщения
        send(clientSocket, message.c_str(), message.length(), 0);
        
        // Получение ответа
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        buffer[bytesReceived] = '\0';
        
        std::cout << "Server: " << buffer << std::endl;
    }
    
    // Закрытие сокета
    closesocket(clientSocket);
    WSACleanup();
    
    return 0;
}