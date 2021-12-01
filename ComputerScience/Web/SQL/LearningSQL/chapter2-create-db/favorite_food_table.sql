create table favorite_food (
	person_id smallint unsigned,
	food varchar(20),
    constraint pk_favorite_food primary key(person_id, food),
    constraint fk_fav_food_person_id foreign key(person_id) references person (person_id)
);