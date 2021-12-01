/*
create table str_table(
    char_fld char(30),
    varchar_fld varchar(30),
    text_fld text
);

insert into str_table (char_fld, varchar_fld, text_fld)
value ( 'This string is 28 characters', 'This string is 28 characters', 'This string is 28 characters');
*/

select length(char_fld), length(varchar_fld), length(text_fld)
from str_table;