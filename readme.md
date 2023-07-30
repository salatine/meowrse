# meowrse

meowrse is a script that converts (and translates) cat code into morse code and vice versa, such that a meow represents a dot (".") and a rawr represents a dash ("-").

## Installing
`$ sudo curl -L -o /usr/local/bin/meowrse https://github.com/salatine/meowrse/releases/download/latest/meowrse && sudo chmod +x /usr/local/bin/meowrse`
<br />
## Examples
### cat code to morse code
```sh
$ meowrse "meow meow"
. .
```

### morse code to cat code
```sh
$ meowrse ". ." --reverse
meow meow
```

### cat code to characters
```sh
$ meowrse "meow meow" --characters
ee
```

### characters to cat code
```sh
$ meowrse "e e" --characters --reverse
. .
```

If you forget the arguments, you can always use the help command:

`$ meowrse --help`

<br />

## Build

`$ make`
