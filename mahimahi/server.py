#!/usr/bin/python
import socket
import sys
import thread

def handle_connection(conn):
    num_msg = 0
    while True:
        msg = conn.recv(1024)
        if not msg:
            break
        num_msg += 1
    print num_msg

if len(sys.argv) != 2:
    print "usage: python server.py PORT"
    sys.exit(-1)

PORT = int(sys.argv[1])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

try:
    s.bind(('', PORT))
except socket.error:
    print "bind error"
    sys.exit(-1)

s.listen(1) #only have 1 connection
print "Awaiting connection on port %d" % PORT

while (True):
    conn,_ = s.accept()
    print "Accepted connection"
    thread.start_new_thread(handle_connection, (conn,))

s.close()
