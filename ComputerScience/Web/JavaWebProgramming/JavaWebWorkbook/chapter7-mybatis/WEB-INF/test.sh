#!/bin/bash

tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$(pwd)/lib/*
export CLASSPATH=$CLASSPATH:$(pwd)/classes

javac -encoding UTF-8 -d classes src/context/ApplicationContext.java
javac -encoding UTF-8 -d classes src/listeners/ContextLoader.java

# server restart
yj-restart-tomcat.sh