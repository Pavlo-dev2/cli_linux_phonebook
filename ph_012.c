#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define ADDRESS "phonebook/ .txt"
#define POSOFLETER 10
#define MAXNAMELENGTH 20
#define MAXNUMBERLENGTH 30
char* findbyname(char name[]);
char* findbynumber(char name[]);
int add(char name[], char number[]);
int delate(char name[]);
int changenum(char name[], char number[]);

int main(int argc, char* args[])
{
	char f;
	if (argc == 4 && !strcmp("add", args[1]))
	{
		printf("Add\n");
		if (strlen(args[2]) < 2)
		{
			printf("This name is too short\n");
			return 1;
		}
		f = add(args[2], args[3]);
	}
	else if (argc == 4 && !strcmp("changenum", args[1]))
	{
		printf("Change number\n");
                if (strlen(args[2]) < 2)
                {
                        printf("This name is too short\n");
                        return 1;
                }
		f = changenum(args[2], args[3]);
	}
	else if (argc == 3 && !strcmp("delate", args[1]))
	{
		printf("Delate\n");
		if (strlen(args[2]) < 2)
                {
                        printf("This name is too short\n");
                        return 1;
                }
		f = delate(args[2]);
	}
	else if (argc == 3 && !strcmp("name", args[1]))
	{
		printf("Find by name\n");
		if (strlen(args[2]) < 2)
		{
			printf("This name is too short\n");
			return 0;
		}
		char *number = findbyname(args[2]);
		if (number == NULL)
		{
			printf("Error\n");
			return 1;
		}
		printf("Number: %s;\n", number);
	}
	else if (argc == 3 && !strcmp("number", args[1]))
	{
		printf("Find by number\n");
		findbynumber(args[2]);
	}
	else
	{
		printf("Invalid input;\n");
		return 1;
	}
	if (f != 0)
	{
		printf("Error\n");
		return 1;
	}
	return 0;
}

int add(char name[], char number[])
{
	if (findbyname(name) != NULL)
	{
		printf("This name is alredy in the phonebook!\n");
		return 1;
	}
	char adrs[] = ADDRESS;
	adrs[POSOFLETER] = name[0];
	FILE *fp = fopen(adrs, "a");
	if (fp == NULL)
	{
		return 1;
	}
	fprintf(fp, "%s: %s;\n", name, number);
	fclose(fp);
	return 0;
}

char *findbyname(char name[])
{
	if ((name[0] >= 'A' && name[0] <= 'Z') || (name[0] >= 'a' && name[0] <= 'z'))
	{
		//length of the name;
		int i;
		for (i = 0; name[i] != 0; i++);
		
		char adrs[] = ADDRESS;
		adrs[POSOFLETER] = name[0];
		//printf("Adress: %s\n", adrs);
		char *an = calloc(i, sizeof(char));
		char *number = calloc(MAXNUMBERLENGTH, sizeof(char));
		FILE *fp = fopen(adrs, "r");
		if (fp == NULL) { return NULL; }

		char io = 0;
		int e = 0;
		//printf("I: %d\n", i);
		for (char c; (c = fgetc(fp)) != EOF; e++)
		{
			//printf("An: %s e: %d, Num: %s\n", an, e, number);
			if (c == ':')
			{
				io = 1;
			}
			if (io == 0 && e < i)
			{
				an[e] = c;
			}
			char v;
			if (c == '\n')
			{
				io = 0;
				e = -1;
			}
			else if (e == i && an[0] != 0 && an[e+1] == 0 && c == ':')
			{
				if (!strcmp(an, name))
				{
					fgetc(fp);
					int b = 0;
					for (char k = fgetc(fp); k != ';' && k != EOF; k = fgetc(fp))
					{
						number[b] = k;
						b++;
					}
					fclose(fp);
					//printf("Number: %s;\n", number);	
					return number;
				}
			}
		}
		free(an);
		fclose(fp);
		return NULL;
	}
	else
	{
		return NULL;
	}
}

char *findbynumber(char num[])
{
	char adrs[] = ADDRESS;
	for (char c = 'A'; c <= 'z'; c++)
	{
		adrs[POSOFLETER] = c;

		FILE *fp = fopen(adrs, "r");

		char number[MAXNUMBERLENGTH] = {0};
		char *name = calloc(MAXNAMELENGTH, sizeof(char));
		if (fp != NULL)
		{
			char io = 0;
			int i = 0;//length of name
			int j = 0;//length of number
			for (char l = fgetc(fp); l != EOF; l = fgetc(fp))
			{
				//printf("Number: %s Name: %s, l: %c\n", number, name, l);
				if (l == ';')
				{

					for (j = j; j < MAXNUMBERLENGTH; j++)
                                       	{
                                       	        number[j] = 0;
                                        }
					if (!strcmp(number, num))
					{
						//fclose(fp);
						printf("Name: %s;\n", name);
					}
					j = 0;
				}
				if (io == 1 && l != ' ' && l != '\n' && l != ';')
				{
					number[j] = l;
					j++;
				}
				else if (l == ':')
				{
					//printf("%s\n", name);
					io = 1;
				}
				else if (io == 0)
				{
					name[i] = l;
					i++;
				}
				else if (l == '\n')
				{
					for (i = 0; i < MAXNAMELENGTH; i++)
					{
						name[i] = 0;
					}
					//printf("Name is empty!, %s\n", name);
					io = i = 0;
				}

			}
		}
		if (c == 'Z')
		{
			c = 'a' - 1;
		}
	}
	return NULL;
}

int delate(char name[])
{
	char adrs[] = ADDRESS;
	adrs[POSOFLETER] = name[0];

	FILE *fp = fopen(adrs, "r");
	if (fp == NULL) { return 1; }

	unsigned long length = 0;
	for (char c; (c = fgetc(fp)) != EOF; length++);
	//printf("Length: %lu\n", length);

	char *copy = calloc(length, sizeof(char));
	if (copy == NULL) { return 1; }

	rewind(fp);
	for (int i = 0; i < length; i++)
	{
		copy[i] = fgetc(fp);
	}
	//printf("Copy:\n%s", copy);

	fclose(fp);
	fp = fopen(adrs, "r+");
	if (fp == NULL) { return 1; }

	char namelength = strlen(name);
	char *an = calloc(namelength, sizeof(char));
	unsigned long ac = 0, st = 0;
	char io = 0;
	char i = 0;
	for (char c; (c = fgetc(fp)) != EOF; ac++)
	{
		//printf("C:%c, An: %s, i: %d\n", c, an, i);
		if (c == ':')
		{
			if (i == namelength)
			{
				if (!strcmp(an, name))
				{
					//printf("I: %d; namelength: %d; c1: %d; c2: %d;\n", i, namelength, (i+1 < namelength), !strcmp(an, name));
					//printf("Name found\n");
					for (ac; copy[ac] != '\n'; ac++);
					fseek(fp, st, SEEK_SET);
					fprintf(fp, "\n%s", copy + (ac+1));
					int fd = fileno(fp);
					long pos = ftell(fp);
					ftruncate(fileno(fp), pos);
				        free(an);
        				fclose(fp);
        				return 0;
				}
			}
			for (int v = 0; an[v] != 0; v++)
			{
				an[v] = '\0';
				//printf("ANV: %c\n", an[v]);
			}
			io = 1;
			i = 0;
		}
		if (io == 0)
		{
			an[i] = c;
			i++;
		}
		else if (c == '\n')
		{
			st = ac;
			io = 0;
		}
	}
	free(an);
	fclose(fp);	
	return 1;
}
int changenum(char name[], char number[])
{
	int f = 0;
	if (strcmp(findbyname(name), number))
	{
		if (delate(name) || add(name, number))
		{
			return 1;
		}
	}
	return 0;
}
