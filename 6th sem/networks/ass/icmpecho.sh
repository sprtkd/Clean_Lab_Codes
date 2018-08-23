#!/bin/sh
while [ 1 ]
do
  netstat -s | grep -A 6 IcmpMsg:
  sleep 2s
done
