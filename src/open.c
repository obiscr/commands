#include <stdio.h>
#include <Windows.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <File or application path>\n", argv[0]);
        return 1;
    }

    const char* path = argv[1];
    HINSTANCE result = ShellExecute(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL);

    if ((int)result <= 32) {
        printf("Can not open file or application：%s\n", path);
        return 1;
    }

    return 0;
}
