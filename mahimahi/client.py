#!/usr/bin/python
import socket
import sys
import random
import string
import os

TCP_CONGESTION = 13
ADDRESS = os.environ.get("MAHIMAHI_BASE") or "127.0.0.1"
if len(sys.argv) != 3:
    print "usage: python server.py PORT EVIL"
    sys.exit(-1)

PORT = int(sys.argv[1])
SIZE = 1024
EVIL = int(sys.argv[2])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
if EVIL:
    s.setsockopt(socket.IPPROTO_TCP, TCP_CONGESTION, 'evil')
print ADDRESS
try:
    s.connect((ADDRESS, PORT))
    print "connection established"
except socket.error as msg:
    print "cannot connect: ", msg
    sys.exit(-1)

msg = ''.join(random.choice(string.ascii_letters) for _ in range(SIZE))
while True:
    s.send(msg)
