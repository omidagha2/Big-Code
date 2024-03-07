#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

#pragma comment(lib, "winmm.lib")

int main() {
    PlaySound(TEXT("ding.wav"), NULL, SND_FILENAME | SND_ASYNC);
    // Your other code here
    return 0;
}
