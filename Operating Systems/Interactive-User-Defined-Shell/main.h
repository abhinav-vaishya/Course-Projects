#include "stdbool.h"

void infinite_loop();
void echo(char **argv);
void cd(char **argv);
void pwd();
void ls(char **argv);
void pinfo(char **argv);
bool run(char **argv, int bg);
bool start(char **argv, int bg);
char **arg(char *getline, char *delimiter);
void change_path(char curr[]);
char *Read();
void redirection();
void piping(char **argv);
void fg(char *job_num);
void bg(char *job_num);
void overkill();
void kjob(char **argv);
void set_env(char **argv);
void unset_env(char **argv);
void addjob(int pid, char *cname);
void jobs();
void itoa(char str[], int num);

int num_of_bg;
char home_dir[205];
char curr[205];
char location[205];
char user[205];
char host[205];
int completed[105];