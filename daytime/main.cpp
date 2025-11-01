#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main() {
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }
    cout << "UDP сокет успешно создан" << endl;

    char msg[] = "Test message\n";
    int rc = sendto(s, msg, sizeof(msg), 0, (const sockaddr*)&server_addr, sizeof(sockaddr_in));

    if (rc == -1) {
        cerr << "Ошибка отправки запроса" << endl;
        close(s);
        return 1;
    }
    cout << "Сообщение успешно отправлено" << endl;

    close(s);
    return 0;
}
