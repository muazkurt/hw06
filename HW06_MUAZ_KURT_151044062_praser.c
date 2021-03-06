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

/*
	I am searching for dest in source
	If i find in it, i return 1.
	else i return 0;
*/
int searchinside(char *dest, char *source)
{
	int counter;
	for (counter = 0; counter <= strlen(source); ++counter)
	{
		if (strncmp(dest, &source[counter], strlen(dest)) == 0)
			return 1;
	}
	return 0;
}

/*
	finds the dest string's position in source file.
*/
int searchtheposition(char *dest, char *source)
{
	int counter;
	for (counter = 0; counter <= strlen(source); ++counter)
	{
		if (strncmp(dest, &source[counter], strlen(dest)) == 0)
			return counter;
	}
	return -1;
}

/*
I take a file and i look up it.
If there will be an error i return the line number of it.
If there is not any error i return -1;
*/
int detectErrorsforEmail(FILE *mailfile)
{
	char mail[2048], *ef;
	int email = 0,
		subject = 0,
		body = 0,
		line, error = 0;
	for (line = 0; error == 0; ++line)
	{
		ef = fgets(mail, 1024, mailfile);
		email += searchinside("<email>", mail);
		email -= searchinside("</email>", mail);
		subject += searchinside("<Subject>", mail);
		subject -= searchinside("</Subject>", mail);
		body += searchinside("<Body>", mail);
		body -= searchinside("</Body>", mail);
		if (ef == NULL)
		{
			if (email == 0 ||
				subject == 0 ||
				body == 0)
				--error;
			else
				++error;
		}
		else if (email < 0 || email > 1 ||
			subject < 0 || subject > 1 ||
			body < 0 || body > 1)
			++error;
	}
	if (error == 1)
		return line;
	return -1;
}

/*
	detecting errors on token file
*/
int detectingErrorsforToken(FILE *tokenfile)
{
	char token[60], *ef;
	int i, error = 0, sign, value = 0, positive;
	for (i = 0; error == 0; ++i)
	{
		ef = fgets(token, 60, tokenfile);
		sign = searchinside("=", token);
		if (sign == -1)
			++error;
		else
		{
			positive = sscanf(&token[searchtheposition("=", token) + 1], "%d", &value);
			if (positive != 1)
				++error;
		}
		if (ef == NULL)
			--error;
	}
	if (error > 0)
		return i;
	return -1;
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
    return "ERROR";
}

/*
    I am searching for a keyword in a string.
    fullreadenfile is the searched string.
    If i find the keyword, then i return the string before the keyword.
    I am not update the given string because it possibly cause data loss.
    If i cant find the keyword in given string,
    Then i return ERROR as there is no keyword.
*/
char *whatsBeforeThis(char *fullreadenfile, char *finish, char *whatsBefore)
{
    int counter;
	for (counter = 0; counter < strlen(fullreadenfile); ++counter)
	{
		if (strncmp(&fullreadenfile[counter], finish, strlen(finish)) == 0)
			return strncpy(whatsBefore, fullreadenfile, counter);
	}
    return "ERROR";
}

/*
    I am searching for 2 keywords in a string.
    fullreadenfile is the searched string.
    I'm finding the string between first keyword and sec keyword.
    I'm searching with early defined functions "whatsAfterThis" and "whatsBeforeThis".
    I return the string between them.
    If there will be some errors, then return value will be ERROR.
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
		searchinside("ERROR", whatsBetweenThese(theFile, "<email>", "</email>", mailweworkon)) == 0 &&
		counter < mssEmail;
		++counter)
		{
			whatsBetweenThese(mailweworkon, "<Subject>", "</Subject>", subject[counter]);
			whatsBetweenThese(mailweworkon, "<Body>", "</Body>", body[counter]);
		}
	return;
}
/*well working reading mails functions*/





/*well working printing functions start*/
/*
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
	for (counter = 0; searchinside("ERROR", subject[counter]) == 0 && counter < mssEmail; ++counter)
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
	printf("\n");
	return;
}
/*wrong functions end*/


void main()
{
    FILE* emails, *token;
	char subject[mssEmail][mssSubject], body[mssEmail][mssBody];
	int error;
	emails=fopen("emails.txt", "r");
	error = detectErrorsforEmail(emails);
	if (error == -1)
		;
	else if (error > 0)
		printf("mail error in %d line\n", error);
	parsingMail(emails, subject, body);	
	//specialMailPrint(subject, body);
    fclose(emails);
	token = fopen("token.txt", "r");
	error = detectingErrorsforToken(token);
	if (error == -1)
		;
	else if (error > 0)
		printf("mail error in %d line\n", error);
	fclose(token);
    return;
}
