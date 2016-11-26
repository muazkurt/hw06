#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define posibleChar 10000
#define maxMailcanbeReaden 20
#define mssSubject 200
#define mssBody 2000

/*
    I can only read posibleChar characters from a file.
    If the file finish before posibleChar,
    then my job ends.
*/
char *readingFile(
                  FILE* data,
                  char *fullreadenfile)
{
    int counter, isEof=0;
    char q;
    for(counter = 0; fscanf(data, "%c", &q)!=EOF && counter < posibleChar - 1; ++counter)
        fullreadenfile[counter] = q;
    fullreadenfile[counter] = 0;
    return fullreadenfile;
}

/*
    I am searching for a keyword inside a string,
    fullreadenfile is the searchen string,
    start is the keyword.
    If I find keyword, then i update the string with after keyword
    and return it.
    If there is no keyword, then I return NULL for saying there will not be keyword.
*/
char *whatsAfterThis(
                     char *fullreadenfile,
                     char *start)
{
    int counter;
    for(counter = 0; counter < strlen(fullreadenfile); ++counter)
    {
        if(strncmp(&fullreadenfile[counter], start, strlen(start)) == 0)
            return strcpy(fullreadenfile,
                          &fullreadenfile[counter + strlen(start)]);
    }
    return "NULL";
}

/*
    I am searching for a keyword in a string.
    If i find the keyword
*/
char *whatsBeforeThis(
                      char *fullreadenfile,
                      char *finish)
{
    int counter;
    char beforeString[posibleChar];
    for(counter = 0; counter < strlen(fullreadenfile); ++counter)
    {
        if(strncmp(&fullreadenfile[counter],
                   finish,
                   strlen(finish)) == 0)
            return strncpy(beforeString,
                           fullreadenfile,
                           counter);
    }
    return "NULL";
}

char *whatsBetweenThese(
                        char *fullreadenfile,
                        char *start,
                        char *finish)
{
    char textintags[posibleChar];
    return strcpy(textintags,
                  (whatsBeforeThis(strcpy(textintags,
                                          whatsAfterThis(fullreadenfile,
                                                         start)),
                                          finish)));
}

void categorisingMailsintoStrings(FILE *openedmail,
                                  char subject[maxMailcanbeReaden][mssSubject],
                                  char body[maxMailcanbeReaden][mssBody])
{
    int counter;



}



void main()
{
    FILE *emails;
    char subject[maxMailcanbeReaden][mssSubject],
        body[maxMailcanbeReaden][mssBody],
        theFile[posibleChar];
    emails=fopen("emails.txt", "r");
    printf("%s\n\n\n", readingFile(emails,theFile));
    printf("%s\n\n\n", whatsAfterThis(theFile,"<email>"));
    printf("%s\n\n\n", whatsBeforeThis(theFile,"</email>"));
    printf("%s\n\n\n", whatsBetweenThese(theFile,"<email>","</email>"));
    return;
}
