#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main() {
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }
    cout << "TCP сокет успешно создан" << endl;

    int rc = connect(s, (const sockaddr*)&server_addr, sizeof(sockaddr_in));
    if (rc == -1) {
        cerr << "Ошибка подключения к серверу" << endl;
        close(s);
        return 1;
    }
    cout << "Успешно подключено к серверу" << endl;

    char msg[] = "Test message";
    rc = send(s, msg, sizeof(msg), 0);
    if (rc == -1) {
        cerr << "Ошибка отправки сообщения" << endl;
        close(s);
        return 1;
    }
    cout << "Сообщение успешно отправлено" << endl;

    char buf[256];
    rc = recv(s, buf, sizeof(buf), 0);
    if (rc == -1) {
        cerr << "Ошибка приема ответа" << endl;
        close(s);
        return 1;
    }
    cout << "Получен ответ: ";
    cout.write(buf, rc);
    cout << endl;

    close(s);
    return 0;
}
