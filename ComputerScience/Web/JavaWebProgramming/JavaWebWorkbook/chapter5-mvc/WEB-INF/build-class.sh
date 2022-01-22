#!/bin/bash

tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$(pwd)/classes
export CLASSPATH=$CLASSPATH:$(pwd)/lib/mysql-connector-java-8.0.27.jar
export CLASSPATH=$CLASSPATH:$(pwd)/lib/commons-dbcp2-2.1.jar
export CLASSPATH=$CLASSPATH:$(pwd)/lib/commons-pool2-2.4.1.jar

# util
javac -encoding UTF-8 -d classes src/util/DBConnectionPool.java

# VO
javac -encoding UTF-8 -d classes src/vo/Member.java

# Dao
javac -encoding UTF-8 -d classes src/dao/MemberDao.java

# Listener
javac -encoding UTF-8 -d classes src/listeners/ContextLoader.java

# Servlet
# ContextLoader 로 기능 옮김
##javac -encoding UTF-8 -d classes src/servlets/AppInitServlet.java

javac -encoding UTF-8 -d classes src/servlets/MemberListServlet.java
javac -encoding UTF-8 -d classes src/servlets/MemberAddServlet.java
javac -encoding UTF-8 -d classes src/servlets/MemberUpdateServlet.java
javac -encoding UTF-8 -d classes src/servlets/MemberDeleteServlet.java

javac -encoding UTF-8 -d classes src/servlets/LoginServlet.java
javac -encoding UTF-8 -d classes src/servlets/LogoutServlet.java

# Filter
javac -encoding UTF-8 -d classes src/filter/CharacterEncodingFilter.java


# server restart
yj-restart-tomcat.sh