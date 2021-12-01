create table person ( 
	person_id smallint unsigned auto_increment,
    fname varchar(20),
    lname varchar(20),
    eye_color enum('BR', 'BL', 'GR'),
    birth_date date,
    street varchar(30),
    city varchar(20),
    state varchar(20),
    country varchar(20),
    postal_code varchar(20),
    constraint pk_persion primary key (person_id)
);