#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main() {
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13);
    server_addr.sin_addr.s_addr = inet_addr("129.6.15.28");

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }

    int rc = sendto(s, nullptr, 0, 0, (const sockaddr*)&server_addr, sizeof(sockaddr_in));

    if (rc == -1) {
        cerr << "Ошибка отправки запроса" << endl;
        close(s);
        return 1;
    }

    char buf[256];
    sockaddr_in from_addr;
    socklen_t len = sizeof(sockaddr_in);

    rc = recvfrom(s, buf, sizeof(buf), 0, (sockaddr*)&from_addr, &len);

    if (rc > 0) {
        buf[rc] = '\0';
        cout << buf;
    } else {
        cerr << "Ошибка получения ответа" << endl;
    }

    close(s);
    return 0;
}
