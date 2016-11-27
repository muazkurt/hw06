#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define posibleChar	 4096	//Max readable chars from file.
#define mssEmail	16			//MeSage String for Email.
#define mssSubject 32		//MeSage String for Subject.
#define mssBody 1024		//MeSage String for Body.
#define mpSubject 15		//Maximum Printable Subject
#define mpBody 50			//Maximum Printable Body

/*
    I can only read posibleChar characters from a file.
    If the file finish before posibleChar,
    then my job ends.
*/
char *readingFile(FILE* data, char *fullreadenfile)
{
    int counter;
    char q;
	for (counter = 0; fscanf(data, "%c", &q) != EOF && counter < posibleChar - 1; ++counter)
		fullreadenfile[counter] = q;
    fullreadenfile[counter] = '\0';
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
char *whatsAfterThis(char *fullreadenfile, char *start)
{
    int counter;
	for (counter = 0; counter < strlen(fullreadenfile); ++counter)
	{
		if (strncmp(&fullreadenfile[counter], start, strlen(start)) == 0)
		{
			if (counter > 0)
				return strcpy(fullreadenfile, &fullreadenfile[counter + strlen(start)]);
			else if (counter == 0)
				return strcpy(fullreadenfile, &fullreadenfile[counter + strlen(start)- 1]);
		}
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
char *whatsBeforeThis(char *fullreadenfile, char *finish, char *whatsBefore)
{
    int counter;
	for (counter = 0; counter < strlen(fullreadenfile); ++counter)
	{
		if (strncmp(&fullreadenfile[counter], finish, strlen(finish)) == 0)
			return strncpy(whatsBefore, fullreadenfile, counter);
	}
    return "Empty";
}

/*
    I am searching for 2 keywords in a string.
    fullreadenfile is the searched string.
    I'm finding the string between first keyword and sec keyword.
    I'm searching with early defined functions "whatsAfterThis" and "whatsBeforeThis".
    I return the string between them.
    If there will be some errors, then return value will be Empty.
*/
char *whatsBetweenThese(char *fullreadenfile, char *start, char *finish, char *placetoPut)
{
	whatsBeforeThis(fullreadenfile, finish, placetoPut);
	whatsAfterThis(placetoPut, start);
	whatsAfterThis(fullreadenfile, finish);
	return placetoPut;
}

/*
	I am the hearth of all early defined functions.
	I am using all of them inside me.
	My job is finding <email> , </email> tags to finding emails
	Then I find <Subject>, </Subject tags to find the subject
	After that I find <Body>, </Body> tags and find the body.
	I need opened file pointer, two double dimentional arrays to put subject and body.
*/
void parsingMail(FILE *openedmail, char subject[mssEmail][mssSubject], char body[mssEmail][mssBody])
{
	int counter;
	char theFile[posibleChar] = "\0", mailweworkon[posibleChar] = "\0";
	readingFile(openedmail, theFile);
	for (counter = 0;
		whatsBetweenThese(theFile, "<email>", "</email>", mailweworkon) != "Empty" &&
		counter < mssEmail;
		++counter)
		{
			whatsBetweenThese(mailweworkon, "<Subject>", "</Subject>", subject[counter]);
			whatsBetweenThese(mailweworkon, "<Body>", "</Body>", body[counter]);
		}
	return;
}





void main()
{
    FILE *emails;
	char subject[mssEmail][mssSubject], body[mssEmail][mssBody];
    emails=fopen("emails.txt", "r");
    parsingMail(emails, subject, body);	
	printf(".......%s....\n\n", subject[0]);
	printf(".......%s....\n", body[0]);
    fclose(emails);
    return;
}
