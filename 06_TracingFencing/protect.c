#include <unistd.h>
#include <ctype.h>
#include <string.h>

int remove(const char *pathname) {
    int ret = 0;
    if (strstr(pathname, "PROTECT") == NULL) {
        ret = unlink(pathname);
    }
    return ret;
}