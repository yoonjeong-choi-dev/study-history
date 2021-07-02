#!/bin/bash

echo "Run 'unix-log-example.go' !!"
go run unix-log-example.go

echo "Now Check Log files........"

echo "syslog.LOG_LOCAL7 is written in /var/log/syslog"
cat /var/log/syslog | grep LOG_

echo "syslog.LOG_MAIL is written in /var/log/syslog and /var/log/mail.log"
cat /var/log/syslog | grep LOG_
cat /var/log/mail.log | grep LOG_

