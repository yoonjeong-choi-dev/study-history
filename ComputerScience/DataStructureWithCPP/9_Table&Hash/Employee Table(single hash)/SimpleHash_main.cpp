#include "Person.h"
#include "Table.h"

int My_hash_func(int k)
{
	return k % 100;
}

int main()
{
	Table my_tbl;
	Person *p1;
	Person *p2;
	Person *p3;

	Table_init(&my_tbl, My_hash_func);


	p1 = Make_person_data(20123424, "Choi", "Seoul");
	Table_insert(&my_tbl, Get_ssn(p1), p1);
	cout << my_tbl.tbl[24].status << endl;//ÀÌ°Å¶û


	p1 = Make_person_data(20123413, "Cho", "Seo");
	Table_insert(&my_tbl, Get_ssn(p1), p1);


	p1 = Make_person_data(20173596, "hoi", "eoul");
	Table_insert(&my_tbl, Get_ssn(p1), p1);
	



	p2 = Table_search(&my_tbl, 20123424);
	if (p2 != NULL)
		Show_info(p2);

	p2 = Table_search(&my_tbl, 20125413);
	if (p2 != NULL)
		Show_info(p2);

	p2 = Table_search(&my_tbl, 20173596);
	if (p2 != NULL)
		Show_info(p2);



	p3 = Table_delete(&my_tbl, 20123424);
	if (p3 != NULL)
		free(p3);

	p3 = Table_delete(&my_tbl, 20123413);
	if (p3 != NULL)
		free(p3);

	p3 = Table_delete(&my_tbl, 20173596);
	if (p3 != NULL)
		free(p3);
	return 0;
}