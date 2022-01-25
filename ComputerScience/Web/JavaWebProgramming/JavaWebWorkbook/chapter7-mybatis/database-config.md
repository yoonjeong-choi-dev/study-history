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

# 프로젝트 테이블 생성
```
CREATE TABLE projects (
	id int auto_increment primary key,
	title VARCHAR(255)  NOT NULL,
    content text not null,
    start_date datetime not null,
    end_date datetime not null,
	created_date DATETIME NOT NULL,
    state int not null,
    tags varchar(255) null
) engine=InnoDB default character set = utf8;
```

# 프로젝트 멤버 테이블 생성
```
CREATE TABLE project_memebers (
	project_id int not null,
	member_id int not null,
	level int not null,
    state int not null,
    modified_data DATETIME NOT NULL,
    constraint project_memebers_PK primary key(project_id, member_id)
) engine=InnoDB default character set = utf8;
```

# 예제 데이터 생성
```
INSERT INTO projects (title,content,start_date,end_date,state,created_date,tags)
VALUES ('프로젝트1','내용1','2021-1-23','2021-2-1',0,NOW(),'java');
```
```
INSERT INTO projects (title,content,start_date,end_date,state,created_date,tags)
VALUES ('프로젝트2','내용2','2022-1-13','2021-2-28',0,NOW(),'javaweb');
```