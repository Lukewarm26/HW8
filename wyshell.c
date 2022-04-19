
#include<stdio.h>
#include<string.h>
#include"wyscanner.h"

int main()
{
    int rtn;
    char *rpt;
    char buf[1024];
    char sym[5];
    int err = 0;
    int REDIR_OUT_COUNT;
    int REDIR_IN_COUNT;
    int APPEND_OUT_COUNT;
    int REDIR_ERR_COUNT;
    int APPEND_ERR_COUNT;
    int REDIR_ERR_OUT_COUNT;
    

char *tokens[] = { "QUOTE_ERROR", "ERROR_CHAR", "SYSTEM_ERROR",
              "EOL", "REDIR_OUT", "REDIR_IN", "APPEND_OUT",
              "REDIR_ERR", "APPEND_ERR", "REDIR_ERR_OUT", "SEMICOLON",
              "PIPE", "AMP", "WORD" };

char *special_symbols[] = { "QUOTE_ERROR", "ERROR_CHAR", "SYSTEM_ERROR",
              "EOL", ">", "<", ">>",
              "2>", "2>>", "2>&1", ";",
              "|", "&", "WORD" };

    while(1)
    {
        printf("$> ");
        strcpy(sym, ":--:\0");
        err = 0;
        REDIR_OUT_COUNT = 0;
        rpt = fgets(buf, 256, stdin);
        if(rpt == NULL)
        {
            if(feof(stdin))
            {
                return 0;
            }
            else
            {
                perror("error reading from stdin");
                return 1;
            }
        }
        rtn = parse_line(buf);
        while(rtn != EOL && err == 0)
        {
            switch(rtn)
            {
                case WORD:
                    printf("%s %s\n", sym, lexeme);
                    strcpy(sym, "--:\0");
                    break;
                case ERROR_CHAR:
                    printf("%d: %s\t =%d\n",rtn,tokens[rtn%96],error_char);
                    err = 1;
                    break;
                case PIPE:
                    printf("%s\n", special_symbols[rtn%96]);
                    strcpy(sym, ":--:\0");
                    break;
                case SYSTEM_ERROR:
                    perror("system error");
                    return 0;
                case QUOTE_ERROR:
                    err = 1;
                    break;
                case REDIR_OUT:
                    REDIR_OUT_COUNT++;
                    if(REDIR_OUT_COUNT > 1)
                    {
                        err = 1;
                        puts("Ambiguous output redirection");
                        break;
                    }
                case SEMICOLON:
                    strcpy(sym, ":--:\0");  
                default:
                    printf("%s\n", special_symbols[rtn%96]);

            }  
            rtn = parse_line(NULL);
            
        }
        if(err = 0)
        {
           printf("%s %s\n", sym, "EOL"); 
        }
        
    }
    
}