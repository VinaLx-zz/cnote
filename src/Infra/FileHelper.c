#ifndef _GNU_SOURCE // enable getline
#define _GNU_SOURCE
#endif

#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "Infra/FileHelper.h"

bool fileExist(const String *path) {
    struct stat stat_buf;
    if (stat(StringConstData(path), &stat_buf) < 0) {
        return false;
    }
    return S_ISREG(stat_buf.st_mode);
}

bool fileExecutable(const String *path) {
    if (not fileExist(path)) {
        return false;
    }
    return access(StringConstData(path), X_OK) == 0;
}

bool fileCreate(const String *path, FilePemission permission) {
    mode_t mode = 0;

    if (permission == PUBLIC_MODE) {
        mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    } else { // permission == PRIVATE_MODE
        mode = S_IRUSR | S_IWUSR;
    }

    int fd = open(StringConstData(path), O_CREAT | O_EXCL, mode);
    if (fd < 0) {
        return false;
    }
    close(fd);
    return true;
}

bool fileRemove(const String *path) {
    if (not fileExist(path)) {
        return false;
    }
    return unlink(StringConstData(path)) == 0;
}

static mode_t last_mode = 0;

bool fileEnableEdit(const String *path) {
    struct stat stat_buf;
    if (last_mode or stat(StringConstData(path), &stat_buf) < 0) {
        return false;
    }
    last_mode = stat_buf.st_mode;
    return chmod(
        StringConstData(path),
        last_mode | S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH) == 0;
}

bool fileRestoreMode(const String *path) {
    if (not last_mode) {
        return false;
    }
    mode_t temp_mode = last_mode;
    last_mode = 0;
    return chmod(StringConstData(path), temp_mode) == 0;
}

bool fileGetTimeString(
    const String *path, String *time_string, FileTimeType time_type) {
    struct stat stat_buf;
    if (stat(StringConstData(path), &stat_buf) < 0) {
        return false;
    }
    time_t file_time;
    if (time_type == ACCESS_TIME) {
        file_time = stat_buf.st_atime;
    } else if (time_type == MODIFY_TIME) {
        file_time = stat_buf.st_mtime;
    } else { // time_type == CHANGE_TIME
        file_time = stat_buf.st_ctime;
    }
    struct tm *time_struct = localtime(&file_time);
    char time_cstr[17]; // magic number :), "YYYY-MM-DD HH:MM\0"
    strftime(time_cstr, 17, "%Y-%m-%d %H:%M", time_struct);
    StringAssignCstring(time_string, time_cstr);
    return true;
}

FILE *fileOpenTruncate(const String *path) {
    return fopen(StringConstData(path), "w");
}

FILE *fileOpenRead(const String *path) {
    return fopen(StringConstData(path), "r");
}

bool fileGetline(FILE *istream, String *destination) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    if (getline(&buffer, &buffer_size, istream) < 0) {
        free(buffer);
        return false;
    }
    StringAssignCstring(destination, buffer);
    free(buffer);
    return true;
}

bool dirExist(const String *path) {
    struct stat stat_buf;
    if (stat(StringConstData(path), &stat_buf) < 0) {
        return false;
    }
    return S_ISDIR(stat_buf.st_mode);
}

bool dirCreate(const String *path, FilePemission permission) {
    mode_t mode = 0;
    if (permission == PUBLIC_MODE) {
        mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
    } else { // permission == PRIVATE_MODE
        mode = S_IRWXU;
    }
    return mkdir(StringConstData(path), mode) == 0;
}

