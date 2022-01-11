#!/bin/bash

# 서블릿 API를 사용해야 하므로, 빌드 시 CLASSPATH 환경 변수 설정 필요
export CLASSPATH=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/lib/servlet-api.jar
javac -encoding UTF-8 -d classes src/util/Cookies.java