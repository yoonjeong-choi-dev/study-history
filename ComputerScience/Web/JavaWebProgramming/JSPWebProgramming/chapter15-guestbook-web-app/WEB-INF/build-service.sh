#!/bin/bash

export CLASSPATH=$(pwd)/classes

# Exceptions
javac -encoding UTF-8 -d classes src/guestbook/service/ServiceException.java
javac -encoding UTF-8 -d classes src/guestbook/service/MessageNotFoundException.java
javac -encoding UTF-8 -d classes src/guestbook/service/InvalidPassowrdException.java

# Services 
javac -encoding UTF-8 -d classes src/guestbook/service/MessageListView.java
javac -encoding UTF-8 -d classes src/guestbook/service/GetMessageListService.java
javac -encoding UTF-8 -d classes src/guestbook/service/WriteMessageService.java
javac -encoding UTF-8 -d classes src/guestbook/service/DeleteMessageService.java
javac -encoding UTF-8 -d classes src/guestbook/service/UpdateMessageService.java