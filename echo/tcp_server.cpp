#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "Ошибка создания серверного сокета" << endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Ошибка привязки сокета" << endl;
        close(server_socket);
        return 1;
    }

    if (listen(server_socket, 5) == -1) {
        cerr << "Ошибка входящего соединения" << endl;
        close(server_socket);
        return 1;
    }
    cout << "TCP сервер запущен на порту 9999..." << endl;

    while (true) {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_len);
        
        if (client_socket == -1) {
            cerr << "Ошибка приема соединения" << endl;
            continue;
        }
        cout << "Получено соединение от клиента" << endl;

        char buffer[256];
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        
        if (bytes_received == -1) {
            cerr << "Ошибка приема данных" << endl;
            close(client_socket);
            continue;
        }

        cout << "Получено от клиента: ";
        cout.write(buffer, bytes_received);
        cout << " (" << bytes_received << " байт)" << endl;

        int bytes_sent = send(client_socket, buffer, bytes_received, 0);
        if (bytes_sent == -1) {
            cerr << "Ошибка отправки ответа" << endl;
        } else {
            cout << "Отправлен ответ: ";
            cout.write(buffer, bytes_received);
            cout << endl;
        }

        close(client_socket);
        cout << endl;
    }

    close(server_socket);
    return 0;
}
