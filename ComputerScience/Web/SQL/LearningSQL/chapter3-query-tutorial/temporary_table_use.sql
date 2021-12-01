insert into actor_j 
SELECT actor_id, first_name, last_name from actor where last_name like 'J%';