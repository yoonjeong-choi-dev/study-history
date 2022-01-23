#!/bin/bash

tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$(pwd)/lib/*
export CLASSPATH=$CLASSPATH:$(pwd)/classes

#export CLASSPATH=$CLASSPATH:$(pwd)/lib/mysql-connector-java-8.0.27.jar
# export CLASSPATH=$CLASSPATH:$(pwd)/lib/commons-dbcp2-2.1.jar
# export CLASSPATH=$CLASSPATH:$(pwd)/lib/commons-pool2-2.4.1.jar
# export CLASSPATH=$CLASSPATH:$(pwd)/lib/reflections-0.9.9-RC1.jar

# annotaion
javac -encoding UTF-8 -d classes src/annotation/Component.java

# VO
javac -encoding UTF-8 -d classes src/vo/Member.java
javac -encoding UTF-8 -d classes src/vo/Project.java

# Dao
javac -encoding UTF-8 -d classes src/dao/MemberDao.java
javac -encoding UTF-8 -d classes src/dao/MySqlMemberDao.java

javac -encoding UTF-8 -d classes src/dao/ProjectDao.java
javac -encoding UTF-8 -d classes src/dao/MySqlProjectDao.java

# Data binding
javac -encoding UTF-8 -d classes src/bind/DataBinding.java
javac -encoding UTF-8 -d classes src/bind/ServletRequestDataBinder.java

# Page Controller
javac -encoding UTF-8 -d classes src/controls/Controller.java
javac -encoding UTF-8 -d classes src/controls/MemberListController.java
javac -encoding UTF-8 -d classes src/controls/MemberListController.java
javac -encoding UTF-8 -d classes src/controls/MemberAddController.java
javac -encoding UTF-8 -d classes src/controls/MemberUpdateController.java
javac -encoding UTF-8 -d classes src/controls/MemberDeleteController.java

javac -encoding UTF-8 -d classes src/controls/LoginController.java
javac -encoding UTF-8 -d classes src/controls/LogoutController.java

javac -encoding UTF-8 -d classes src/controls/ProjectListController.java
javac -encoding UTF-8 -d classes src/controls/ProjectAddController.java
javac -encoding UTF-8 -d classes src/controls/ProjectUpdateController.java
javac -encoding UTF-8 -d classes src/controls/ProjectDeleteController.java

# context
javac -encoding UTF-8 -d classes src/context/ApplicationContext.java

# Listener
javac -encoding UTF-8 -d classes src/listeners/ContextLoader.java


# # Front Controller
javac -encoding UTF-8 -d classes src/servlets/DispatcherServlet.java

# # Filter
javac -encoding UTF-8 -d classes src/filter/CharacterEncodingFilter.java

# server restart
yj-restart-tomcat.sh