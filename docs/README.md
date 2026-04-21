# iPad Tablet Input
A low-latency system that turns an iPad into a pseudo drawing tablet for precision input for Windows PC. The system streams touch and Apple Pencil input from iPadOS to PC, where it is translated into a mouse or virtual tablet input.

# Overview
This project consists of two independant applications connected via a network protocol:
- **iPad**: captures touch or Apple Pencil input and sends it over UPD
- **PC**: receives input packets and injects them into windows as mouse or tablet input
Video translation is deliberately ignored as it is unnecessary and to reduce latency.

# Target Use Case
Primary use case:
- Precision input for games such as OSU or other games that require drawing-like inputs
- Graphic input for notetaking in Markdown-based tools
Lack of screen mirroring will restrict usage to these specific cases.

# Communication Protocol
We will use a struct transmitted over UDP in binary.
- **Protocol**: UDP
- **Format**: Binary struct
- **Update Rate**: ~60-120 Hz (as limited by iPadOS)

### Example packet structure
```c++
struct InputPacket {
    float x;            // normalized [0,1]
    float y;
    float pressure;     // optional [0,1]
    uint8_t flags;      // input state
    uint64_t timestamp;
};
```

# Development Timeline
### Phase 1: (PC-Only)
- [ ] Build UDP receiver
- [ ] Simulate input stream
- [ ] Inject mouse movement
### Phase 2: (iPad Integration)
- [ ] Build input sender in swift
- [ ] Connect to receiver
### Phase 3: Optimization
- [ ] Reduce latency
- [ ] Improve precision mapping
- [ ] Optional virtual tablet emulation
### Additional Plans
- [ ] Multi-platform support (Linux)

# Notes
This is a systems programming and real time I/O project focusing on
- low-latency networking,
- OS level input injection,
- and cross-platform architecture design

# Status
Early design phase.