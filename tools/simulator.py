import socket
import struct
import time
import math

PC_IP = "127.0.0.1"
PC_PORT = 5000

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Packet Format (same as structs)
# float x
# float y
# float pressure
# uint8 flags
# uint64 timestamp

PACKET_FORMAT = "fffBQ"

# test generator
def generate_input(t):
    # normalized circular motion
    x = 0.5 + 0.3 * math.cos(t)
    y = 0.5 + 0.3 * math.sin(t)

    pressure = 1.0
    flags = 0b00000010

    timestamp = int(time.time() * 1000)

    return x, y, pressure, flags, timestamp

def main():
    print(f"Sending packets to {PC_IP}: {PC_PORT}")

    start = time.time()
    
    while True:
        t = time.time() - start

        x, y, p, f, ts = generate_input(t)

        packet = struct.pack(
            PACKET_FORMAT,
            x,
            y,
            p,
            f,
            ts
        )

        sock.sendto(packet, (PC_IP, PC_PORT))

        time.sleep(1/120)

if __name__ == "__main__":
    main()