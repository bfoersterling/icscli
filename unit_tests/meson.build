project('ics_cli', 'c')

t1e = executable('test_print_upcoming', 'test_print_upcoming.c', '../src/parse_ics.c', '../src/string_handling.c', \
'../src/list_handling.c', '../src/date_time_handling.c', '../src/file_handling.c')

test('test print_upcoming', t1e)

t2e = executable('test_pretty_print_date_time', 'test_pretty_print_date_time.c', '../src/string_handling.c', \
'../src/date_time_handling.c', '../src/file_handling.c')

test('test pretty_print_date_time', t2e)

t3e = executable('test_parse_ics_file', 'test_parse_ics_file.c', '../src/parse_ics.c', '../src/string_handling.c', '../src/list_handling.c', \
'../src/date_time_handling.c', '../src/file_handling.c')

test('test parse_ics_file', t3e)
