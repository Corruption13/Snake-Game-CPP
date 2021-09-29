/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
*/

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}


// Some Utility Functions for the game that i had to stackoverflow.

int PressKey() {
    // Borrowed from Stack Overflow.
    int c;
    while ((c=! _kbhit())) {
        printf(".");
        fflush(stdout);
        usleep(1000);
        return 0;
    }
    return 1;
} 


void sleepms(int x=1000){
    std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

char readEnteredKey(){
    return getch();
}