#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define posibleChar	 4096	//Max readable chars from file.
#define mssEmail 16			//MeSage String for Email.
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

/*well working reading mail functions start*/
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
/*well working reading mails functions*/





/*well working printing functions start

these functions works very well. But their job is only printing '-', ' ' or printing some defined thing.
 I couldnt use them for printing expecting style.
*/
void fillthelane()
{
	int i;
	for (i = (mpBody + mpSubject +13); i > 0; --i)
		printf("-");
	printf("\n");
	return;
}

void witchmail(int square)
{
	if (square > 0)
		printf("|%4d |", square);
	else if (square == 0)
		printf("|%4c |", '#');
	else if (square == -1)
		printf("|%4c |", ' ');
	return;
}

void subjectonTop()
{
	int counter;
		printf("    subject    |");
	return;
}

void bodyonTop()
{
	int i;
	for (i = 0; i < 23; ++i)
		printf(" ");
	printf("body");
	for (i = 0; i < 27; ++i)
		printf(" ");
	printf("|\n");
	return;
}
/*well working printing functions end*/


/*
these are for using upper function tools and printing expected style.
	there is some lessnes on them. I think my algoriythm is ok but couldn't impliment them
	Thats why I cant print them like expected.
*/
void subjectinside(char subject[mpSubject])
{
	int i;
	char filler[mpSubject];
	if (strlen(subject) != 0)
	{

		printf("%s ", strtok(subject," "));
		for (i = 1; i < 3; ++i)
		{
			printf("%s ", strtok(NULL, " "));
		}
		if (strlen(subject) < mpSubject)
			for (i = 0; i < (mpSubject - strlen(subject)); ++i)
				printf("%c", ' ');
		printf("%c", '|');
	}
	else
		printf("%15c|", ' ');
	return;
}

void bodyinside(char body[mpBody])
{
	printf("%s|\n", body);
	return;
}

void specialMailPrint(char subject[mssEmail][mssSubject], char body[mssEmail][mssBody])
{
	int counter, sub, bdy;
	char fillerS[mpSubject+1], fillerB[mpBody+1];
	fillthelane();
	witchmail(0);
	subjectonTop();	
	bodyonTop();
	fillthelane();
	for (counter = 0; strcmp(subject[counter], "Empty") != 0 && counter < mssEmail; ++counter)
	{
		witchmail(counter + 1);
		for (sub = 0; strlen(subject[counter]) > mpSubject && strlen(body[counter]) > mpBody && sub<3; ++sub)
		{
			if (sub == 0)
			{
				subjectinside(strncpy(fillerS, subject[counter], mpSubject));
				bodyinside(strncpy(fillerB, body[counter], mpBody));
			}
			else
			{
				witchmail(-1);
				subjectinside(strncpy(fillerS, &subject[counter][sub*mpSubject], mpSubject));
				bodyinside(strncpy(fillerB, &body[counter][sub*mpBody], mpBody-1));
			}
		}
		
	}

	return;
}
/*wrong functions end*/


void main()
{
    FILE* emails;
	char subject[mssEmail][mssSubject], body[mssEmail][mssBody];
    emails=fopen("emails.txt", "r");
    parsingMail(emails, subject, body);	
	specialMailPrint(subject, body);
    fclose(emails);
    return;
}
