# 🌐 HTTPTester

> **HTTP-based ping tool — measure response time of HTTP requests, like ping but at the application layer.**

![Language](https://img.shields.io/badge/language-C-blue?style=flat-square)
![Version](https://img.shields.io/badge/version-1.1-green?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS-lightgrey?style=flat-square)
![Protocol](https://img.shields.io/badge/protocol-HTTP%2F1.1-orange?style=flat-square)

---

## 📖 Description

**HTTPTester** is a lightweight C tool that behaves like `ping`, but at the **HTTP application layer**.

Instead of ICMP or TCP SYN packets, it sends real **HTTP/1.1 requests** (GET, POST, HEAD, etc.) to a target server and measures the **round-trip time (RTT)** for each response — including the full TCP connect, HTTP send, and response receive cycle. It also displays the **real HTTP status code** returned by the server.

> ℹ️ HTTPTester works over **plain HTTP only** (no TLS/HTTPS support). It uses standard TCP sockets (`SOCK_STREAM`) — no raw sockets, no root privileges required.

---

## ✨ Features

- 📡 Sends real **HTTP/1.1 requests** (GET, POST, HEAD, or any method)
- ⏱️ Measures **RTT per request** in milliseconds (full TCP connect → send → recv cycle)
- ✅ Displays the **real HTTP status code** from the server response (`200`, `301`, `404`, `500`...)
- 📊 Per-request output: HTTP response code, sequence number, RTT
- 📉 Final statistics on `^C` or end of count: transmitted, received, loss %, min/avg/max RTT
- 🏠 **Virtual host support** (`-vh`) for testing name-based vhosts behind a shared IP
- 📝 **POST data support** (`-dp`) with automatic `Content-Length` header
- 🔧 Configurable: port, URI, method, count, interval

---

## 🚀 Usage

```bash
./httptester -d [ip destination]
     optional :
         -p  [port]          (default 80)
         -i  [interval]      (default 1 second)
         -m  [METHOD]        (default GET)
         -u  [uri]           (default /)
         -vh [vhost]
         -c  [count]         (default 4)
         -dp [PostData HTTP]
         -h  display this help.
```

### Options

| Flag | Description | Default |
|------|-------------|---------|
| `-d` | Destination IP address (**required**) | — |
| `-p` | Target TCP port | `80` |
| `-m` | HTTP method (`GET`, `POST`, `HEAD`, ...) | `GET` |
| `-u` | Request URI | `/` |
| `-vh` | Virtual host (`Host:` header value) | Destination IP |
| `-c` | Number of requests to send (`-1` = unlimited) | `4` |
| `-i` | Interval between requests in seconds (float) | `1` |
| `-dp` | POST body data (requires `-m POST`) | — |
| `-h` | Display usage | — |

---

## 💡 Examples

### Basic GET request

```bash
./httptester -d 188.165.76.5
```

### GET with virtual host

```bash
./httptester -d 188.165.76.5 -p 80 -m "GET" -vh "tybbow.com"
```

**Output:**
```
from (188.165.76.5): response: (200) http_seq=1 time=17.32 ms
from (188.165.76.5): response: (200) http_seq=2 time=16.35 ms
from (188.165.76.5): response: (200) http_seq=3 time=20.73 ms
from (188.165.76.5): response: (200) http_seq=4 time=16.64 ms

--- 188.165.76.5 HTTPtester statistics ---
4 packets transmitted, 4 received, 0.00% packets loss
rtt min/avg/max = 16.35/17.76/20.73 ms
```

### Catching a redirect

```bash
./httptester -d 188.165.76.5 -u "/old-page"
```

```
from (188.165.76.5): response: (301) http_seq=1 time=15.10 ms
from (188.165.76.5): response: (301) http_seq=2 time=14.87 ms
```

### POST request with data

```bash
./httptester -d 192.168.1.10 -p 8080 -m "POST" -u "/api/login" -dp "user=admin&pass=1234" -c 10
```

### Probe a health endpoint continuously

```bash
./httptester -d 10.0.0.1 -u "/health" -i 0.5 -c -1
```

---

## 🛠️ Build

### Prerequisites

- GCC or Clang
- Linux or macOS
- `make`

> No root required — HTTPTester uses standard `SOCK_STREAM` TCP sockets.

### Compile

```bash
make
```

### Clean

```bash
make clean
```

### Run

```bash
./httptester -d  -vh 
```

---

## 🗂️ Project Structure

```
HttpTester/
├── includes/
│   └── httptester.h    # Structs (t_opts, t_stats), color macros, function prototypes
├── srcs/
│   ├── httptester.c    # Entry point: init, main loop (launch), SIGINT setup
│   ├── options.c       # Option parsing (getOpts), request builder (createRequest), checkOpts
│   ├── http.c          # TCP connect → HTTP send → recv → parse status code → close
│   ├── functions.c     # RTT calculation (time_diff), stats update, intlen helper
│   ├── handle.c        # SIGINT handler: prints final statistics and exits
│   └── usage.c         # Displays help message
└── Makefile
```

---

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
