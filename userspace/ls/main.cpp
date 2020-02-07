
#include "unistd.h"
#include "asserts.h"
#include "stdio.h"
#include "constants.h"
#include "libc/FileSystem/DirectoryEntry.h"
#include "kernel/errs.h"

void do_ls(const String& directory) {
    size_t size = 0;
    int rc = std::list_dir(directory, nullptr, &size);
    if(rc == E_NOTFOUND)
    {
        printf("directory not found\n");
        return;
    }
    ASSERT(rc == E_TOO_SMALL);
    Vector<u8> buff(size);
    rc = std::list_dir(directory, buff.data(), &size);
    ASSERT(rc == 0);
    size_t offset = 0;
    Vector<DirectoryEntry> entries;
    while(offset < size)
    {
        size_t entry_size = 0;
        entries.append(DirectoryEntry::deserialize(buff.data() + offset, entry_size));
        offset += entry_size;
    }

    for(auto& entry : entries)
    {
        printf("%s%s  ", entry.path().to_string().c_str(), entry.type() == DirectoryEntry::Type::Directory ? "/" : "");
    }
}

int main(char** argv, size_t argc) {
    if(argc < 1) {
        printf("expected argc >= 1\n");
        return 1;
    }
    if(argc > 2) {
        printf("Usage: %s [directory_path]\n", argv[0]);
        return 1;
    }
    String directory = ".";

    if(argc == 2)
    {
        directory = argv[1];
    }

    do_ls(directory);

    printf("\n");
    return 0;
}