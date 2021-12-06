/*다음 쿼리를 단순화*/
select name,
	case name 
		when 'English' then 'latin1'
        when 'Italian' then 'latin1'
        when 'French' then 'latin1'
        when 'German' then 'latin1'
        when 'Japanese' then 'utf8'
        when 'Mandarin' then 'utf8'
        else 'Unknown'
	end character_set
from language;


select name,
	case  
		when name in ('English','Italian', 'German')  then 'latin1'
        when name in ('Japanese','Mandarin')  then 'utf8'
        else 'Unknown'
	end character_set
from language;