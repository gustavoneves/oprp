#!/bin/bash
  
AVG_host1=`ping -c 5 1.1.1.1 | grep rtt | awk -F "/" '{print $5}'`
AVG_host2=`ping -c 5 1.1.1.1 | grep rtt | awk -F "/" '{print $5}'`
AVG_host3=`ping -c 5 1.1.1.1 | grep rtt | awk -F "/" '{print $5}'`
AVG_host4=`ping -c 5 1.1.1.1 | grep rtt | awk -F "/" '{print $5}'`
AVG_host5=`ping -c 5 1.1.1.1 | grep rtt | awk -F "/" '{print $5}'`

echo $TESTE
