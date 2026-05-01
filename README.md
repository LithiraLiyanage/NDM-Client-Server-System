<div align="center">

# 🌐 DNS & Client-Server System

### Linux Networking Project with BIND DNS, Mail Server, and C Socket Programming

![Linux](https://img.shields.io/badge/OS-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![CentOS](https://img.shields.io/badge/Server-CentOS-262577?style=for-the-badge&logo=centos&logoColor=white)
![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![BIND](https://img.shields.io/badge/DNS-BIND-2E8B57?style=for-the-badge)
![Postfix](https://img.shields.io/badge/Mail-Postfix-D14836?style=for-the-badge)
![Dovecot](https://img.shields.io/badge/Mail-Dovecot-6A5ACD?style=for-the-badge)
![TCP](https://img.shields.io/badge/Protocol-TCP%2FIP-0078D4?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge)

<br/>

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=22&duration=2500&pause=800&center=true&vCenter=true&width=800&lines=Authoritative+DNS+Server+with+BIND;Forward+and+Reverse+DNS+Resolution;Postfix+%2B+Dovecot+Mail+Server;TCP+Client-Server+Application+in+C;Session+Logging+with+IP+and+Port+Details" alt="Typing SVG" />

</div>

## 📌 Overview

A real-world networking project that demonstrates:

✨ Authoritative DNS Server (BIND)
✨ Forward & Reverse DNS resolution
✨ TCP Client-Server communication using C
✨ Session logging system
✨ Mail server DNS (MX records)

---

## 🧠 Architecture

```
Client (23.74.33.20)
        │
        │  TCP Connection (Port 8080)
        ▼
Server (23.74.33.10)
        │
        │  DNS Queries (Port 53)
        ▼
DNS Server (BIND)
```

---

## 🌐 DNS Configuration

### 🔹 Forward DNS

```
IT23743380.lk        → 23.74.33.10
kalindu3380          → 23.74.33.10
kalindu3380cli       → 23.74.33.20
```

### 🔹 Reverse DNS

```
23.74.33.10 → achindu4940.IT23534940.lk
23.74.33.20 → achindu4940cli.IT23534940.lk
```

---

## 💻 Client-Server System

### 🔹 Features

✔ TCP socket communication
✔ Iterative server design
✔ Sends real-time server date & time
✔ Logs client connections
✔ Handles multiple client sessions

---

## ⚙️ Technologies Used

| Category   | Technology     |
| ---------- | -------------- |
| OS         | Linux (CentOS) |
| DNS        | BIND (named)   |
| Language   | C              |
| Networking | TCP/IP         |

---

## 🚀 How to Run

### 🔧 Compile

```bash
gcc server.c -o server
gcc client.c -o client
```

### ▶️ Run Server

```bash
./server
```

### ▶️ Run Client

```bash
./client
```

---

📧Mail Server

🔹Technologies
Postfix – Mail Transfer Agent (sending)
Dovecot – Mail Delivery Agent (receiving)

🔹Features
Maildir-based storage
Local mail delivery


## 🧪 DNS Testing

```bash
dig @23.74.33.10 IT23743380.lk
dig kalindu3380.IT23743380.lk
dig -x 23.74.33.10
```

## 🎯 Learning Outcomes

✔ DNS Zone Configuration
✔ Socket Programming
✔ Network Troubleshooting
✔ Linux Server Management

---

## 👨‍💻 Author

**Kalindu Methmuditha**
🎓 Software Engineering Student


---

⭐ If you like this project, give it a star!
