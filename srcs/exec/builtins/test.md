# export

case#1
```bash
$ export var_test
$ env | grep var_test # 출력 X (var_test가 없음. 왜? 쉘 변수에 존재하지 않아서, 환경변수 설정 실패)
$ var_test=123
$ env | grep var_test
123
```