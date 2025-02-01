project('ics_cli', 'c')

executable('icscli', 'main.c', 'cli_arg_parsing.c', 'date_time_handling.c', 'insert_event.c', \
'list_handling.c', 'parse_ics.c', 'read_until_nl.c', 'read_until_string.c', 'seek_string_a.c', \
'string_handling.c', link_args : '-luuid', install: true, install_dir: '/usr/local/bin')
