### Readline | <stdio.h>
* **readline(3)**: `char *readline(const char prompt)`, read a line from the terminal and return it using promp as promt, the line returned is allocated with `malloc(3)` so it should be freed properly. It offers editing capabilities as well.
* **rl_clear_history**: `void rl_clear_history (void)`, clear the history by deleting all of the entries, it frees private data `readline` saves in history.
* **rl_on_new_line**: `int rl_on_new_line (void)`, Tell the update functions that we have moved onto a new `(empty)` line, usually after outputing a newline.
* **rl_replace_line**: `void rl_replace_line (const char *text, int clear undo)`, replaces the content of of `rl_line_buffer` with text. The point and mark are pre-served, if possible. If clear undo is non-zero, the undo list associated with the current
line is cleared.
* **rl_redisplay**: `void rl_redisplay(void)`, changes what is displayed on the screen to reflect the current contents of `rl_line_buffer`.

### Readline variables:
* char * rl_line_buffer: This is the line gathered so far. You are welcome to modify the contents of the line.

------
### history(3) | [GNU History Library](https://tiswww.case.edu/php/chet/readline/history.html)
    Many programs read input from the user a line at a time.
    The GNU History library is able to keep track of those lines,
    associate arbitrary data with each line,
    and utilize information from previous lines in composing new ones.

* **add_history**: `void add_history(const char *string)`, place a string add the end of the history list.
---
### wait | <sys/wait.h>
    wait for a process to change state.
* **wait** : `pid_t wait(int *stat_loc)`, Suspends execution of the calling thread until one of its children terminates.
* **waitpid** : `pid_t waitpid9pid_t pid, int *stat_loc, struct rusage *rusage)`, suspends execution of the calling thread until a child specified by  `pid` argument has changed state.
    
    > By default `waitpid()` waits only for terminated children, but this behavior is modifiable via options argument, as described below. "
    
    * **< -1** : meaning wait for any child process whose process group ID is equal to absolute value of `pid`.
    * **-1** : meaning for any child process.
    * **0** : meaning  wait for any child process whose process group ID is equal to that of the calling process at the time of the call to `waitpid()`.
    * **>0** : meaning wait for the child whose process ID is equal to the value of `pid`.
* **wait3** || **wait4** : `pid_t wait3(int *status, int options, struct rusage *rusage)` || `pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);`, The wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage.
    
---
* printf(3)
* malloc
* free
* write
* access : check the accessiblity of a file.
* open : open a file.
* read : read a file.
* close : close the opened file.
* fork : create a new proccess.
---
