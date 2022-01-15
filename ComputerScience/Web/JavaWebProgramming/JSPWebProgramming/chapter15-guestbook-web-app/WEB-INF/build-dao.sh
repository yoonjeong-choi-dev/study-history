#!/bin/bash

export CLASSPATH=$(pwd)/classes

# model 빌드
javac -encoding UTF-8 -d classes src/guestbook/model/Message.java

# dao 빌드
javac -encoding UTF-8 -d classes src/guestbook/dao/MessageDao.java