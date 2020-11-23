#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dir;
    dir = opendir(".");
    int dir_size = 0;

    struct dirent *entry;
    entry = readdir(dir);
    printf("statistics for directory: %s\n", entry->d_name);
    struct stat file;

    while (entry) {
        if (entry->d_type == DT_REG) {
            stat(entry->d_name, &file);
            dir_size += file.st_size;
        }
        entry = readdir(dir);
    }
    printf("total directory size: %d bytes\n", dir_size);

    printf("directories:\n");
    rewinddir(dir);
    entry = readdir(dir);
    while (entry) {
        if (entry->d_type == DT_DIR)
            printf("\t%s\n", entry->d_name);
        entry = readdir(dir);
    }

    printf("regular files:\n");
    rewinddir(dir);
    entry = readdir(dir);
    while (entry) {
        if (entry->d_type == DT_REG)
            printf("\t%s\n", entry->d_name);
        entry = readdir(dir);
    }

    closedir(dir);
    return 0;
}