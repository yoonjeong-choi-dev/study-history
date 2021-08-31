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
1. Display System Information
2. Display Disk Space
3. Display Home Space Utiliztion
0. Quit
==============================================
"

    read -p "Enter selection [0-3] : "
    case $REPLY in
        0) continue
            ;;
        1) echo "Host name: $HOSTNAME"
            uptime
            sleep $DELAY
            ;;
        2) df -h
            sleep $DELAY
            ;;
        3) main_str="Home Space Utiliztion"
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
