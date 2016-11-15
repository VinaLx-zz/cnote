#include "Infra/Directory.h"

bool open_flag = false;

void DirectoryInitDefault(Directory *this) {
    StringInitDefault(&this->path_);
    this->directory_ = NULL;
}

bool DirectoryOpen(Directory *this, const String *path) {
    if ((this->directory_ = opendir(StringConstData(path))) == NULL) {
        return false;
    }
    StringAssignString(&this->path_, path);
    open_flag = true;
    return true;
}

bool DirectoryClose(Directory *this) {
    if (not open_flag) {
        return false;
    }
    closedir(this->directory_);
    StringAssignCstring(&this->path_, "");
    open_flag = false;
    return true;
}

void DirectoryDestroy(Directory *this) {
    DirectoryClose(this);
    StringDestroy(&this->path_);
}

const String *DirectoryPath(const Directory *this) {
    return &this->path_;
}

bool DirectoryNextEntry(Directory *this, String *entry_name) {
    struct dirent* entry = readdir(this->directory_);
    if (not entry) {
        return false;
    }
    StringAssignCstring(entry_name, entry->d_name);
    return true;
}
