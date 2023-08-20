# export

## case 1) valid identifier
```bash
$ export val=1
$ export empty=
$ export none
$ export
declare -x val="1"
declare -x empty=""
declare -x none # env 명령에서 보이지 않음
$ env
val=1
empty=
```

## case 2) not a valid identifier
```bash
$ export =
$ export =1
$ export ?=1
$ export !=1
$ export 1=1
$ export 1a=1
```