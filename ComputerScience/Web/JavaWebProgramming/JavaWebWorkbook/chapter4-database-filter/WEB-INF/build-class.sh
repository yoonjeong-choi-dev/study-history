#!/bin/bash

tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$(pwd)/lib/mysql-connector-java-8.0.27.jar

javac -encoding UTF-8 -d classes src/servlets/MemberListServlet.java
javac -encoding UTF-8 -d classes src/servlets/MemberAddServlet.java
javac -encoding UTF-8 -d classes src/servlets/MemberUpdateServlet.java
javac -encoding UTF-8 -d classes src/servlets/MemberDeleteServlet.java

javac -encoding UTF-8 -d classes src/filter/CharacterEncodingFilter.java