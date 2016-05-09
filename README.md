# TCPTuner
TCPTuner is TCP congestion control kernel module and GUI packaged together. By loading our kernel module (which is essentially a clone of CUBIC), and running the GUI, users can adjust several parameters of the CUBIC congestion control algorithm.

See the [TCPTuner Paper (PDF)](https://arxiv.org/ftp/arxiv/papers/1605/1605.01987.pdf) for more information about the background, implementation, and contributions of TCPTuner.

## How to Build and Load the Kernel Module

```
cd module/
make
sudo rmmod tcp_tuner.ko
sudo insmod tcp_tuner.ko
sudo sysctl -w net.ipv4.tcp_congestion_control=tuner
```

## The TCPTuner GUI
### Dependencies

```
sudo apt-get install qt5-qmake qt5-default
```

### To Build and Run

```
cd gui/TCPTuner/
qmake
make
sudo ./TCPTuner
```

## TCPTuner's Parameters
TCPTuner exposes the parameters of TCP CUBIC to the user via the TCPTuner GUI. The parameters present in TCP CUBIC, along with their descriptions and default values are in the table below.

Parameter        | Description                                                                 | Default
:--------------: | :-------------------------------------------------------------------------- | :-----:
alpha            | Scales W_max, which adjusts the rate at which cwnd grows after a loss event | 512
beta             | beta for multiplicative decrease                                            | 717
fast_convergence | turn on/off fast convergence                                                | 1
tcp_friendliness | turn on/off tcp friendliness                                                | 1

### Additonal Parameters from ip-route
The TCPTuner GUI also provides access to the following `ip route` parameters. The GUI will apply these `ip route` parameters to all of the routes in the routing table.

Parameter | Description                                                                                                                 | Default
:-------: | :-------------------------------------------------------------------------------------------------------------------------- | :------:
rto_min   | the minimum TCP retransmission timeout to use when communicating with this destination.                                     | None
initcwnd  | the initial congestion window size for connections to this destination. Actual window size is this value multiplied by MSS. | 0

## MahiMahi Simulation Environment
This repository also contains a [MahiMahi](http://mahimahi.mit.edu/) simulation environment so that users can see the impact of TCP congestion control parameters.

### Dependencies
First, you must install MahiMahi:
```
sudo add-apt-repository ppa:keithw/mahimahi
sudo apt-get update
sudo apt-get install mahimahi
```

Before you can run MahiMahi, you must set ip_forward=1
```
sudo sysctl -w net.ipv4.ip_forward=1
```

Now, tcp_tuner should be set as the congestion control algorithm.

### Single Flow, Tail-drop Buffer
The first simulation shows throughput and delay of a single TCP flow on a 12Mbps uplink.

```
cd mahimahi/
./start_all
```

### Two Flows Sharing Bottleneck
The second simulation shows throughput graphs of each flow sharing a bottleneck link. This can be used to compare default cubic to tcp_tuner.

```
cd mahimahi/
./start_shell
```

Now that the bottleneck link is created, we can run multiple clients within that shell.

```
./start_client 5050 1 & <-- creates an tuner client in a new process
./start_client 5050 0 & <-- creates a cubic client in a new process
```

To close these
```
fg <--to bring one of the kid process to the foreground
Ctrl+C
(repeat for each client)
exit <-- to exit the shell
```
