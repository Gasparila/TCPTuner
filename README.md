# TCPvil
Kernal module for tcp congestion control algorithm with user defined params for things such as slow start and AIMD

##To Run
make
sudo rmmod tcp_evil.ko
sudo insmod tcp_evil.ko
sudo sysctl -w net.ipv4.tcp_congestion_control=evil
