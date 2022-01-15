#!/bin/bash

tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

# 서블릿 API를 사용해야 하므로, 빌드 시 CLASSPATH 환경 변수 설정 필요
export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$(pwd)/classes


javac -encoding UTF-8 -d classes src/example/NowServlet.java
javac -encoding UTF-8 -d classes src/example/HelloServlet.java

export CLASSPATH=$CLASSPATH:$tomcatDir/webapps/yj/WEB-INF/lib/commons-dbcp2-2.1.jar
export CLASSPATH=$CLASSPATH:$tomcatDir/webapps/yj/WEB-INF/lib/commons-pool2-2.4.1.jar
export CLASSPATH=$CLASSPATH:$tomcatDir/webapps/yj/WEB-INF/lib/commons-logging-1.2.jar
javac -encoding UTF-8 -d classes src/jdbc/DBCPInit2.java