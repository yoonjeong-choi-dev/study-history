#!/bin/bash

# clear bash
clear

# Main Loop
DELAY=0
IS_RUN=0

while [[ $REPLY != 0 ]]; do
    
    echo "
==============================================
Please Select:
A. Display System Information
B. Display Disk Space
C. Display Home Space Utiliztion
Q. Quit
==============================================
"

    read -p "Enter selection [0-3] : "
    case $REPLY in
        0|Q|q) REPLY=0
            continue
            ;;
        1|A|a) echo "Host name: $HOSTNAME"
            uptime
            sleep $DELAY
            ;;
        2|B|b) df -h
            sleep $DELAY
            ;;
        3|C|c) main_str="Home Space Utiliztion"
            if [[ $(id -u) -eq 0 ]]; then
                echo ${main_str} "All Users"
                du -sh /home/*
            else
                echo ${main_str} $USER
                du -sh $HOME
            fi
            sleep $DELAY
            ;;
        *) echo "Invalid entry" >&2
            sleep $DELAY
            ;;
    esac
    
done
