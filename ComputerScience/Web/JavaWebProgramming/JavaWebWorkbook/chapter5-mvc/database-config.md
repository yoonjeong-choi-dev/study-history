# 데이터 베이스 설정
```
create database javawebworkbook default character set utf8;
set global validate_password.policy=LOW;
CREATE USER 'javawebuser'@'localhost' IDENTIFIED BY 'javawebuser';
grant all privileges on javawebworkbook.* to 'javawebuser'@'localhost';
flush privileges;
```

# member 테이블 생성 
```
create table members (
	id int auto_increment primary key,
	email VARCHAR(40)  NOT NULL unique,
	password VARCHAR(100) NOT NULL,
	name VARCHAR(50)  NOT NULL,
	created_date DATETIME NOT NULL,
	modified_date DATETIME NOT NULL
) engine=InnoDB default character set = utf8;
```

# 예제 데이터 생성
```
INSERT INTO members(email,password, name,created_date, modified_date)
VALUES ('s1@test.com','1234','최윤정',now(),now());
```
```
INSERT INTO members(email,password, name,created_date, modified_date)
VALUES ('s2@test.com','1234','최윤정2',now(),now());
```