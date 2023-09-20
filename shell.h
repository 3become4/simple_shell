#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 *
 * @num: number
 * @str: string
 * @next: next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - info strings
 *
 *@arg: aarguements
 *@argv: array generated
 *@path: path current command
 *@argc: argument count
 *@line_count: line count
 *@err_num: exit code
 *@linecount_flag: count flag
 *@fname: filename
 *@env: environ
 *@environ: environ
 *@history: history
 *@alias: alias
 *@env_changed: environ change
 *@status: return status
 *@cmd_buf: cmd_buf on chain
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: fd to read line input
 *@histcount: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - builtin sting of functions
 *
 *@type: the builtin command flag
 *@func: the function
 *
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh functions */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
/* info functions  */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
/* path functions */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* string error functions */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string functions */
int _strlen(char *);
int _strlex(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strsplitd(char *, char);
char **strsplit(char *, char *);

/* memory functions */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
int bfree(void **);

/* utility functions */
int interactive(info_t *);
int _atoi(char *);
int _erratoi(char *);
int _isalpha(int);
int is_delim(char, char *);
void remove_comments(char *);
int print_d(int, int);
void print_error(info_t *, char *);
char *convert_number(long int, int, int);

/* builtin functions */
int _myexit(info_t *);
int _myhistory(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* aliases */
int unset_alias(info_t *, char *);
int set_alias(info_t *, char *);
int print_alias(list_t *);
int _myalias(info_t *);

/* env functions */
char *_getenv(info_t *, const char *);
char **get_environ(info_t *);
int _myenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);

/* history functions */
char *get_history_file(info_t *info);
int read_history(info_t *info);
int write_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* list functions */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
list_t *node_starts_with(list_t *, char *, char);
size_t print_list(const list_t *);
size_t print_list_str(const list_t *);
size_t list_len(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
char **list_to_strings(list_t *);

/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
/* buffers and lines */
ssize_t input_buf(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
ssize_t read_buf(info_t *, char *, size_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

#endif

