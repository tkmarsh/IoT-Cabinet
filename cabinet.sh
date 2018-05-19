#!/bin/bash
if [ "`ping -c 1 192.168.1.50`" ]
 then
   curl 192.168.1.50:49000/?command=open
   termux-toast "Opening cabinet."
 else
  termux-toast "Error, lock offline."
fi
exit
