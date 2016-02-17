#!/usr/bin/python
import socket
import sys
import random
import string
import os

ADDRESS = os.environ.get("MAHIMAHI_BASE") or "127.0.0.1"
if len(sys.argv) != 2:
    print "usage: python server.py PORT"
    sys.exit(-1)
 
PORT = int(sys.argv[1]) 
SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.connect((ADDRESS, PORT))
    print "connection established"
except socket.error as msg:
    print "cannot connect: ", msg
    sys.exit(-1)

while True:
    msg = ''.join(random.choice(string.ascii_letters) for _ in range(SIZE))
    s.send(msg)
