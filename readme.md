# <img src="https://github.com/ekisu/meowrse/assets/5082637/f2bf3b0d-297c-485f-bff2-579c160df8d5" style="height: 2em"/> meowrse

meowrse is a script that converts (and translates) cat code into morse code and vice versa, such that a meow represents a dot (".") and a rawr represents a dash ("-").

## Installing
`$ sudo curl -L -o /usr/local/bin/meowrse https://github.com/salatine/meowrse/releases/download/latest/meowrse && sudo chmod +x /usr/local/bin/meowrse`
<br />
## Examples
### cat code to morse code
```sh
$ meowrse meow-to-morse "meow meow"
. .
```

### morse code to cat code
```sh
$ meowrse morse-to-meow ". ."
meow meow
```

### cat code to characters
```sh
$ meowrse meow-to-characters "meow meow"
ee
```

### characters to cat code
```sh
$ meowrse characters-to-meow "e e"
. .
```

If you forget any command, you can always use the help command:

`$ meowrse --help`

<br />

## Build

`$ make`
