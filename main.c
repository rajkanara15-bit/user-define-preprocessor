/******************************************************************************

my Preprocessor.

*******************************************************************************/
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include"myheader.h"
void comment_removal();
void headerFile_inclusion(FILE *);
void macro_replacement(char *);


int main(int argc, char **argv)
{
  
    char outputFile[100];

    macro_replacement(argv[1]); 
    comment_removal();    
    
    // output file name : filename.i;
    strcpy(outputFile, argv[1]);
    strcat(outputFile, ".i");
	
    // Indicate that output file is generated.		
    printf("%s", outputFile);


    // provide output file to store final content. 
    FILE *final = fopen(outputFile, "w");
    headerFile_inclusion(final); 
    fclose(final);

    remove("source.macro");
    remove("source.clean");

    return 0;

}

//------------------------------------------------------------------------------------------------------------------------------------------------------------

void headerFile_inclusion(FILE *of)
{
    FILE *fp = fopen("source.clean", "r");

    if (fp == 0)
    {
        printf("Could not open source.clean");
        return;
    }

    char s[100];

    while (fgets(s, 100, fp))
    {
        if (strstr(s, "#include"))
        {
            char headerFile[50] = "";

            int i = 8;
            int j = 0;

            // Skip spaces after #include
            while (s[i] == ' ' || s[i] == '\t')
                i++;

            // Check <stdio.h> or "myheader.h"
            int predefined = (s[i] == '<');

            // Move past < or "
            i++;

            // Get header file name
            while (s[i] != '>' && s[i] != '"' && s[i] != '\0')
            {
                headerFile[j++] = s[i++];
            }

            headerFile[j] = '\0';

            printf("\nHeader found: %s\n", headerFile);

            FILE *hf = NULL;

            // Predefined header
            if (predefined)
            {
               
                   char path[200] = "C:/MinGW/include/";

                strcat(path, headerFile);

                printf("Trying: %s\n", path);

                hf = fopen(path, "r");
            }
            else
            {
                // User-defined header
                hf = fopen(headerFile, "r");
            }

            // Copy header contents
            if (hf)
            {
                char line[200];

                while (fgets(line, sizeof(line), hf))
                {
                    fputs(line, of);
                }

                fclose(hf);
            }
            else
            {
                printf("Could not open header: %s\n", headerFile);
            }
        }
        else
        {
            fputs(s, of);
        }
    }

    fclose(fp);
}

//--------------------------------------------------------------------------------------------------------------------------------------

void macro_replacement(char *p) {

    FILE *fp = fopen(p, "r");
    FILE *of = fopen("source.macro", "w");

    int i, lines = 0;
    char s[100];

    // total numbers of macros present in file
    while (fgets(s, 100, fp)) {

        if (strstr(s, "#define"))
            lines++;

        if (strstr(s, "main"))
            break;
    }

    char **macroNames = malloc(sizeof(char *) * lines);
    char **macroBodies = malloc(sizeof(char *) * lines);

    for (i = 0; i < lines; i++) {
        macroNames[i] = malloc(sizeof(char) * 50);
        macroBodies[i] = malloc(sizeof(char) * 100);
    }

    // Store all the macross in 2d array.
    rewind(fp);

    int index = 0;

    while (fgets(s, 100, fp)) {

        if (strstr(s, "#define")) {

            char name[50];
            char body[100];

            /*
             * FIX:
             * %s was taking only the first word.
             *
             * Example:
             * #define MESSAGE "Hello from preprocessor"
             *
             * Old:
             * body = "Hello
             *
             * New:
             * body = "Hello from preprocessor"
             */
            sscanf(s, "#define %s %[^\n]", name, body);

            strcpy(macroNames[index], name);
            strcpy(macroBodies[index], body);

            index++;
        }
    }

    // replacements of macross
    rewind(fp);
    
    while (fgets(s, sizeof(s), fp)) {

        if (strstr(s, "#define"))
            continue;

        for (i = 0; i < lines; i++) {

            /*
             * FIX:
             * Replace all occurrences instead of only
             * replacing the first occurrence.
             */
            char *pos = strstr(s, macroNames[i]);

            while (pos) {

                char temp[200] = "";

                // line content before position.
                int prefixLen = pos - s;

                strncat(temp, s, prefixLen);

                // add macro body.
                strcat(temp, macroBodies[i]);

                // add remaining content.
                strcat(temp, pos + strlen(macroNames[i]));

                strcpy(s, temp);

                // Search again for same macro.
                pos = strstr(s, macroNames[i]);
            }
        }
        
        fputs(s, of);
    }

    fclose(fp);
    fclose(of);
}


//-------------------------------------------------------------------------------------------------------------------------------------

void comment_removal() {

    FILE *fp = fopen("source.macro", "r");
    FILE *of = fopen("source.clean", "w");

    if (fp == NULL) {
        printf("File error");
        return;
    }

    char s[200];
    int flag = 0;

    while (fgets(s, sizeof(s), fp)) {

        int i = 0;
        int j = 0;
        char result[200] = "";

        while (s[i] != '\0') {

            // Inside multiline comment
            if (flag) {

                if (s[i] == '*' && s[i + 1] == '/') {
                    flag = 0;
                    i += 2;
                    continue;
                }

                i++;
                continue;
            }

            // Single line comment
            if (s[i] == '/' && s[i + 1] == '/') {
                break;
            }

            // Multiline comment
            if (s[i] == '/' && s[i + 1] == '*') {
                flag = 1;
                i += 2;
                continue;
            }

            // Normal character
            result[j++] = s[i];
            i++;
        }

        result[j] = '\0';

        fputs(result, of);
    }

    fclose(fp);
    fclose(of);
}