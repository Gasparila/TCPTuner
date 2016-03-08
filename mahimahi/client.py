#!/usr/bin/python
import socket
import sys
import random
import string
import time
import os
import struct

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
print ADDRESS
try:
    s.connect((ADDRESS, PORT))
    print "connection established"
except socket.error as msg:
    print "cannot connect: ", msg
    sys.exit(-1)

msg = ''.join(random.choice(string.ascii_letters) for _ in range(SIZE))

# Open a log file to print TCP info
if SAVE_CWND:
    f = open("cwnd_data.csv", 'w')
    starttime = time.time()

while True:
    if ((time.time()-starttime) >= 0.2 and SAVE_CWND):
        starttime = time.time()
        # Read CWND
        f.write(str(struct.unpack("B"*7+"I"*21, s.getsockopt(socket.SOL_TCP, socket.TCP_INFO, 92))[25]) + '\n')

    s.send(msg)
