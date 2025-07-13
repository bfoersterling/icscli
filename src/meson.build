project(
  'ics_cli',
  'c',
  default_options: 'warning_level=3',
)

executable('icscli', 'main.c', 'cli_arg_parsing.c', 'date_time_handling.c', 'insert_event.c', \
'list_handling.c', 'parse_ics.c', 'file_handling.c', 'string_handling.c', \
link_args : '-luuid', install: true, install_dir: '/usr/local/bin')
