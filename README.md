Udprelay
========

Udprelay implements trivial symmetrical UDP relay. After start, it "opens" two
UDP ports and waits for clients. When clients are connected, the tool sends data 
received from one of them to another and vice versa.
Typical use case is to allow UDP clients behind different NATs to talk to each other.

One (and maybe the only) it's application is to help [Mosh](https://mosh.org) client
to connect to Mosh server behind NAT while staying behind another NAT. Details are
described in this StackOverflow [answer](https://stackoverflow.com/a/57948167/1133157).

Usage
=====

To build, just `make install`. The only mode of operation is:

```
$ udprelay bind-ip port-a port-b
```

where `bind-ip` is an IP to bind both ports to (like 0.0.0.0), `port-a` and `port-b` are UDP ports to
wait messages from.

Limitations
===========

* No security. The encription is up to user.
* Absolutely no security. Application doesn't attempt to track `port-a` and
  `port-b` remote credentials. Instead, it just sends one hand's data to the last
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
