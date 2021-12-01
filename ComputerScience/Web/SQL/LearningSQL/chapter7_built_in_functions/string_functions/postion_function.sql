/*
create table str_table(
    char_fld char(30),
    varchar_fld varchar(30),
    text_fld text
);

insert into str_table (char_fld, varchar_fld, text_fld)
value ( 'This string is 28 characters', 'This string is 28 characters', 'This string is 28 characters');
*/


select position('is' in char_fld)
from str_table;

select locate('is', char_fld, 5)
from str_table;