## ics_cli

#### Use Case

- show upcoming events of an .ics file
- insert events in your calendar


#### Installation

```
cd src/builddir
``` 

```
meson compile
```

```
meson install
```

#### Usage

The default path to the ics file is `~/.local/share/evolution/calendar/system/calendar.ics`.\
(The default path for the builtin evolution calendar.)

```
icscli
```

for a custom path
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

#### Git-hooks for Ctags Pre-commit

The developer has to actively enable git hooks:
```
git config --local core.hooksPath git-hooks
```
This will run `ctags` on every commit.

#### TODO

- improve and automate unit testing
- add cli argument that will not show ongoing events, only upcoming events
