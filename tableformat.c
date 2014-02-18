#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>

/**
 * @berief Format text table
 * @author informationsea
 */

int main(int argc, char *argv[])
{
    char buf[1024*1024];
    int *fields;
    int maximum_field_num = 0; /* array size */
    int field_num = 20; /* memory size */
    int current_field_num = 0;
    int current_field_width = 0;
    FILE* input = stdin;
    FILE *output = stdout;
    char separetor[1024] = " | ";
    char inputseparetor = '\t';

    int ch;

    while((ch = getopt(argc,argv,"?hs:e:")) != -1) {
	switch(ch) {
	case 'e':
	    inputseparetor = optarg[0];
	    break;
	case 's':
	    strncpy(separetor,optarg,sizeof(separetor)-1);
	    break;
	case 'h':
	case '?':
	    printf("Usage : %s [options] file\n",argv[0]);
	    printf("Format text table\n"
		   "   -h -? Show this help\n"
		   "   -s    Output separator (string) default:\"%s\"\n"
		   "   -e    Input separator (one char) default:TAB\n",separetor);
	    return 0;
	    break;
	default:
	    printf("Unknown options %c\n"
		   "Use -h option to show usages.",ch);
	    return 1;
	}
    }
    
    argc -= optind;
    argv += optind;

    fields = (int *)malloc(sizeof(int)*field_num);
    memset(fields,0,sizeof(int)*field_num);

    if (argc == 0){
        input = tmpfile();
        if (!input) {
            perror("Cannot open tempolary file");
            return 1;
        }
        while(!feof(stdin) && !ferror(stdin)) {
            size_t length = fread(buf,sizeof(buf[0]),sizeof(buf)/sizeof(buf[0]), stdin);
            fwrite(buf, sizeof(buf[0]), length, input);
        }
        fseek(input, 0, SEEK_SET);
    }else{
	input = fopen(argv[0],"r");
    }

    if(input == NULL){
	perror("Cannot open input file");
	return 1;
    }

    while(!feof(input) && !ferror(input)){
	size_t length = fread(buf,sizeof(buf[0]),sizeof(buf)/sizeof(buf[0]),input);
	char *p = buf;

	while(p < buf+length) {
	    if(*p == '\n' || *p == inputseparetor){
		if(field_num < current_field_num) {
		    field_num += 20;
		    fields = (int *)realloc(fields,sizeof(int)*field_num);
		}
		if(maximum_field_num < current_field_num) {
		    maximum_field_num = current_field_num;
		}
		if (fields[current_field_num] < current_field_width)
		    fields[current_field_num] = current_field_width;
		current_field_num++;
		current_field_width = 0;
		if (*p == '\n') {
		    current_field_num = 0;
		    current_field_width = 0;
		}
	    }else{
		current_field_width++;
	    }
	    p++;
	}
    }


    rewind(input);

    current_field_num = 0;
    current_field_width = 0;
    while(!feof(input) && !ferror(input)){
	size_t length = fread(buf,sizeof(buf[0]),sizeof(buf)/sizeof(buf[0]),input);
	char *p = buf;

	while(p < buf+length) {
	    if(*p == '\n'){
		current_field_width = 0;
		current_field_num = 0;
		fputc(*p,output);
	    }else if(*p == inputseparetor){
		while(current_field_width < fields[current_field_num]){
		    putchar(' ');
		    current_field_width++;
		}
		fprintf (output,"%s",separetor);
		
		current_field_num++;
		current_field_width = 0;
		if (*p == '\n') {
		    current_field_num = 0;
		    current_field_width = 0;
		}
	    }else{
		current_field_width++;
		fputc(*p,output);
	    }
	    p++;
	}
    }



    fclose(input);
    
    return 0;
}
