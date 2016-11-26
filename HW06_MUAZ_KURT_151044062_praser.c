#include <stdio.h>
#include <string.h>
#define posibleChar 10000
#define maxMailcanbeReaden 20
#define mssSubject 200
#define mssBody 2000
void findingMails(char *fullreadenfile,
                  char mail[maxMailcanbeReaden][mssSubject + mssBody + 80])
{
    int i, mailScout;
    char start[] = "<email>";
    for(mailScout = 0; mailScout < maxMailcanbeReaden;++mailScout);
        for(i = 0; i < strlen( strtok( fullreadenfile, "</email>" )); ++i)
        {
            if(strcmp(&fullreadenfile[i], start) == 0)
                strcpy(mail[mailScout],&fullreadenfile[i + 7]);
        }
}



void categorisingMailsintoStrings(FILE *openedmail,
                                  char subject[maxMailcanbeReaden][mssSubject],
                                  char body[maxMailcanbeReaden][mssBody])
{
    char theFile[posibleChar];

    int readerofAll,
        mailsReaden;

    for(readerofAll=0;
        theFile[readerofAll] == EOF &&
        readerofAll < posibleChar - 1;
        ++readerofAll)
    {
        fscanf(openedmail, "%c", &theFile[readerofAll]);
    }
    theFile[readerofAll + 1] = '\0';

    strtok(theFile, "<email>");
    for(mailsReaden = 0;
        strlen(NULL) > 7,
        mailsReaden < maxMailcanbeReaden;
        ++mailsReaden)
    {
        strtok(NULL, "<Subject>");
        strcpy(subject[mailsReaden], strtok(NULL, "</Subject>"));
        strtok(NULL, "<Body>");
        strcpy(body[mailsReaden], strtok(NULL, "</Body>"));
        strtok(NULL, "</email>");
        strtok(NULL, "<email>");
    }
}



void main()
{
    FILE *emails;
    char subject[maxMailcanbeReaden][mssSubject],
        body[maxMailcanbeReaden][mssBody];
    emails=fopen("emails.txt", "r");
    categorisingMailsintoStrings(emails,subject,body);
    return;
}
