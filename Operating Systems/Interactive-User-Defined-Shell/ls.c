#include "dirent.h"
#include "grp.h"
#include "main.h"
#include "malloc.h"
#include "pwd.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "time.h"
#include "unistd.h"

void ls(char **argv) {
    int i = 1;
    bool a = false, l = false, d = false;
    int cnt = 0;
    struct dirent *dir_name;
    struct stat pd;
    char date[205];
    DIR *dir;
    char **content = (char **)(malloc)(8 * cnt);
    while (argv[i] != NULL) {
        if (!strcmp(argv[i], "-a")) {
            a = true;
        } else if (!strcmp(argv[i], "-l")) {
            l = true;
        } else if (!strcmp(argv[i], "-al") || !strcmp(argv[i], "-la")) {
            a = true;
            l = true;
        } else if (strcmp(argv[i], " ")) {
            cnt++;
        }
        i++;
    }
    if (!cnt) {
        cnt++;
        d = true;
    }
    i = 0;
    while (i < cnt) {
        content[i] = (char *)(malloc)(100);
        i++;
    }
    if (d) {
        content[0] = ".";
    }
    i = 1;
    int j = 0;
    while (argv[i] != NULL) {
        if (strcmp(argv[i], "-a") && strcmp(argv[i], "-l") &&
            strcmp(argv[i], "-al") && strcmp(argv[i], "-la")) {
            content[j] = argv[i];
            j++;
        }
        i++;
    }
    i = 0;
    while (i < cnt) {
        dir = opendir(content[i]);
        if (dir == NULL) {
            printf("Error: Directory named %s does not exist", content[i]);
            printf("\n");
        } else {
            // while ((dir_name = readdir(dir)) != NULL)
            while (1) {
                dir_name = readdir(dir);
                if (dir_name == NULL) {
                    break;
                }
                stat(dir_name->d_name, &pd);
                if (a == false && l == false) {
                    if (dir_name->d_name[0] != '.') {
                        printf("%s", dir_name->d_name);
                        printf("\n");
                    }
                } else if (a == true && l == false) {
                    printf("%s", dir_name->d_name);
                    printf("\n");
                } else if (a == false && l == true) {
                    if (dir_name->d_name[0] != '.') {
                        strftime(date, 200, "%d %h %H:%M",
                                 localtime(&(pd.st_ctime)));
                        mode_t stmode;
                        stmode = pd.st_mode;
                        struct group *grp = getgrgid(pd.st_gid);
                        struct passwd *pwd = getpwuid(pd.st_uid);
                        if (S_ISDIR(stmode)) {
                            printf("d");
                        } else {
                            printf("-");
                        }
                        if (stmode & S_IRUSR) {
                            printf("r");
                        } else {
                            printf("-");
                        }
                        if (stmode & S_IWUSR) {
                            printf("w");
                        } else {
                            printf("-");
                        }
                        if (stmode & S_IXUSR) {
                            printf("x");
                        } else {
                            printf("-");
                        }
                        if (stmode & S_IRGRP) {
                            printf("r");
                        } else {
                            printf("-");
                        }
                        if (stmode & S_IWGRP) {
                            printf("w");
                        } else {
                            printf("-");
                        }
                        if (stmode & S_IXGRP) {
                            printf("x");
                        } else {
                            printf("-");
                        }
                        if (stmode & S_IROTH) {
                            printf("r");
                        } else {
                            printf("-");
                        }
                        if (stmode & S_IWOTH) {
                            printf("w");
                        } else {
                            printf("-");
                        }
                        if (stmode & S_IXOTH) {
                            printf("x");
                        } else {
                            printf("-");
                        }

                        printf(" %d %s %s %d %s %s", (int)pd.st_nlink,
                               pwd->pw_name, grp->gr_name, (int)pd.st_size,
                               date, dir_name->d_name);
                        printf("\n");
                    }
                } else {
                    strftime(date, 200, "%d %h %H:%M",
                             localtime(&(pd.st_ctime)));
                    mode_t stmode;
                    stmode = pd.st_mode;
                    struct group *grp = getgrgid(pd.st_gid);
                    struct passwd *pwd = getpwuid(pd.st_uid);
                    if (S_ISDIR(stmode)) {
                        printf("d");
                    } else {
                        printf("-");
                    }
                    if (stmode & S_IRUSR) {
                        printf("r");
                    } else {
                        printf("-");
                    }
                    if (stmode & S_IWUSR) {
                        printf("w");
                    } else {
                        printf("-");
                    }
                    if (stmode & S_IXUSR) {
                        printf("x");
                    } else {
                        printf("-");
                    }
                    if (stmode & S_IRGRP) {
                        printf("r");
                    } else {
                        printf("-");
                    }
                    if (stmode & S_IWGRP) {
                        printf("w");
                    } else {
                        printf("-");
                    }
                    if (stmode & S_IXGRP) {
                        printf("x");
                    } else {
                        printf("-");
                    }
                    if (stmode & S_IROTH) {
                        printf("r");
                    } else {
                        printf("-");
                    }
                    if (stmode & S_IWOTH) {
                        printf("w");
                    } else {
                        printf("-");
                    }
                    if (stmode & S_IXOTH) {
                        printf("x");
                    } else {
                        printf("-");
                    }
                    printf(" %d %s %s %d %s %s", (int)pd.st_nlink, pwd->pw_name,
                           grp->gr_name, (int)pd.st_size, date,
                           dir_name->d_name);
                    printf("\n");
                }
            }
        }
        i++;
    }
    closedir(dir);
}