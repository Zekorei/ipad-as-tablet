# System Architecture
## iPad Application (Swift)
Built with:
- Swift (we have to)
- Xcode, Apple IDE
- UIKit (touch input handling)
### Responsibilities
- Capture touch input (hand and Apple Pencil)
- Normalize coordinate
- Encode input as binary packets
- Transmit packets via UDP
### Constraints
- No background execution
- No system-level input injection
- Sandboxed execution environment
## PC Application (C++)
Build with:
- C++17+
- VSCode
- WinSock (networking)
- Wiin32 API (input injection)
### Responsibilities
- Receive UDP packets
- Decode binary protocol
- Map coordinates to screen space
- Inject input into OS (mouse or virtual tablet)
# Data Flow
```mermaid
flowchart TB

    subgraph S1[Input Layer]
        direction LR
        A[iPad Touch Input]
        B[UIKit Event Capture]
        C[Normalize Coordinates]
        D[Binary Packet Serialization]
        A --> B --> C --> D
    end

    subgraph S2[Network Layer]
        direction LR
        E[UDP Transmission]
        F[PC UDP Receiver]
        E --> F
    end

    subgraph S3[Processing Layer]
        direction LR
        G[Input Processing]
        H[Coordinate Mapping]
        G --> H
    end

    subgraph S4[Injection Layer]
        direction LR
        I[OS Input Injection]
        J[Target Application]
        I --> J
    end
    S1 --> S2 --> S3 --> S4
```