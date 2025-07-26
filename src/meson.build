project('ics_cli', 'c', default_options: ['warning_level=3', 'c_std=gnu23'])

sources = files(
    'cli_arg_parsing.c',
    'date_time_handling.c',
    'file_handling.c',
    'insert_event.c',
    'list_handling.c',
    'main.c',
    'parse_ics.c',
    'string_handling.c',
)

executable(
    'icscli',
    sources,
    link_args: '-luuid',
    install: true,
    install_dir: '/usr/local/bin',
)
