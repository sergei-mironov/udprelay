Udprelay
========

This tool implements trivial symmetrical UDP relay. After start, it "opens" two
UDP ports and sends data received from one of them to another and vice versa.
Typical use case is to allow UDP clients behind NATs talk to each other.

Usage
=====

To build, just `make install`. The only mode of operation is:

```
$ udprelay bind-ip port-a port-b
```

where `bind-ip` is IP to bind both ports to, `port-a` and `port-b` are UDP ports to
wait messages from.

Limitations
===========

* No security. The encription is up to user.
* Absolutely no security. Application doesn't attempt to track `port-a` and
  `port-b` remote credentials. Instead, it just sends one hand data to the last
  seen address of another hand.
* Udprelay drops packets from one hand before it knows the remote credentials of
  the other hand.

Debugging
=========

The following tools may be usful:

* `strace`
* `tcpdump -i IFACE udp portrange PORTA-PORTB -vv -X -n`

Credits
=======

Based on `udp_redirect` C program by Ivan Tikhonov
