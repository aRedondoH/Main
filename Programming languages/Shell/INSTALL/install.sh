#!/bin/sh

if [ `id | cut -d'(' -f1 | cut -d'=' -f2` -eq "0" ]; then
    echo "Installing SNOK software"
else
    echo "Please run as root (sudo ?)"
fi

case "$1" in 
    server)
	useradd -c "SNOK daemon user" -d /dev/null -r -s /bin/false snok
	cp sbin/snok-server /usr/sbin/
	mkdir -p /etc/snok/ssl
	chmod 711 /etc/snok/ssl
	cp snok/ssl/server.* /etc/snok/ssl/
	chmod 400 /etc/snok/ssl/*
	chown snok /etc/snok/ssl/*
	cp init/snok-server /etc/init.d/
	;;
    box)
	useradd -c "SNOK daemon user" -d /dev/null -r -s /bin/false snok
	cp sbin/snok-box /usr/sbin/
	mkdir -p /etc/snok/ssl
	chmod 711 /etc/snok/ssl
	cp snok/ssl/box.* /etc/snok/ssl/
	chmod 400 /etc/snok/ssl/*
	chown snok /etc/snok/ssl/*
	cp init/snok-box /etc/init.d/
	;;
    agent)
	useradd -c "SNOK daemon user" -d /dev/null -r -s /bin/false snok
	cp sbin/snok-agent /usr/sbin/
	cp init/snok-agent /etc/init.d/
	;;
    *)
	echo "Usage: $0 [server|box|agent]"
	;;
esac

:
