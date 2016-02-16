# TCPvil
Kernal module for tcp congestion control algorithm with user defined params for things such as slow start and AIMD

## To Run

```
make
sudo rmmod tcp_evil.ko
sudo insmod tcp_evil.ko
sudo sysctl -w net.ipv4.tcp_congestion_control=evil
```

## Sliders of Evil
### Dependencies

```
sudo apt-get install qt5-qmake qt5-default
```

### To Run

```
cd gui/SlidersOfEvil/
qmake
make
sudo ./SlidersOfEvil
```

## TCPvil's Parameters
TCPvil exposes the parameters of TCP CUBIC to the user via the Sliders of Evil. The parameters present in TCP CUBIC, along with their descriptions and default values are in the table below.

Parameter          | Description                                                                                    | Default
:----------------: | :--------------------------------------------------------------------------------------------- | :-----:
beta               | beta for multiplicative increase                                                               | 717
bic_scale          | scale (scaled by 1024) value for bic function (bic_scale/1024) (READ-ONLY)                     | 41
fast_convergence   | turn on/off fast convergence                                                                   | 1
hystart            | turn on/off hybrid slow start algorithm                                                        | 1
hystart_ack_delta  | spacing between ack's indicating train (msecs)                                                 | 2
hystart_detect     | hybrid slow start detection mechanisms 1: packet-train 2: delay 3: both packet-train and delay | 3
hystart_low_window | lower bound cwnd for hybrid slow start                                                         | 16
initial_ssthresh   | initial value of slow start threshold                                                          | 0
tcp_friendliness   | turn on/off tcp friendliness                                                                   | 1

### Additonal Parameters from ip-route

Parameter  | Description                                                                                                                           | Default
:--------: | :------------------------------------------------------------------------------------------------------------------------------------ | :------------------------------------------------------------------------:
mtu        | maximum transmission unit                                                                                                             | ?
advmss     | the Maximal Segment Size to advertise to destinations when establishing TCP connections                                               | Calculated from first hop device MTU.
rtt        | the initial RTT estimate                                                                                                              | ?
rttvar     | initial RTT variance estimate                                                                                                         | ?
reordering | maximal reordering on the path to this destination                                                                                    | Linux uses the value selected with sysctl variable net/ipv4/tcp_reordering
window     | the maximal window for TCP to advertise in bytes. This limits maximal data burst that TCP peers are allowed to send to us.            | ?
cwnd       | the clamp for congestion window. Ignored if the lock flag is not used.                                                                | ?
ssthresh   | an estimate for the intial slow start threshold                                                                                       | ?
realms     | todo                                                                                                                                  | ?
rto_min    | the minimum TCP retransmission timeout to use when communicating with this destination.                                               | ?
initcwnd   | the initial congestion window size for connections to this destination. Actual window size is this value multiplied by MSS.           | 0
initrwnd   | inital receive window size for connections to this destination. Actual window size is this value multiplied by MSS of the connection. | 0
quickack   | Enable or disable quick ack for connections to this destination                                                                       | ?
