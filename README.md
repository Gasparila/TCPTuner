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
TCPvil exposes the parameters of TCP CUBIC to the user via the Sliders of Evil. The parameters present in TCP CUBIC, along with their descriptions are in the table below.

Parameter          | Description                                                                                    | Default
:----------------: | :--------------------------------------------------------------------------------------------- | :-----:
beta               | beta for multiplicative increase                                                               | 717
bic_scale          | scale (scaled by 1024) value for bic function (bic_scale/1024)                                 | 41
fast_convergence   | turn on/off fast convergence                                                                   | 1
hystart            | turn on/off hybrid slow start algorithm                                                        | 1
hystart_ack_delta  | spacing between ack's indicating train (msecs)                                                 | 2
hystart_detect     | hybrid slow start detection mechanisms 1: packet-train 2: delay 3: both packet-train and delay | 3
hystart_low_window | lower bound cwnd for hybrid slow start                                                         | 16
initial_ssthresh   | initial value of slow start threshold                                                          | 0
tcp_friendliness   | turn on/off tcp friendliness                                                                   | 1

In order to simplify what the user can control, the Sliders of Evil expose the following parameters.

Parameter          | Description                                                                                    | Default
:----------------: | :--------------------------------------------------------------------------------------------- | :-----:
beta               | beta for multiplicative increase                                                               | 717
bic_scale          | scale (scaled by 1024) value for bic function (bic_scale/1024)                                 | 41
additive_increment | ?                                                                                              | ?
send_window        | ?                                                                                              | ?
fast_convergence   | turn on/off fast convergence                                                                   | 1
hystart            | turn on/off hybrid slow start algorithm                                                        | 1
hystart_ack_delta  | spacing between ack's indicating train (msecs)                                                 | 2
hystart_detect     | hybrid slow start detection mechanisms 1: packet-train 2: delay 3: both packet-train and delay | 3
hystart_low_window | lower bound cwnd for hybrid slow start                                                         | 16
initial_ssthresh   | initial value of slow start threshold                                                          | 0
tcp_friendliness   | turn on/off tcp friendliness                                                                   | 1
