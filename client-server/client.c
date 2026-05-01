#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define SERVER_IP "23.65.83.10"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024
#define LOG_FILE "client_log.txt"

void log_session(const char *server_ip, int server_port) {
    FILE *fp = fopen(LOG_FILE, "a");
    if (fp == NULL) {
        perror("Error opening client log file");
        return;
    }

    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);
    char time_str[100];

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    fprintf(fp, "[%s] Connected to server %s:%d\n", time_str, server_ip, server_port);
    fclose(fp);
}

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 1. Create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid server IP address");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Connect to server
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Session initiated.\n");
    printf("Connected to server %s:%d\n", SERVER_IP, SERVER_PORT);

    // Log client-side session
    log_session(SERVER_IP, SERVER_PORT);

    // 4. Receive date and time from server
    memset(buffer, 0, sizeof(buffer));
    int bytes_received = recv(sock_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
        perror("Receive failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    // 5. Display received data
    printf("Message received from server:\n%s\n", buffer);

    // 6. Close socket
    close(sock_fd);
    printf("Connection closed.\n");

    return 0;
}