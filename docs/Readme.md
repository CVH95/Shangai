# Connecting to LocoKit controller from Linux

### Connect to ad-hoc network (linux)

 - First, build up the ad-hoc mode to connect to the controller.

```sh
sudo iwconfig wlan0 mode ad-hoc essid LocoKitController01
sudo ifconfig wlan0 up
sudo ip route add 192.168.2.2 dev wlan0
sudo dhclient wlan0
ssh root@192.168.2.2
```

### Setup ad-hoc network on LocoKit controller
 - Add interface to /etc/network/interfaces:

```sh
	auto wlan0
	iface wlan0 inet static
	address 192.168.2.2
	netmask 255.255.255.0
	wireless-mode ad-hoc
	wireless-essid LocoKitController<#>
```

 - Reboot LokoKit controller

### Setup dhcp server on LocoKit controller

 - Create configuration file /etc/udhcpd.conf

```sh
	start           192.168.2.3
	end             192.168.2.10
	interface       wlan0
	max_leases      8
```

 - Create an empty leases file /var/lib/misc/udhcpd.leases
 - Create script etc/init.d/locodhcp.sh

```sh
	#!/bin/sh
	(udhcpd /etc/udhcpd.conf)&
```

 - Run `update-rc.d locodhcp.sh defaults 5` 
 - Reboot