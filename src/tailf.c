#include <stdio.h>
#include <Windows.h>

void tailf(const char* filename) {
    HANDLE hFile;
    DWORD dwFileSize;
    DWORD dwBytesRead;
    char buffer[1024];

    // Open file
    hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Can not open file：%s\n", filename);
        return;
    }

    // Get file size
    dwFileSize = GetFileSize(hFile, NULL);

    // Locate the end of the file
    SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);

    while (1) {
        // Read file content
        if (ReadFile(hFile, buffer, sizeof(buffer) - 1, &dwBytesRead, NULL) && dwBytesRead > 0) {
            buffer[dwBytesRead] = '\0';
            printf("%s", buffer);
        }

        // Check for file changes
        DWORD dwNewSize = GetFileSize(hFile, NULL);
        if (dwNewSize != dwFileSize) {
            // If file has changed, relocate to the end
            SetFilePointer(hFile, dwNewSize, NULL, FILE_BEGIN);
            dwFileSize = dwNewSize;
        }

        // Check user input carriage return
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            printf("\n"); // Line break
        }

        // Pause for a while and wait for the file to change
        Sleep(200);

    }

    // Close file
    CloseHandle(hFile);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    tailf(filename);

    return 0;
}
