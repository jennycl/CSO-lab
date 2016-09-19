#include "lab4.h"

void sighandler(int);

int main()
{
	signal(SIGINT, sighandler);
    //run the shell until EOF (keyboard Ctrl+D) is detected
    while (userinput( ) != EOF)
    {
        process();
    }
    return 0;

   
}

/* Bug 4
* The bug was that Ctrl+C quit the entire shell because
* Ctrl+C is a signal that terminates the shell, and in order
* for it not to terminate, we had to use a signalhandler
* to "catch" the SIGINT signal. By doing so, we tell the program
* to not terminate if a Ctrl+C is pressed and go to the sighandler instead.
* This allows for the processes in the foreground mode to be killed when Ctrl+C is pressed,
* not the entire shell itself.
*/
 void sighandler(int signum){
    
    return;
 }
