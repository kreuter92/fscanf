/**
*	Projekt geforked von https://github.com/bjoekeldude/fscanf
*/


#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

const char VERSIONSNR[] = "0.1.2";

const int DB_SIZE = 20;

typedef struct person_t{
	int personalnummer;
	char nachname[20];
	char vorname[20];
	int geburtsjahr;
} person_t;

void readcsv(char *datei)
{
	FILE *filepointer = NULL;
	int zaehler = 0;
	//check for empty file
	if(NULL == (filepointer = fopen(datei, "r")))
	{
		fprintf(stderr, "Couldnt open file '%s'\n", datei);
		exit(2);
	}
	person_t database[DB_SIZE];
	while((fscanf(filepointer, "%d,%[^,],%[^,],%d", &database[zaehler].personalnummer,
			 database[zaehler].nachname, database[zaehler].vorname,
			 &database[zaehler].geburtsjahr))!= EOF)
		{		
			printf("%d, %s, %s, %d \n", database[zaehler].personalnummer, 
			database[zaehler].nachname, database[zaehler].vorname,
			database[zaehler].geburtsjahr);
			zaehler++;
		}
	//check if file closed correctly	
	if(fclose(filepointer) == EOF)
	{
		fprintf(stderr, "Fehler beim schließen der Datei! \n");
		exit(2);
	}
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "No option recognized. Wrong Usage. Please try -h\n");
	}
	
	int option;

	while((option = getopt(argc, argv, "hvf:"))!=-1)
	{
		switch(option)
		{
			case 'h':
				printf("Bitte -f nutzen um einen File-Path anzugeben\n");
				exit(0);
			case 'v':
				printf("Version %s\n", VERSIONSNR);
				exit(0);
			case 'f':
				readcsv(optarg);
				break;
			case '?':
				fprintf(stderr ,"Please try -h\n");
				exit(1);
		}
	}

	return 0;
}

