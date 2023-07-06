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
