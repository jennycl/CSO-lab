#include "lab4.h"

/* Shell input line */
int process(void)
{
    char *arg[MAXARG + 1];  /* pointer array for runcommand */
    int toktype;            /* type of token in command */
    int narg ;              /* number of arguments so far */
    int type;               /* type = FOREGROUND or BACKGROUND */

    while (1) 
    {
        /* Take action according to token type */
        switch(toktype = gettok(&arg[narg]))
        {
            case ARG:
                if(narg < MAXARG) 
                {
                    narg++;
                }
                break;

            case EOL:
            
            case SEMICOLON:
            
            case AMPERSAND:
                type = toktype == AMPERSAND ? BACKGROUND : FOREGROUND;
                
                if(narg != 0)
                {
                    arg[narg] = 0;
                    runcommand(arg,type);
                }

                /* bug #1 
                * The bug is that narg = 0 was set after the if(toktype == EOL). This caused only the first command to work
                * and subsequent ones to fail. This is because if narg = 0 is put after checking if 
                * toktype = EOL, it will never happen if the toktype is EOL. The process will return and
                * narg would have never been set to 0, thus causing subsequent commands besides the
                * first to not execute. 
                */
                
                narg = 0;


                if(toktype == EOL)
                {
                    return;   
                }

                break;
        }
    }
}
