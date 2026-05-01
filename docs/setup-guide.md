\# ⚙️ Setup Guide – DNS, Mail Server \& Client-Server System



This guide explains how to set up the full system on \*\*CentOS / RHEL-based Linux\*\*.



\---



\# 🌐 1. DNS SERVER SETUP (BIND)



\## 🔹 Install BIND



```bash

sudo dnf install bind bind-utils -y

```



\---



\## 🔹 Configure named.conf



```bash

sudo vi /etc/named.conf

```



Add:



```conf

options {

&#x20;   listen-on port 53 { 127.0.0.1; <SERVER\_IP>; };

&#x20;   directory "/var/named";

&#x20;   allow-query { localhost; any; };

&#x20;   recursion yes;

&#x20;   dnssec-validation no;

};



zone "<DOMAIN>" IN {

&#x20;   type master;

&#x20;   file "forward.<DOMAIN>";

};



zone "<REVERSE\_ZONE>" IN {

&#x20;   type master;

&#x20;   file "reverse.<DOMAIN>";

};

```



\---



\## 🔹 Create Forward Zone



```bash

sudo vi /var/named/forward.<DOMAIN>

```



Example:



```dns

$TTL 86400

@   IN  SOA ns.<DOMAIN>. root.<DOMAIN>. (

&#x20;       2026040101

&#x20;       3600

&#x20;       1800

&#x20;       604800

&#x20;       86400 )



@       IN  NS      ns.<DOMAIN>.

@       IN  A       <SERVER\_IP>



ns      IN  A       <SERVER\_IP>

client  IN  A       <CLIENT\_IP>

helpdesk IN A       <SERVER\_IP>



@       IN  MX 10   mail.<DOMAIN>

mail    IN  A       <SERVER\_IP>

```



\---



\## 🔹 Create Reverse Zone



```bash

sudo vi /var/named/reverse.<DOMAIN>

```



Example:



```dns

$TTL 86400

@   IN  SOA ns.<DOMAIN>. root.<DOMAIN>. (

&#x20;       2026040101

&#x20;       3600

&#x20;       1800

&#x20;       604800

&#x20;       86400 )



@   IN  NS  ns.<DOMAIN>.



10  IN  PTR ns.<DOMAIN>.

20  IN  PTR client.<DOMAIN>.

```



\---



\## 🔹 Start DNS



```bash

sudo systemctl enable named

sudo systemctl restart named

```



\---



\## 🔹 Open firewall



```bash

sudo firewall-cmd --permanent --add-port=53/udp

sudo firewall-cmd --reload

```



\---



\## 🔹 Test DNS



```bash

dig @<SERVER\_IP> <DOMAIN>

dig helpdesk.<DOMAIN>

dig -x <SERVER\_IP>

```



\---



\# 📧 2. MAIL SERVER SETUP (POSTFIX + DOVECOT)



\## 🔹 Install packages



```bash

sudo dnf install postfix dovecot s-nail -y

```



\---



\## 🔹 Configure Postfix



```bash

sudo vi /etc/postfix/main.cf

```



Set:



```conf

myhostname = mail.<DOMAIN>

mydomain = <DOMAIN>

myorigin = $mydomain



inet\_interfaces = all

inet\_protocols = ipv4



mydestination = $myhostname, localhost.$mydomain, localhost, $mydomain



home\_mailbox = Maildir/

```



\---



\## 🔹 Start Postfix



```bash

sudo systemctl enable postfix

sudo systemctl restart postfix

```



\---



\## 🔹 Configure Dovecot



```bash

sudo vi /etc/dovecot/conf.d/10-mail.conf

```



Set:



```conf

mail\_location = maildir:\~/Maildir

```



\---



\## 🔹 Start Dovecot



```bash

sudo systemctl enable dovecot

sudo systemctl restart dovecot

```



\---



\## 🔹 Create users



```bash

sudo useradd user1

sudo passwd user1



sudo useradd user2

sudo passwd user2

```



\---



\## 🔹 Create Maildir



```bash

sudo mkdir -p /home/user2/Maildir/{cur,new,tmp}

sudo chown -R user2:user2 /home/user2/Maildir

sudo chmod -R 700 /home/user2/Maildir

```



\---



\## 🔹 Mail alias (helpdesk)



```bash

sudo vi /etc/aliases

```



Add:



```text

helpdesk: user2

```



Apply:



```bash

sudo newaliases

```



\---



\## 🔹 Test mail



```bash

echo "Test message" | mail -s "Test" helpdesk@<DOMAIN>

```



\---



\# 💻 3. CLIENT-SERVER PROGRAM (C)



\## 🔹 Compile



```bash

gcc server.c -o server

gcc client.c -o client

```



\---



\## 🔹 Run



```bash

./server

./client

```



\---



\# 🧪 4. TROUBLESHOOTING



\## DNS issues



```bash

named-checkconf

named-checkzone <DOMAIN> /var/named/forward.<DOMAIN>

```



\---



\## Mail issues



```bash

sudo tail -f /var/log/maillog

```



\---



\## Port issues



```bash

fuser -k 8080/tcp

```



\---



\# 🎯 Notes



\* Replace `<DOMAIN>` with your registration domain

\* Replace `<SERVER\_IP>` and `<CLIENT\_IP>` accordingly

\* Restart services after every change



\---



\# 🚀 Final Result



✔ DNS resolving correctly

✔ Mail sending and receiving

✔ Client-server communication working



