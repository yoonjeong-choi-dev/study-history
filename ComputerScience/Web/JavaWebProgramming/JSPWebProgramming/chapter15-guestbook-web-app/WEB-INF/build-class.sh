#!/bin/bash

tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

# 서블릿 API 및 dbcp 관련 CLASSPATH 환경 변수 설정 필요
export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$tomcatDir/webapps/yj/WEB-INF/lib/commons-dbcp2-2.1.jar
export CLASSPATH=$CLASSPATH:$tomcatDir/webapps/yj/WEB-INF/lib/commons-pool2-2.4.1.jar
export CLASSPATH=$CLASSPATH:$tomcatDir/webapps/yj/WEB-INF/lib/commons-logging-1.2.jar

# JDBC 관련 빌드
javac -encoding UTF-8 -d classes src/jdbc/DBCPInit.java
javac -encoding UTF-8 -d classes src/jdbc/JdbcUtil.java
javac -encoding UTF-8 -d classes src/jdbc/connection/ConnectionProvider.java
