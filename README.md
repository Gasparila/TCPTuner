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

## MahiMahi Simulation Environment
### To Run

```
cd mahimahi
sudo sysctl -w net.ipv4.ip_forward=1
```

Note that for best results, evil should be an allowed congestion control algorithm, but should not be set. To do this, you can run

```
sudo sysctl -w net.ipv4.tcp_congestion_control=evil
sudo sysctl -w net.ipv4.tcp_congestion_control=cubic
```

## TCPvil's Parameters
TCPvil exposes the parameters of TCP CUBIC to the user via the Sliders of Evil. The parameters present in TCP CUBIC, along with their descriptions and default values are in the table below.

Parameter        | Description                                                                 | Default
:--------------: | :-------------------------------------------------------------------------- | :-----:
alpha            | Scales W_max, which adjusts the rate at which cwnd grows after a loss event | 512
beta             | beta for multiplicative increase                                            | 717
fast_convergence | turn on/off fast convergence                                                | 1
tcp_friendliness | turn on/off tcp friendliness                                                | 1

### Additonal Parameters from ip-route

Parameter | Description                                                                                                                 | Default
:-------: | :-------------------------------------------------------------------------------------------------------------------------- | :-----:
rto_min   | the minimum TCP retransmission timeout to use when communicating with this destination.                                     | None
initcwnd  | the initial congestion window size for connections to this destination. Actual window size is this value multiplied by MSS. | 0
