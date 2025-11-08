#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main() {
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        cerr << "Ошибка создания серверного сокета" << endl;
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Ошибка привязки сокета" << endl;
        close(server_socket);
        return 1;
    }
    cout << "UDP сервер запущен на порту 8888..." << endl;

    while (true) {
        char buffer[256];
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int bytes_received = recvfrom(server_socket, buffer, sizeof(buffer), 0, (sockaddr*)&client_addr, &client_len);
        
        if (bytes_received == -1) {
            cerr << "Ошибка приема данных" << endl;
            continue;
        }

        cout << "Получено от клиента: ";
        cout.write(buffer, bytes_received);
        cout << " (" << bytes_received << " байт)" << endl;

        char response[] = "Ответ от UDP сервера";
        int bytes_sent = sendto(server_socket, response, sizeof(response), 0, (sockaddr*)&client_addr, client_len);
        
        if (bytes_sent == -1) {
            cerr << "Ошибка отправки ответа" << endl;
        } else {
            cout << "Отправлен ответ клиенту: " << response << endl;
        }
        cout << endl;
    }

    close(server_socket);
    return 0;
}
