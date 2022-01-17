#!/bin/bash

# 개발 시 필수로 필요한 소스 코드들 빌드
# 한번만 빌드하면 됨
tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

# 서블릿 API를 사용해야 하므로, 빌드 시 CLASSPATH 환경 변수 설정 필요
export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$tomcatDir/webapps/yj/WEB-INF/lib/commons-dbcp2-2.1.jar
export CLASSPATH=$CLASSPATH:$tomcatDir/webapps/yj/WEB-INF/lib/commons-pool2-2.4.1.jar
export CLASSPATH=$CLASSPATH:$tomcatDir/webapps/yj/WEB-INF/lib/commons-logging-1.2.jar
export CLASSPATH=$CLASSPATH:$(pwd)/classes

# jdbc
javac -encoding UTF-8 -d classes src/jdbc/DBCPInitListener.java
javac -encoding UTF-8 -d classes src/jdbc/JdbcUtil.java
javac -encoding UTF-8 -d classes src/jdbc/connection/ConnectionProvider.java

# util filter
javac -encoding UTF-8 -d classes src/util/CharacterEncodingFilter.java

# Controller for MVC
javac -encoding UTF-8 -d classes src/mvc/command/CommandHandler.java
javac -encoding UTF-8 -d classes src/mvc/command/NullHandler.java
javac -encoding UTF-8 -d classes src/mvc/controller/ControllerUsingURI.java