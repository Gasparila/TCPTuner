#!/usr/bin/python
import socket
import sys
import random
import string
import time
import os
import struct
import thread


SAVE_CWND = 1
TCP_CONGESTION = 13
ADDRESS = os.environ.get("MAHIMAHI_BASE") or "127.0.0.1"
if len(sys.argv) != 3:
    print "usage: python server.py PORT TUNER"
    sys.exit(-1)

PORT = int(sys.argv[1])
SIZE = 1024
TUNER = int(sys.argv[2])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
if TUNER:
    s.setsockopt(socket.IPPROTO_TCP, TCP_CONGESTION, 'tuner')
else:
    s.setsockopt(socket.IPPROTO_TCP, TCP_CONGESTION, 'cubic')

print ADDRESS
try:
    s.connect((ADDRESS, PORT))
    print "connection established"
except socket.error as msg:
    print "cannot connect: ", msg
    sys.exit(-1)

msg = ''.join(random.choice(string.ascii_letters) for _ in range(SIZE))

starttime = time.time()
def log_cwnd (f, s):
    while True:
        # Read CWND
        # NOTE: We are parsing the first 92 bytes into a tuple where the first 7 elements are 1 byte long
        # and the next 21 are 4 bytes long. Then getting index 25 (the snd_cwnd)
        cwnd = struct.unpack("B"*7+"I"*21, s.getsockopt(socket.SOL_TCP, socket.TCP_INFO, 92))[25]
        advmss = struct.unpack("B"*7+"I"*21, s.getsockopt(socket.SOL_TCP, socket.TCP_INFO, 92))[26]
        f.write(str(cwnd * advmss) + '\n')
        time.sleep(0.2 - ((time.time() - starttime) % 0.2))

# Open a log file to print TCP info
if SAVE_CWND:
    f = open("cwnd_data.csv", 'w')
    thread.start_new_thread(log_cwnd, (f, s))

while True:
    s.send(msg)
