#!/bin/bash

tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

# 서블릿 API를 사용해야 하므로, 빌드 시 CLASSPATH 환경 변수 설정 필요
export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$(pwd)/classes

javac -encoding UTF-8 -d classes src/mvc/simple/SimpleController.java

javac -encoding UTF-8 -d classes src/mvc/command/CommandHandler.java
javac -encoding UTF-8 -d classes src/mvc/command/NullHandler.java

javac -encoding UTF-8 -d classes src/mvc/hello/HelloHandler.java

javac -encoding UTF-8 -d classes src/mvc/controller/ControllerUsingFile.java
javac -encoding UTF-8 -d classes src/mvc/controller/ControllerUsingURI.java