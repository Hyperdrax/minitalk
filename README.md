*This project has been created as part of the 42 curriculum by flhensel.*

## Description

Minitalk is a client-server communication program that demonstrates inter-process communication (IPC) using UNIX signals. The project consists of two programs:

- **Server**: Waits for incoming messages and displays them
- **Client**: Sends a string message to the server using its PID

The challenge lies in transmitting text data using only two signals: `SIGUSR1` and `SIGUSR2`. Each character is sent bit-by-bit, requiring careful signal handling and synchronization between processes.

**Key Features:**
- Bit-level data transmission using only UNIX signals
- Bidirectional acknowledgment system for reliable communication
- Support for multiple sequential client connections
- Robust error handling and timeout management
- Dynamic buffer allocation for messages of any length

## Instructions

### Compilation

To compile the project, run:
```bash
make
```

This will create two executables: `server` and `client`.

**Available make targets:**
- `make` or `make all` - Compile both server and client
- `make clean` - Remove object files
- `make fclean` - Remove object files and executables
- `make re` - Rebuild the entire project

### Usage

1. **Start the server:**
```bash
./server
```
The server will display its PID, which you'll need for the client.

Example output:
```
Server's ID : 12345
Waiting for a message...
```

2. **Send a message from the client:**
```bash
./client <server_PID> "Your message here"
```

Example:
```bash
./client 12345 "Hello, World!"
```

### Examples

**Basic usage:**
```bash
# Terminal 1
./server
# Server's ID : 12345
# Waiting for a message...

# Terminal 2
./client 12345 "Hello from client!"
# ✅ Message delivered!

# Terminal 1 will display:
# Hello from client!
```

**Multiple messages:**
The server can receive multiple messages without restarting:
```bash
./client 12345 "First message"
./client 12345 "Second message"
./client 12345 "Third message"
```

**Error handling:**
```bash
# Invalid PID
./client 0 "test"
# Error: Invalid PID

# Wrong number of arguments
./client 12345
# Error: The correct format is ./client <PID> <message>
```

## Technical Implementation

### Signal Protocol

The communication protocol works as follows:

1. **Client** sends each character bit-by-bit (MSB first):
   - `SIGUSR1` represents bit `1`
   - `SIGUSR2` represents bit `0`

2. **Server** acknowledges each bit with `SIGUSR1`

3. When a null terminator is received, **server** sends `SIGUSR2` to confirm message completion

4. **Client** waits for acknowledgment before sending the next bit (prevents signal loss)

### Architecture

**Server (`server.c`):**
- Uses `sigaction` with `SA_SIGINFO` to get sender's PID
- Accumulates bits into bytes (8 bits = 1 character)
- Dynamic buffer allocation grows as needed
- Sends acknowledgment signals back to client

**Client (`client.c`):**
- Validates server PID and message
- Sends each bit with timeout/retry mechanism
- Waits for confirmation before proceeding
- Includes null terminator for message completion

## Resources

### UNIX Signals
- [Linux Signal Manual](https://man7.org/linux/man-pages/man7/signal.7.html) - Comprehensive signal documentation
- [sigaction(2)](https://man7.org/linux/man-pages/man2/sigaction.2.html) - Signal handling with sigaction
- [kill(2)](https://man7.org/linux/man-pages/man2/kill.2.html) - Sending signals between processes
- [Beej's Guide to Unix IPC](https://beej.us/guide/bgipc/html/split/signals.html) - Inter-process communication tutorial

### Tutorials & Articles
- [Unix Signals - GeeksforGeeks](https://www.geeksforgeeks.org/signals-c-language/) - Signal basics in C
- [Understanding SIGUSR1 and SIGUSR2](https://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/) - User-defined signals

### AI Usage

AI assistance was used for Debugging & Understanding the Topic.

All core logic, signal handling implementation, and protocol design were developed independently. AI was primarily used as a debugging tool rather than for code generation.
