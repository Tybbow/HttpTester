<<<<<<< HEAD
#🌐 HTTPTester

> **HTTP/HTTPS-based ping tool — measure response time of HTTP requests, like ping but at the application layer.**
=======
# 🌐 HTTPTester

> **HTTP-based ping tool — measure response time of HTTP requests, like ping but at the application layer.**
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342

![Language](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Version](https://img.shields.io/badge/version-1.1-green?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey?style=flat-square)
<<<<<<< HEAD
![Protocol](https://img.shields.io/badge/protocol-HTTP%20%7C%20HTTPS-orange?style=flat-square)
![OpenSSL](https://img.shields.io/badge/OpenSSL-libssl--dev-red?style=flat-square)
=======
![Protocol](https://img.shields.io/badge/protocol-HTTP%2F1.1-orange?style=flat-square)
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342

---

## 📖 Description

**HTTPTester** is a lightweight C tool that behaves like `ping`, but at the **HTTP application layer**.

<<<<<<< HEAD
Instead of ICMP or TCP SYN packets, it sends real **HTTP/1.1 requests** (GET, POST, HEAD, etc.) to a target server and measures the **round-trip time (RTT)** for each response — including the full TCP connect, HTTP send, and response receive cycle. It displays the **real HTTP status code** returned by the server, and supports both **plain HTTP** and **HTTPS** via OpenSSL.

> ℹ️ HTTPTester uses standard TCP sockets (`SOCK_STREAM`) — no raw sockets, **no root privileges required**.
=======
Instead of ICMP or TCP SYN packets, it sends real **HTTP/1.1 requests** (GET, POST, HEAD, etc.) to a target server and measures the **round-trip time (RTT)** for each response — including the full TCP connect, HTTP send, and response receive cycle. It also displays the **real HTTP status code** returned by the server.

> ℹ️ HTTPTester works over **plain HTTP only** (no TLS/HTTPS support). It uses standard TCP sockets (`SOCK_STREAM`) — no raw sockets, no root privileges required.
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342

---

## ✨ Features

- 📡 Sends real **HTTP/1.1 requests** (GET, POST, HEAD, or any method)
- ⏱️ Measures **RTT per request** in milliseconds (full TCP connect → send → recv cycle)
- ✅ Displays the **real HTTP status code** from the server response (`200`, `301`, `404`, `500`...)
<<<<<<< HEAD
- 🔒 **HTTPS support** via OpenSSL (`-ssl` flag or auto-detection on port 443)
- 🏠 **Virtual host support** (`-vh`) with automatic **SNI** injection for HTTPS
- 📊 Per-request output: HTTP response code, sequence number, RTT
- 📉 Final statistics on `^C` or end of count: transmitted, received, loss %, min/avg/max RTT
=======
- 📊 Per-request output: HTTP response code, sequence number, RTT
- 📉 Final statistics on `^C` or end of count: transmitted, received, loss %, min/avg/max RTT
- 🏠 **Virtual host support** (`-vh`) for testing name-based vhosts behind a shared IP
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342
- 📝 **POST data support** (`-dp`) with automatic `Content-Length` header
- 🔧 Configurable: port, URI, method, count, interval

---

## 🚀 Usage

```bash
./httptester -d [ip destination]
     optional :
<<<<<<< HEAD
         -p   [port]          (default 80)
         -i   [interval]      (default 1 second)
         -m   [METHOD]        (default GET)
         -u   [uri]           (default /)
         -vh  [vhost]
         -c   [count]         (default 4)
         -dp  [PostData HTTP]
         -ssl                 (force HTTPS, auto-enabled if port 443)
         -h   display this help.
=======
         -p  [port]          (default 80)
         -i  [interval]      (default 1 second)
         -m  [METHOD]        (default GET)
         -u  [uri]           (default /)
         -vh [vhost]
         -c  [count]         (default 4)
         -dp [PostData HTTP]
         -h  display this help.
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342
```

### Options

| Flag | Description | Default |
|------|-------------|---------|
| `-d` | Destination IP address (**required**) | — |
| `-p` | Target TCP port | `80` |
| `-m` | HTTP method (`GET`, `POST`, `HEAD`, ...) | `GET` |
| `-u` | Request URI | `/` |
<<<<<<< HEAD
| `-vh` | Virtual host (`Host:` header + SNI for HTTPS) | Destination IP |
| `-c` | Number of requests (`-1` = unlimited) | `4` |
| `-i` | Interval between requests in seconds (float) | `1` |
| `-dp` | POST body data (requires `-m POST`) | — |
| `-ssl` | Force HTTPS/TLS (auto-enabled if port is `443`) | disabled |
=======
| `-vh` | Virtual host (`Host:` header value) | Destination IP |
| `-c` | Number of requests to send (`-1` = unlimited) | `4` |
| `-i` | Interval between requests in seconds (float) | `1` |
| `-dp` | POST body data (requires `-m POST`) | — |
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342
| `-h` | Display usage | — |

---

## 💡 Examples

<<<<<<< HEAD
### Basic HTTP GET

```bash
./httptester -d 188.165.76.5 -vh "tybbow.com"
=======
### Basic GET request

```bash
./httptester -d 188.165.76.5
```

### GET with virtual host

```bash
./httptester -d 188.165.76.5 -p 80 -m "GET" -vh "tybbow.com"
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342
```

**Output:**
```
<<<<<<< HEAD
[+] Mode: HTTP  (port 80)

=======
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342
from (188.165.76.5): response: (200) http_seq=1 time=17.32 ms
from (188.165.76.5): response: (200) http_seq=2 time=16.35 ms
from (188.165.76.5): response: (200) http_seq=3 time=20.73 ms
from (188.165.76.5): response: (200) http_seq=4 time=16.64 ms

--- 188.165.76.5 HTTPtester statistics ---
4 packets transmitted, 4 received, 0.00% packets loss
rtt min/avg/max = 16.35/17.76/20.73 ms
```

<<<<<<< HEAD
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
=======
### Catching a redirect
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342

```bash
./httptester -d 188.165.76.5 -u "/old-page"
```

```
from (188.165.76.5): response: (301) http_seq=1 time=15.10 ms
<<<<<<< HEAD
```

### POST avec données
=======
from (188.165.76.5): response: (301) http_seq=2 time=14.87 ms
```

### POST request with data
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342

```bash
./httptester -d 192.168.1.10 -p 8080 -m "POST" -u "/api/login" -dp "user=admin&pass=1234" -c 10
```

<<<<<<< HEAD
### Probe continu sur un endpoint de santé
=======
### Probe a health endpoint continuously
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342

```bash
./httptester -d 10.0.0.1 -u "/health" -i 0.5 -c -1
```

---

## 🛠️ Build

<<<<<<< HEAD
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
=======
### Prerequisites

- GCC or Clang
- Linux or macOS
- `make`

> No root required — HTTPTester uses standard `SOCK_STREAM` TCP sockets.

### Compile
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342

```bash
make
```

<<<<<<< HEAD
### Nettoyer

```bash
make clean    # supprime les .o
make fclean   # supprime les .o + le binaire
make re       # recompile tout
```

### Lancer

```bash
./httptester -d  [-p ] [-ssl] [-vh ]
=======
### Clean

```bash
make clean
```

### Run

```bash
./httptester -d  -vh 
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342
```

---

<<<<<<< HEAD
## 🗂️ Structure du projet
=======
## 🗂️ Project Structure
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342

```
HttpTester/
├── includes/
<<<<<<< HEAD
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
=======
│   └── httptester.h    # Structs (t_opts, t_stats), color macros, function prototypes
├── srcs/
│   ├── httptester.c    # Entry point: init, main loop (launch), SIGINT setup
│   ├── options.c       # Option parsing (getOpts), request builder (createRequest), checkOpts
│   ├── http.c          # TCP connect → HTTP send → recv → parse status code → close
│   ├── functions.c     # RTT calculation (time_diff), stats update, intlen helper
│   ├── handle.c        # SIGINT handler: prints final statistics and exits
│   └── usage.c         # Displays help message
└── Makefile
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342
```

---

<<<<<<< HEAD
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
=======
## 🧠 How It Works

HTTPTester uses a simple **single-threaded sequential** approach — one request at a time, no raw sockets needed.

```
For each probe:

  gettimeofday(&before)
       │
       ▼
  socket() → connect(dst:port)
       │
       ▼
  send(HTTP request)
  ┌─────────────────────────────────────────┐
  │  METHOD URI HTTP/1.1\r\n                │
  │  Host: <vhost or dst>\r\n               │
  │  [Content-Length: N\r\n]  (POST only)   │
  │  \r\n                                   │
  │  [postdata]               (POST only)   │
  └─────────────────────────────────────────┘
       │
       ▼
  recv(server_reply, 512 bytes)
       │
       ▼
  parse_status_code()
  "HTTP/1.1 200 OK" → strchr(' ') → atoi() → 200
       │
       ▼
  close(socket)
       │
       ▼
  gettimeofday(&after)
  RTT = after - before (ms)
```

### HTTP Status Code Parsing (`http.c`)

The server response always starts with `HTTP/1.x NNN Reason`. `parse_status_code()` locates the first space with `strchr()`, reads the 3-digit code with `atoi()`, and validates it is in the `100–599` range. A return value of `0` indicates a connection failure or malformed response.

---

## 📐 HTTP Status Codes Reference

| Code | Meaning | Example cause |
|------|---------|---------------|
| `200` | OK | Normal response |
| `301` / `302` | Redirect | Wrong URI or HTTP→HTTPS redirect |
| `400` | Bad Request | Malformed request |
| `403` | Forbidden | Access denied |
| `404` | Not Found | Wrong URI |
| `500` | Internal Server Error | Server-side crash |
| `0` | No response | Connection refused or timeout |

---

## ⚠️ Known Limitations

- **HTTP only** — no TLS/HTTPS support. For HTTPS targets, consider using `curl` or `openssl s_client`.
- **No DNS resolution** — destination must be specified as an IP address.
- **512-byte receive buffer** — only the beginning of the HTTP response is captured, sufficient for status code extraction and RTT measurement.

---

## 👤 Author

**Tybbow**  

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).
>>>>>>> 3c20d45e299fa25d5b414ae8ea6b94109c674342
