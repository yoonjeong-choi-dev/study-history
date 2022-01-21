#!/bin/bash

tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

export CLASSPATH=$tomcatDir/lib/servlet-api.jar
javac -encoding UTF-8 -d classes src/servlets/HelloWorld.java
javac -encoding UTF-8 -d classes src/servlets/CalculatorServlet.java