# 데이터 베이스 설정
```
create database jsp_guestbook default character set utf8;
set global validate_password.policy=LOW;
CREATE USER 'jspdbuser'@'localhost' IDENTIFIED BY 'jspdbuser';
grant all privileges on jsp_guestbook.* to 'jspdbuser'@'localhost';
flush privileges;
```

# guestbook_message 테이블 생성 
```
create table guestbook_message (
	message_id int not null auto_increment primary key,
    guest_name varchar(50) not null,
    password varchar(10) not null,
    message text not null
) engine=InnoDB default character set = utf8;
```
