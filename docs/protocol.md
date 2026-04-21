# Input Protocol
This document defines the binary communication protocol used between the iPad (sender) and the Windows PC (receiver)

# Overview
- **Transport**: UDP
- **Direction**: iPad $\rarr$ PC
- **Rate**: 60-120 Hz (event-driven limited by iPadOS)
- **Format**: Fixed size binary packets
- **Endianness**: Little-endian
Optimized for low latency, minimal overhead, and deterministic packet layout.

# Packet Format
Each packet represents a single event snapshot.
```c++
struct InputPacket {
    float x;
    float y;
    float pressure;
    unint8_t flags;
    unint64_t timestamp;
};
```

# Coordinate System
## iPad Space
- **Origin**: top-left
- **Range**: $[0, 1]$
- Normalized and independant of resolution or aspect ratio

## PC Space
Mapped to the screen or a user-defined region.
### Mapping Formula
```
screen_x = offset_x + (x * width)
screen_y = offset_y + (y * height)
```

# Flags (Bitmask)
Input state encoding
bit | state
----|-------
0   | touch down
1   | touch move
2   | touch up
3   | secondary touch (optional)
4-7 | reserved

# Timing Model
Input is sent immediately on event.
- No frame buffering on iPad
- PC process packets in arrival order

## Target latency budget
- **Capture**: ~1-3 ms
- **Network**: ~1-5 ms (LAN)
- **Processing**: ~1-2 ms
- **Injection**: ~1-3 ms
`total: ~5-15ms`

# Design Philosophy
Latency over reliability. Since we are sending input data continuously, as with video games, there is no need to verify each packet. In the case of packet loss, we simply wait for the device to send updated positions. We also avoid video transmission to improve latency at the cost of a call and response behaviour. Since this mimics designated drawing tablets, it is not a concern for us.