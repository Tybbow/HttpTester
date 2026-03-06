#🌐 HTTPTester

> **HTTP/HTTPS-based ping tool — measure response time of HTTP requests, like ping but at the application layer.**

![Language](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Version](https://img.shields.io/badge/version-1.1-green?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey?style=flat-square)
![Protocol](https://img.shields.io/badge/protocol-HTTP%20%7C%20HTTPS-orange?style=flat-square)
![OpenSSL](https://img.shields.io/badge/OpenSSL-libssl--dev-red?style=flat-square)

---

## 📖 Description

**HTTPTester** is a lightweight C tool that behaves like `ping`, but at the **HTTP application layer**.

Instead of ICMP or TCP SYN packets, it sends real **HTTP/1.1 requests** (GET, POST, HEAD, etc.) to a target server and measures the **round-trip time (RTT)** for each response — including the full TCP connect, HTTP send, and response receive cycle. It displays the **real HTTP status code** returned by the server, and supports both **plain HTTP** and **HTTPS** via OpenSSL.

> ℹ️ HTTPTester uses standard TCP sockets (`SOCK_STREAM`) — no raw sockets, **no root privileges required**.

---

## ✨ Features

- 📡 Sends real **HTTP/1.1 requests** (GET, POST, HEAD, or any method)
- ⏱️ Measures **RTT per request** in milliseconds (full TCP connect → send → recv cycle)
- ✅ Displays the **real HTTP status code** from the server response (`200`, `301`, `404`, `500`...)
- 🔒 **HTTPS support** via OpenSSL (`-ssl` flag or auto-detection on port 443)
- 🏠 **Virtual host support** (`-vh`) with automatic **SNI** injection for HTTPS
- 📊 Per-request output: HTTP response code, sequence number, RTT
- 📉 Final statistics on `^C` or end of count: transmitted, received, loss %, min/avg/max RTT
- 📝 **POST data support** (`-dp`) with automatic `Content-Length` header
- 🔧 Configurable: port, URI, method, count, interval

---

## 🚀 Usage

```bash
./httptester -d [ip destination]
     optional :
         -p   [port]          (default 80)
         -i   [interval]      (default 1 second)
         -m   [METHOD]        (default GET)
         -u   [uri]           (default /)
         -vh  [vhost]
         -c   [count]         (default 4)
         -dp  [PostData HTTP]
         -ssl                 (force HTTPS, auto-enabled if port 443)
         -h   display this help.
```

### Options

| Flag | Description | Default |
|------|-------------|---------|
| `-d` | Destination IP address (**required**) | — |
| `-p` | Target TCP port | `80` |
| `-m` | HTTP method (`GET`, `POST`, `HEAD`, ...) | `GET` |
| `-u` | Request URI | `/` |
| `-vh` | Virtual host (`Host:` header + SNI for HTTPS) | Destination IP |
| `-c` | Number of requests (`-1` = unlimited) | `4` |
| `-i` | Interval between requests in seconds (float) | `1` |
| `-dp` | POST body data (requires `-m POST`) | — |
| `-ssl` | Force HTTPS/TLS (auto-enabled if port is `443`) | disabled |
| `-h` | Display usage | — |

---

## 💡 Examples

### Basic HTTP GET

```bash
./httptester -d 188.165.76.5 -vh "tybbow.com"
```

**Output:**
```
[+] Mode: HTTP  (port 80)

from (188.165.76.5): response: (200) http_seq=1 time=17.32 ms
from (188.165.76.5): response: (200) http_seq=2 time=16.35 ms
from (188.165.76.5): response: (200) http_seq=3 time=20.73 ms
from (188.165.76.5): response: (200) http_seq=4 time=16.64 ms

--- 188.165.76.5 HTTPtester statistics ---
4 packets transmitted, 4 received, 0.00% packets loss
rtt min/avg/max = 16.35/17.76/20.73 ms
```

### HTTPS via flag `-ssl`

```bash
./httptester -d 188.165.76.5 -p 443 -ssl -vh "tybbow.com"
```

### HTTPS auto-detection (port 443 suffit)

```bash
./httptester -d 188.165.76.5 -p 443 -vh "tybbow.com"
```

**Output:**
```
[+] Mode: HTTPS (port 443)

from (188.165.76.5): response: (200) http_seq=1 time=21.10 ms
...
```

### Détecter une redirection HTTP → HTTPS

```bash
./httptester -d 188.165.76.5 -u "/old-page"
```

```
from (188.165.76.5): response: (301) http_seq=1 time=15.10 ms
```

### POST avec données

```bash
./httptester -d 192.168.1.10 -p 8080 -m "POST" -u "/api/login" -dp "user=admin&pass=1234" -c 10
```

### Probe continu sur un endpoint de santé

```bash
./httptester -d 10.0.0.1 -u "/health" -i 0.5 -c -1
```

---

## 🛠️ Build

### Prérequis

- GCC ou Clang
- Linux ou macOS
- `make`
- **libssl-dev** (OpenSSL)

```bash
# Debian / Ubuntu
sudo apt install libssl-dev

# macOS
brew install openssl
```

> Aucun accès root requis — HTTPTester utilise des sockets TCP standards (`SOCK_STREAM`).

### Compiler

```bash
make
```

### Nettoyer

```bash
make clean    # supprime les .o
make fclean   # supprime les .o + le binaire
make re       # recompile tout
```

### Lancer

```bash
./httptester -d  [-p ] [-ssl] [-vh ]
```

---

## 🗂️ Structure du projet

```
HttpTester/
├── includes/
│   └── httptester.h    # Structs (t_opts, t_stats), macros couleur, prototypes
├── srcs/
│   ├── httptester.c    # Point d'entrée : init, boucle principale, routing HTTP/HTTPS
│   ├── options.c       # Parsing des options, construction de la requête, checkOpts
│   ├── http.c          # Requête HTTP plain : connect → send → recv → parse status
│   ├── https.c         # Requête HTTPS : idem + handshake TLS OpenSSL + SNI
│   ├── functions.c     # time_diff(), statistics(), intlen()
│   ├── handle.c        # Gestionnaire SIGINT : affiche les stats finales
│   └── usage.c         # Affichage de l'aide
└── Makefile            # -lssl -lcrypto en fin de commande de link
```

---

## 🧠 Fonctionnement

### Mode HTTP (`http.c`)

```
gettimeofday(&before)
    │
    ▼
socket() → connect(dst:port)
    │
    ▼
send(requête HTTP/1.1)
    │
    ▼
recv(512 bytes) → parse_status_code()
"HTTP/1.1 200 OK" → strchr(' ') → atoi() → 200
    │
    ▼
close(socket)
    │
    ▼
gettimeofday(&after) → RTT = after - before (ms)
```

### Mode HTTPS (`https.c`)

```
gettimeofday(&before)
    │
    ▼
socket() → connect(dst:port)
    │
    ▼
SSL_CTX_new(TLS_client_method())
SSL_new(ctx) → SSL_set_fd(ssl, socket)
SSL_set_tlsext_host_name()   ← SNI (vhost ou IP)
SSL_connect()                ← Handshake TLS
    │
    ▼
SSL_write(requête HTTP/1.1)
    │
    ▼
SSL_read(512 bytes) → parse_status_code()
    │
    ▼
SSL_shutdown() → SSL_free() → close() → SSL_CTX_free()
    │
    ▼
gettimeofday(&after) → RTT = after - before (ms)
```

### Routing HTTP / HTTPS (`httptester.c`)

```c
if (opts->ssl)
    code = request_ssl(opts);   // https.c
else
    code = request(opts);       // http.c
```

Le flag `ssl` est activé par `-ssl` **ou** automatiquement si le port est `443`.

---

## 📐 Codes HTTP de référence

| Code | Signification | Cause fréquente |
|------|--------------|-----------------|
| `200` | OK | Réponse normale |
| `301` / `302` | Redirection | Mauvais URI ou HTTP → HTTPS |
| `400` | Bad Request | Requête malformée |
| `403` | Forbidden | Accès refusé |
| `404` | Not Found | URI inexistant |
| `500` | Internal Server Error | Crash côté serveur |
| `0` | Pas de réponse | Connexion refusée, timeout ou erreur SSL |

---

## 👤 Auteur

**Tybbow**

---

## 📄 Licence

Ce projet est sous licence [MIT](LICENSE).