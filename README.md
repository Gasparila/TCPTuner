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

|     Parameter      | Description                             | Default value |
|:------------------:|:----------------------------------------|:-------------:|
|        beta        | The multiplicative decrease. (e.g. 1/2) |       ?       |
|     bic_scale      | ?                                       |       ?       |
|  fast_convergence  | ?                                       |       ?       |
|      hystart       | ?                                       |       ?       |
| hystart_ack_delta  | ?                                       |       ?       |
|   hystart_detect   | ?                                       |       ?       |
| hystart_low_window | ?                                       |       ?       |
|  initial_ssthresh  | ?                                       |       ?       |
|  tcp_friendliness  | ?                                       |       ?       |

In order to simplify what the user can control, the Sliders of Evil expose the following parameters.

|     Parameter      | Description                             | Default value |
|:------------------:|:----------------------------------------|:-------------:|
|        beta        | The multiplicative decrease. (e.g. 1/2) |       ?       |
|     bic_scale      | ?                                       |       ?       |
| additive_increment | ?                                       |       ?       |
|    send_window     | ?                                       |       ?       |
