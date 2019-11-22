#include "process.h"
#include "task.h"
#include "FileSystem/VFS.h"
#include "errs.h"
#include "device.h"

u32 g_next_pid;

Process* Process::create(void (*main)(), String name) {
    auto* task = create_kernel_task(main);
    return new Process(g_next_pid++, task, name);
}


Process::~Process() {
    // TODO: free usespace resources & pages
    delete m_task;
}

int Process::syscall_open(const String& path) {
    auto* file = VFS::the().open(path);
    if(file == nullptr)
        return -E_NOTFOUND;
    for(size_t i = 0; i < NUM_FILE_DESCRIPTORS; i++) {
        if(m_file_descriptors[i] == nullptr) {
            m_file_descriptors[i] = file;
            return i;
        }
    }
    return -E_LIMIT;
}

int Process::syscall_ioctl(size_t fd, u32 code, void* data) {
    if(fd >= NUM_FILE_DESCRIPTORS)
        return -E_NOTFOUND;
    auto* file = m_file_descriptors[fd];
    if(file == nullptr)
        return -E_NOTFOUND;
    // TODO: dynamic_cast
    Device* d = static_cast<Device*>(file);
    return d->ioctl(code, data);
}