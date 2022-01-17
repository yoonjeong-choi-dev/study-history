# 데이터 베이스 설정
```
create database jsp_board default character set utf8;
set global validate_password.policy=LOW;
CREATE USER 'jspdbuser'@'localhost' IDENTIFIED BY 'jspdbuser';
grant all privileges on jsp_board.* to 'jspdbuser'@'localhost';
flush privileges;
```

# 유저 테이블 생성 
```
create table jsp_board.member (
	member_id varchar(50) primary key,
    name varchar(50) not null,
    password varchar(20) not null,
    registered_date datetime not null
) engine=InnoDB default character set = utf8;
```
