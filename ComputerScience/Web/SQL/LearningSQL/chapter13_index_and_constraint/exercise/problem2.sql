alter table payment
add index date_amount (payment_date, amount);

/* 생성했던 인덱스 삭제 */
alter table payment
drop index date_amount;