# 데이터 베이스 설정
```
create database jsp_board default character set utf8;
set global validate_password.policy=LOW;
CREATE USER 'jspdbuser'@'localhost' IDENTIFIED BY 'jspdbuser';
grant all privileges on jsp_board.* to 'jspdbuser'@'localhost';
flush privileges;
```

# 멤버 테이블 생성 
```
create table jsp_board.member (
	member_id varchar(50) primary key,
    name varchar(50) not null,
    password varchar(20) not null,
    registered_date datetime not null
) engine=InnoDB default character set = utf8;
```

# 게시글 테이블 생성
```
create table jsp_board.article (
	article_id int auto_increment primary key,
    writer_id varchar(50) not null,
	writer_name varchar(50) not null,
    title varchar(255) not null,
    registered_date datetime not null,
    modified_date datetime not null,
    read_count int
) engine=InnoDB default character set = utf8;
```

# 게시글 내용 테이블 생성
```
create table jsp_board.article_content (
	article_id int primary key,
    content text
) engine=InnoDB default character set = utf8;
```