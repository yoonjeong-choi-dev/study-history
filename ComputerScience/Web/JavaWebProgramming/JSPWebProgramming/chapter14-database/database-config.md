# 데이터 베이스 설정
```
create database jpa14 default character set utf8;
set global validate_password.policy=LOW;
CREATE USER 'jpadbuser'@'localhost' IDENTIFIED BY 'jpadbuser';
grant all privileges on jpa14.* to 'jpadbuser'@'localhost';
flush privileges;
```

# member 테이블 생성 
```
create table member (
	member_id varchar(10) not null primary key,
    password varchar(10) not null,
    name varchar(20) not null,
    email varchar(80),
    description varchar(80)
) engine=InnoDB default character set = utf8;
```

# memo 테이블 생성
```
create table memo (
	id int(10) not null auto_increment primary key,
    data long varchar
)engine=InnoDB default character set = utf8;
```