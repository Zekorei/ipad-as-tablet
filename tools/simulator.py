import socket
import struct
import time
import math

PC_IP = "127.0.0.1"
PC_PORT = 5000
FRAME_RATE = 120

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Packet Format (same as structs)
# float x
# float y
# float pressure
# uint8 flags
# uint64 timestamp

PACKET_FORMAT = "fffB3xQ"

# test generator
def generate_input_circle(t):
    # normalized circular motion
    x = 0.5 + 0.25 * math.cos(t)
    y = 0.5 + 0.25 * math.sin(t)

    pressure = 1.0

    flags = 0b00000010

    timestamp = int(time.time() * 1000)

    return x, y, pressure, flags, timestamp

def generate_left_right_wave(t):
    x = 0.5 * math.sin(2*t) + 0.5
    y = 0.5

    pressure = 1.0
    flags = 0b00000010

    timestamp = int(time.time() * 1000)

    return x, y, pressure, flags, timestamp

# generate alternate click and release every interval
def generate_click(t):
    x = 0.5
    y = 0.5

    pressure = 1.0

    if int(t) % 2 == 0:
        flags = 0b00000001
    else:
        flags = 0b00000100

    timestamp = int(time.time() * 1000)

    return x, y, pressure, flags, timestamp

def main():
    print(f"Sending packets to {PC_IP}: {PC_PORT}")

    time.sleep(2)

    start = time.time()
    
    while (t := time.time() - start) < 10:
        x, y, p, f, ts = generate_left_right_wave(t)

        packet = struct.pack(
            PACKET_FORMAT,
            x,
            y,
            p,
            f,
            ts
        )

        sock.sendto(packet, (PC_IP, PC_PORT))

        time.sleep(1/FRAME_RATE)

if __name__ == "__main__":
    main()