# meowrse

meowrse is a script that converts (and translates) cat code into morse code and vice versa, such that a meow represents a dot (".") and a rawr represents a dash ("-").

## Installing
`$ sudo curl -L -o /usr/local/bin/meowrse https://github.com/salatine/meowrse/releases/download/latest/meowrse && sudo chmod +x /usr/local/bin/meowrse`
<br></br>
## Examples
### cat code to morse code
`$ meowrse "meow meow"`

`. .`

### morse code to cat code
`$ meowrse ". ." -r`

`meow meow`

### cat code to characters
`$ meowrse "meow meow" -c`

`ee`

### characters to cat code
`$ meowrse "e e" -c -r`

`. .`
<br></br>
## Build
`$ gcc meowrse.c -o meowrse`
