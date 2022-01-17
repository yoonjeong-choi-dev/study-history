#!/bin/bash

# 개발 시 필수로 필요한 소스 코드들 빌드
# 한번만 빌드하면 됨
tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$(pwd)/classes

package="src/auth"

javac -encoding UTF-8 -d classes $package/service/User.java
javac -encoding UTF-8 -d classes $package/service/LoginFailException.java
javac -encoding UTF-8 -d classes $package/service/LoginService.java
javac -encoding UTF-8 -d classes $package/command/LoginHandler.java
javac -encoding UTF-8 -d classes $package/command/LogoutHandler.java

filter="src/filter"
javac -encoding UTF-8 -d classes $filter/LoginCheckFilter.java