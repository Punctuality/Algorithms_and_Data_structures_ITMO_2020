#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

char *get_line(int line_capacity) {

    char *line = malloc(line_capacity), *linep = line;
    size_t len_max = line_capacity, len = len_max;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        // Reallocation, in case capacity is not enough.
        if(--len == 0) {
            len = len_max;
            char *linen = realloc(linep, len_max *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        *line++ = (int) c; // TODO Maybe need to fix this one.

        if (c == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int str_to_int(char *str){
    return strtoimax(str, NULL, 10);
}