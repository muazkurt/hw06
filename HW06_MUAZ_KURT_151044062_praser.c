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
    int counter;
    char q;
    for(counter = 0;
            fscanf(data, "%c", &q)!= EOF &&
            counter < posibleChar - 1;
                ++counter)
        fullreadenfile[counter] = q;
    fullreadenfile[counter] = 0;
    return fullreadenfile;
}

/*
    I am searching for a keyword inside a string,
    fullreadenfile is the searched string,
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
    return "Empty";
}

/*
    I am searching for a keyword in a string.
    fullreadenfile is the searched string.
    If i find the keyword, then i return the string before the keyword.
    I am not update the given string because it possibly cause data loss.
    If i cant find the keyword in given string,
    Then i return Empty as there is no keyword.
*/
char *whatsBeforeThis(
                      const char *fullreadenfile,
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
    return "Empty";
}

/*
    I am searching for 2 keywords in a string.
    fullreadenfile is the searched string.
    I'm finding the string between first keyword and sec keyword.
    I'm searching with early defined functions "whatsAfterThis" and "whatsBeforeThis".
    I return the string between them.
    If there will be some errors, then return value will be NULL.
*/
char *whatsBetweenThese(
                        char *fullreadenfile,
                        char *start,
                        char *finish)
{
    char textintags[posibleChar];
    return strcpy(textintags,
                  whatsBeforeThis(strcpy(textintags,
                                          whatsAfterThis(fullreadenfile,
                                                         start)),
                                          finish));
}

void parsingMail(FILE *openedmail,
                 char subject[maxMailcanbeReaden][mssSubject],
                 char body[maxMailcanbeReaden][mssBody])
{
    int counter;
    char theFile[posibleChar];
    readingFile(openedmail,theFile);
    for(counter = 0;
            whatsBetweenThese(theFile,
                          "<email>",
                          "</email>") != "Empty" &&
            counter < maxMailcanbeReaden;
                ++counter);
    {
        strcpy(subject[counter],
               whatsBetweenThese(theFile,
                                 "<Subject>",
                                 "</Subject>"));
        strcpy(body[counter],
               whatsBetweenThese(theFile,
                                 "<Body>",
                                 "</Body>"));
    }
    return;
}



void main()
{
    FILE *emails;
    char subject[maxMailcanbeReaden][mssSubject],
        body[maxMailcanbeReaden][mssBody];
    emails=fopen("emails.txt", "r");
    parsingMail(emails, subject, body);
    printf("%s\n\n\n", subject[0]);
    printf("%s\n\n\n", body[0]);
    fclose(emails);
    return;
}
