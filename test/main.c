#include <stdio.h>
#include <check.h>
#include "../src/roman.h"

static char error_numa_wrong_input[100]="ERROR: first number input illegal!";
static char error_numb_wrong_input[100]="ERROR: second number input illegal!";
static char error_result_overflow[100]="ERROR: result is out of roman range!";



START_TEST(test_roman_regular_1){
	ck_assert_str_eq(addRomanNumbers("XXVI","XIV",0),"XL");
}
END_TEST

START_TEST(test_roman_regular_2){
	ck_assert_str_eq(addRomanNumbers("XLVI","XIV",0),"LX");
}
END_TEST
START_TEST(test_roman_size_overflow){
	ck_assert_str_eq(addRomanNumbers("DJKSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS","XL",0),error_numa_wrong_input);
	ck_assert_str_eq(addRomanNumbers("XL","DJKSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS",0),error_numb_wrong_input);
}
END_TEST

START_TEST(test_roman_illegal_character_count){
	ck_assert_str_eq(addRomanNumbers("XXXX","X",0),error_numa_wrong_input);
	ck_assert_str_eq(addRomanNumbers("X","XXXX",0),error_numb_wrong_input);
}
END_TEST

START_TEST(test_roman_illegal_organization){
	ck_assert_str_eq(addRomanNumbers("IVVII","X",0),error_numa_wrong_input);
	ck_assert_str_eq(addRomanNumbers("X","IVXVI",0),error_numb_wrong_input);
}
END_TEST

START_TEST(test_roman_output_overflow){
	ck_assert_str_eq(addRomanNumbers("XXXX","X",0),error_numa_wrong_input);
	ck_assert_str_eq(addRomanNumbers("X","XXXX",0),error_numb_wrong_input);
}
END_TEST

Suite* roman_suite(void){
	Suite *s;
	TCase *tc_core;
	s = suite_create("Roman");
	
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_roman_regular_1);
	tcase_add_test(tc_core, test_roman_regular_2);
	tcase_add_test(tc_core, test_roman_size_overflow);
	tcase_add_test(tc_core, test_roman_illegal_organization);
	tcase_add_test(tc_core, test_roman_illegal_character_count);
	tcase_add_test(tc_core, test_roman_output_overflow);

	suite_add_tcase(s, tc_core);
	return s;
}


int main() {

	int number_failed;
	Suite *s;

	SRunner *sr;

	s = roman_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? 0 : -1;
}


