create database springbootReactTutorial default character set utf8;
CREATE USER 'springbootReactTutorialUser'@'localhost' IDENTIFIED BY 'springbootReactTutorialPassword';
grant all privileges on springbootReactTutorial.* to 'springbootReactTutorialUser'@'localhost';
flush privileges;

