alter table rental
add constraint fk_customer_id foreign key (customer_id)
references customer (customer_id) on delete restrict;