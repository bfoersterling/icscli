## ics_cli

#### Use Case

- show upcoming events of an .ics file
- insert events in your calendar


#### Installation

```
just install
```

#### Usage

The default path to the ics file is `~/.local/share/evolution/calendar/system/calendar.ics`.\
(The default path for the builtin `evolution` calendar.)

```
$ icscli
Current date and time: 2025-02-01 05:06:40

2025-02-03 - 2025-02-09
SUMMARY: Vacation

2025-02-28 08:00:00 - 08:30:00
SUMMARY: Gym

2025-03-10 14:00:00 - 15:00:00
SUMMARY: Meeting

2025-04-26 - 2025-04-27
SUMMARY: Weekend Hike

2025-05-19 09:00:00 - 10:00:00
SUMMARY: Doctor's Appointment
```

To use a different path to the ics file:
```
icscli -f path/to/ics/file.ics
```

```
icscli -h
```

Insert an event:
```
icscli -i
```


#### Uninstall

```
sudo rm -fv /usr/local/bin/icscli
```

#### Unit Testing

```
just test
```

Or manual:

```
cd unit_tests
```

```
meson setup testdir
```

```
meson test -C testdir
```

#### Git-hooks for Ctags Pre-commit

The developer has to actively enable git hooks:
```
git config --local core.hooksPath git-hooks
```
This will run `ctags` on every commit.

#### TODO

- use env var `ICAL_FILE`, `ICS_FILE`, or `ICALENDAR_FILE`
- add option to import .ics files (for single events)
- improve unit tests
- make ics file path configurable
- add cli argument that will not show ongoing events, only upcoming events
