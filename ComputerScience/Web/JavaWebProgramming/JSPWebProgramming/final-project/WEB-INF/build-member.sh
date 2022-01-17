#!/bin/bash

# 개발 시 필수로 필요한 소스 코드들 빌드
# 한번만 빌드하면 됨
tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$(pwd)/classes

package="src/member"
javac -encoding UTF-8 -d classes $package/model/Member.java

javac -encoding UTF-8 -d classes $package/dao/MemberDao.java

javac -encoding UTF-8 -d classes $package/service/DuplicateIdException.java
javac -encoding UTF-8 -d classes $package/service/InvalidPasswordException.java
javac -encoding UTF-8 -d classes $package/service/MemberNotFoundException.java


javac -encoding UTF-8 -d classes $package/service/JoinRequest.java
javac -encoding UTF-8 -d classes $package/service/JoinService.java
javac -encoding UTF-8 -d classes $package/service/ChangePasswordService.java

javac -encoding UTF-8 -d classes $package/command/JoinHandler.java
javac -encoding UTF-8 -d classes $package/command/ChangePasswordHandler.java