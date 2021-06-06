#!/bin/bash

# Server and path
FTP_SERVER=ftp.nl.debian.org
FTP_PATH=//debian/dists/Debian8.11/main/installer-i386/current/images/cdrom
REMOTE_FILE=debian-cd_info.tar.gz

# download
ftp -n << _EOF_
open $FTP_SERVER
user anonymous ${USER}@${HOSTNAME}
cd $FTP_PATH
hash
get $REMOTE_FILE
bye
_EOF_

echo "Result..."
ls -l $REMOTE_FILE