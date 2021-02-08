/****************************************************/
/* File: scan.c                                     */
/* The scanner implementation for the TINY compiler */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/


#include "globals.h"
#include "util.h"
#include "scan.h"

/* states in scanner DFA */
typedef enum
{
    START, INASSIGN, INCOMMENT, INNUM, INID, DONE, INPLUSASSIGN
}
StateType;

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN + 1];

/* BUFLEN = length of the input buffer for
source code lines */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* holds the current line */
int linepos = 0; /* current position in LineBuf */
int bufsize = 0; /* current size of buffer string */
int EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */
bool isPlusAssign = false;



                             /* getNextChar fetches the next non-blank character
                             from lineBuf, reading in a new line if lineBuf is
                             exhausted */
static int getNextChar(void)
{
    if (!(linepos < bufsize))
    {
        lineno++;
        if (fgets(lineBuf, BUFLEN - 1, source))
        {
            if (EchoSource)
                fprintf(listing, "%4d: %s", lineno, lineBuf);
            bufsize = strlen(lineBuf);
            linepos = 0;
            return lineBuf[linepos++];
        }
        else
        {
            EOF_flag = TRUE;
            return EOF;
        }
    }
    else return lineBuf[linepos++];
}

/* ungetNextChar backtracks one character
in lineBuf */
static void ungetNextChar(void)
{
    if (!EOF_flag) linepos--;
}



/* lookup table of reserved words */
static struct
{
    char* str;
    TokenType tok;
} reservedWords[MAXRESERVED]
= { { (char *)"if",IF },{ (char *)"then",THEN },{ (char *)"else",ELSE },{ (char *)"end",END },
{ (char *)"repeat",REPEAT },{ (char *)"until",UNTIL },{ (char *)"read",READ },
{ (char *)"write",WRITE }, {(char *)"do", DO}, {(char *)"while", WHILE}, {(char *)"to", TO}, {(char *)"downto", DOWNTO},
{(char *)"for", FOR}, {(char *)"enddo", ENDDO}, {(char *)"endwhile", ENDWHILE} };

/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static TokenType reservedLookup(char * s)
{
    int i;
    for (i = 0; i<MAXRESERVED; i++)
        if (!strcmp(s, reservedWords[i].str))
            return reservedWords[i].tok;
    return ID;
}


TokenType getToken(void)
{  /* index for storing into tokenString */
    int tokenStringIndex = 0;
    /* holds current token to be returned */
    TokenType currentToken;

    /* current state - always begins at START */
    StateType state = START;
    /* flag to indicate save to tokenString */
    int save;
    while (state != DONE)
    {
        int c = getNextChar();
        save = TRUE;
        switch (state)
        {
        case START:
            if (isdigit(c))
                state = INNUM;
            else if (isalpha(c))
                state = INID;
            else if (c == ':')
                state = INASSIGN;
            else if ((c == ' ') || (c == '\t') || (c == '\n'))
                save = FALSE;
            else if (c == '{')
            {
                save = FALSE;
                state = INCOMMENT;
            }
            else
            {
                    state = DONE;
                    switch (c)
                    {
                    case EOF:
                        save = FALSE;
                        currentToken = ENDFILE;
                        break;
                    case '=':
                        currentToken = EQ;
                        break;
                    case '<':
                        currentToken = LT;
                        break;
                    case '+':
                        currentToken = PLUS;
                        if(isPlusAssign)
                        {
                            state = INPLUSASSIGN;
                        }
                        break;
                    case '-':
                        currentToken = MINUS;
                        break;
                    case '*':
                        currentToken = TIMES;
                        if(lineBuf[linepos]=='*') {
                            currentToken = DBMULTI;
                            linepos++;
                            tokenString[tokenStringIndex++] = (char)c;
                        }
                        break;
                    case '/':
                        currentToken = OVER;
                        break;
                    case '(':
                        currentToken = LPAREN;
                        break;
                    case ')':
                        currentToken = RPAREN;
                        break;
                    case ';':
                        currentToken = SEMI;
                        break;
                    default:
                        currentToken = ERROR;
                        break;
                    }
                  }

            break;
        case INCOMMENT:
            save = FALSE;
            if (c == EOF)
            {
                state = DONE;
                currentToken = ENDFILE;
            }
            else if (c == '}') state = START;
            break;
        case INASSIGN:
            state = DONE;
            if (char(c) == '='){
                    currentToken = ASSIGN;
            }
            else
            { /* backup in the input */
                ungetNextChar();
                save = FALSE;
                currentToken = ERROR;
            }
            break;
            //由+跳转而来，此时已经知道了后面的等号
        case INPLUSASSIGN:
            state = DONE;
            currentToken = PLUSASSIGN;
            break;
        case INNUM:
            if (!isdigit(c))
            { /* backup in the input */
                ungetNextChar();
                save = FALSE;
                state = DONE;
                currentToken = NUM;
                if(isPlusAssign){
                    isPlusAssign = false;
                }
            }
            break;
        case INID:
            if(isPlusAssign){
                isPlusAssign = false;
            }
            if(!isPlusAssign){
                if(linepos<bufsize-1) {
                    //处理+=的情况
                    if((lineBuf[linepos]=='+')&&(lineBuf[linepos+1]=='=')){
                        isPlusAssign = true;
                    }
                }
            }
                if (!isalpha(c))
                { /* backup in the input */
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currentToken = ID;
                }
            break;

        case DONE:
        default: /* should never happen */
            fprintf(listing, "Scanner Bug: state= %d\n", state);
            state = DONE;
            currentToken = ERROR;
            break;
        }
        if ((save) && (tokenStringIndex <= MAXTOKENLEN))
            tokenString[tokenStringIndex++] = (char)c;
        if (state == DONE)
        {
            tokenString[tokenStringIndex] = '\0';
            if (currentToken == ID)
                currentToken = reservedLookup(tokenString);
        }
    }
    if (TraceScan) {
        fprintf(listing, "\t%d: ", lineno);
        printToken(currentToken, tokenString);
    }
    return currentToken;
}
