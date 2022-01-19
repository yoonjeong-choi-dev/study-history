#!/bin/bash

# 개발 시 필수로 필요한 소스 코드들 빌드
# 한번만 빌드하면 됨
tomcatDir=/home/yjchoi/apps/tomcat/apache-tomcat-8.5.73/

export CLASSPATH=$tomcatDir/lib/servlet-api.jar
export CLASSPATH=$CLASSPATH:$(pwd)/classes

package="src/article"

javac -encoding UTF-8 -d classes $package/model/Writer.java
javac -encoding UTF-8 -d classes $package/model/Article.java
javac -encoding UTF-8 -d classes $package/model/ArticleContent.java
javac -encoding UTF-8 -d classes $package/model/ArticleData.java

javac -encoding UTF-8 -d classes $package/dao/ArticleDao.java
javac -encoding UTF-8 -d classes $package/dao/ArticleContentDao.java

javac -encoding UTF-8 -d classes $package/service/PermissionDeniedException.java
javac -encoding UTF-8 -d classes $package/service/ArticleNotFoundException.java
javac -encoding UTF-8 -d classes $package/service/ArticleContentNotFoundException.java


javac -encoding UTF-8 -d classes $package/service/WriteRequest.java
javac -encoding UTF-8 -d classes $package/service/WriteArticleService.java

javac -encoding UTF-8 -d classes $package/service/ArticlePage.java
javac -encoding UTF-8 -d classes $package/service/ListAritcleService.java

javac -encoding UTF-8 -d classes $package/service/ReadArticleService.java

javac -encoding UTF-8 -d classes $package/service/ModifyRequest.java
javac -encoding UTF-8 -d classes $package/service/ModifyArticleService.java

javac -encoding UTF-8 -d classes $package/service/DeleteArticleService.java

javac -encoding UTF-8 -d classes $package/command/WriteArticleHandler.java
javac -encoding UTF-8 -d classes $package/command/ListArticleHandler.java
javac -encoding UTF-8 -d classes $package/command/ReadArticleHandler.java
javac -encoding UTF-8 -d classes $package/command/ModifyArticleHandler.java
javac -encoding UTF-8 -d classes $package/command/DeleteArticleHandler.java