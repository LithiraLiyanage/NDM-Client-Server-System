#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define LOG_FILE "server_log.txt"

void log_session(const char *client_ip, int client_port) {
    FILE *fp = fopen(LOG_FILE, "a");
    if (fp == NULL) {
        perror("Error opening server log file");
        return;
    }

    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);
    char time_str[100];

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);

    fprintf(fp, "[%s] Client connected from %s:%d\n", time_str, client_ip, client_port);
    fclose(fp);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char time_buffer[BUFFER_SIZE];

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Optional: allow quick restart of server
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;   // listen on all server interfaces
    server_addr.sin_port = htons(PORT);

    // 3. Bind socket to IP and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Start listening
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Iterative TCP Server started.\n");
    printf("Listening on port %d...\n", PORT);

    // 5. Iterative loop
    while (1) {
        // Accept one client at a time
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        // Extract client IP and port
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
        int client_port = ntohs(client_addr.sin_port);

        printf("\nNew session initiated.\n");
        printf("Client IP   : %s\n", client_ip);
        printf("Client Port : %d\n", client_port);

        // Log server-side session
        log_session(client_ip, client_port);

        // Get current system date and time
        time_t now = time(NULL);
        struct tm *time_info = localtime(&now);
        strftime(time_buffer, sizeof(time_buffer),
                 "Current server date and time: %Y-%m-%d %H:%M:%S",
                 time_info);

        // Send date and time to client
        if (send(client_fd, time_buffer, strlen(time_buffer), 0) < 0) {
            perror("Send failed");
        } else {
            printf("Date and time sent to client successfully.\n");
        }

        // Close current client connection
        close(client_fd);
        printf("Client connection closed.\n");
    }

    close(server_fd);
    return 0;
}