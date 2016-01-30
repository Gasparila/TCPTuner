# TCPvil
Kernal module for tcp congestion control algorithm with user defined params for things such as slow start and AIMD

##To Run
make<br>
sudo rmmod tcp_evil.ko<br>
sudo insmod tcp_evil.ko<br>
sudo sysctl -w net.ipv4.tcp_congestion_control=evil<br>
