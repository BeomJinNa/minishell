# minishell

프로그램 이름: `minishell`
제출 파일: `Makefile`, `*.h`, `*.c`

Makefile 규칙:
- `NAME`
- `all`
- `clean`
- `fclean`
- `re`

쉘 기능:
- 새로운 명령어를 기다릴 때 프롬프트 표시
- 작동하는 히스토리 가짐
- `PATH` 변수를 기반으로 적절한 실행 파일 검색 및 실행 또는 상대 경로 또는 절대 경로 사용
- 전역 변수 하나 이상 사용하지 않음
- 따옴표나 특수 문자 적절하게 처리
- 리다이렉션과 파이프 구현
- 환경 변수 처리하여 그 값을 확장
- `$?` 처리하여 가장 최근에 실행된 포그라운드 파이프라인의 종료 상태 확장
- `ctrl-C`, `ctrl-D`, `ctrl-\` 처리하여 bash와 같은 동작
- 내장 함수 구현

## 새로운 함수목록

1. Readline 관련 함수
    - `char *readline(const char *prompt);`
    - `void rl_clear_history(void);`
    - `void rl_on_new_line(void);`
    - `int rl_replace_line(const char *text, int clear_undo);`
    - `void rl_redisplay(void);`
    - `void add_history(const char *string);`

2. 시그널 관련 함수
    - `int sigemptyset(sigset_t *set);`
    - `int sigaddset(sigset_t *set, int signum);`

3. 디렉터리/파일 관련 함수
    - `char *getcwd(char *buf, size_t size);`
    - `int chdir(const char *path);`
    - `int stat(const char *pathname, struct stat *statbuf);`
    - `int lstat(const char *pathname, struct stat *statbuf);`
    - `int fstat(int fd, struct stat *statbuf);`
    - `DIR *opendir(const char *name);`
    - `struct dirent *readdir(DIR *dirp);`
    - `int closedir(DIR *dirp);`

4. 터미널 관련 함수
    - `int isatty(int fd);`
    - `char *ttyname(int fd);`
    - `int ttyslot(void);`
    - `int ioctl(int fd, unsigned long request, ...);`

5. 환경 변수 및 터미널 설정 함수
    - `char *getenv(const char *name);`
    - `int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);`
    - `int tcgetattr(int fd, struct termios *termios_p);`
    - `int tgetent(char *bp, const char *name);`
    - `int tgetflag(char *id);`
    - `int tgetnum(char *id);`
    - `char *tgetstr(char *id, char **area);`
    - `char *tgoto(const char *cap, int col, int row);`
    - `int tputs(const char *str, int affcnt, int (*putc)(int));`

## 나머지 허용 함수

1. 메모리 할당 및 해제
    - `void *malloc(size_t size);`
    - `void free(void *ptr);`

2. I/O 함수
    - `ssize_t write(int fd, const void *buf, size_t count);`
    - `ssize_t read(int fd, void *buf, size_t count);`
    - `int printf(const char *format, ...);`

3. 파일 및 디렉터리 접근 함수
    - `int access(const char *pathname, int mode);`
    - `int open(const char *pathname, int flags);`
    - `int close(int fd);`
    - `int unlink(const char *pathname);`

4. 프로세스 관련 함수
    - `pid_t fork(void);`
    - `pid_t wait(int *status);`
    - `pid_t waitpid(pid_t pid, int *status, int options);`
    - `pid_t wait3(int *status, int options, struct rusage *rusage);`
    - `pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);`

5. 시그널 처리 함수
    - `void (*signal(int signum, void (*handler)(int)))(int);`
    - `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`
    - `int kill(pid_t pid, int sig);`

6. 프로그램 실행 함수
    - `int execve(const char *filename, char *const argv[], char *const envp[]);`

7. 파일 디스크립터 복사 함수
    - `int dup(int oldfd);`
    - `int dup2(int oldfd, int newfd);`

8. 파이프 생성 함수
    - `int pipe(int pipefd[2]);`

9. 에러 관련 함수
    - `char *strerror(int errnum);`
    - `void perror(const char *s);`

10. 종료 함수
    - `void exit(int status);`

## 명령어 파싱

### 입력 문자열 받기
- 사용자로부터 입력 문자열을 받아온다.

### 파이프 기호로 문자열 나누기
- 따옴표 안에 있지 않은 파이프 (|) 기호를 기준으로 문자열을 나눈다.
- 이는 파이프가 다른 명령으로 연결되어 있기 때문에 각 파이프 사이의 명령을 분리하기 위한 과정이다.

### 리다이렉션 기호 추출
- 따옴표 안에 있지 않은 리다이렉션 기호 (>, >>, <, <<)를 추출한다.
- 이 리다이렉션 기호와 인자들은 별도의 메모리에 저장하고, 원래 문자열에서는 삭제한다.
- 이는 리다이렉션 기호가 따옴표 안에서는 리터럴로 처리되고, 따옴표 밖에서는 리다이렉션 명령으로 처리되기 때문이다.

### 변수 확장
- 전처리된 문자열과 별도 저장된 리다이렉션 명령어들 중에서, 작은 따옴표(') 안에 있지 않은 환경변수들을 찾아 확장시켜 치환한다. 이 때, 변수 확장은 다음과 같은 과정을 거친다:
  - `$` 다음에 `{`가 오는 경우에만 오류 검사를 진행한다. `{`가 없으면 정확한 변수 이름을 구분하기 어렵기 때문이다.
  - `${` 바로 뒤에 오는 문자는 알파벳 대소문자, 숫자, 언더바, 특수 변수 이름 중 하나여야 한다. 그렇지 않으면 에러로 처리한다. 변수의 이름은 이러한 문자로 구성되어야 하기 때문이다.
  - 변수 이름의 첫 글자 이후에는 알파벳 대소문자, 숫자, 언더바만 허용되며, 이외의 문자가 나오면 에러로 처리한다. 변수 이름의 이후 부분은 이러한 문자로만 구성되어야 하기 때문이다.
  - 이러한 오류 검사가 끝나고도 `}`가 나타나기 전에 문자열이 끝나면 에러로 처리한다. 변수 확장 과정에서 중괄호를 닫지 않으면 오류로 처리해야 한다.
  - 오류가 없으면 문자열을 `$`을 기준으로 토큰으로 나눈다. 이는 변수 이름과 그 값을 구분하기 위한 과정이다.
  - `$` 뒤에 `{`가 없으면서 알파벳 대소문자, 언더바가 아닌 경우 한 글자만 토큰으로 취급한다. 이는 특수 변수를 구분하기 위한 과정이다.
  - `$`로 시작하는 토큰은 해당하는 변수의 내용으로 문자열을 치환한다. 유효한 이름이지만 해당하는 변수가 없는 경우 빈 문자열로 치환한다. 유효하지 않은 이름이면서 특수 변수에도 해당하지 않는 경우 `$`는 리터럴로 취급한다.
  - 중괄호가 제대로 닫혔는지, 내용이 유효한 변수 이름이거나 특수 변수 이름인지 확인한다. 유효하지 않은 변수 이름이면 에러로 처리한다.

### 인자 나누기 및 따옴표 삭제
- 따옴표 안에 있지 않은 공백을 기준으로 인자들을 나누고, 따옴표를 모두 삭제한다.
- 이는 공백이 인자의 경계를 나타내고, 따옴표는 리터럴 문자열을 나타내지만 명령어에서는 필요 없기 때문이다.
