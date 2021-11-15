#include <fstream>
#include <string.h>

#include <sndfile.h>

#define	BUFFER_LEN			4096

int main(int argc, char **argv){
    // frame = sample
    // ler o framerate do .wav origem
    if(argc != 3){	
        puts("please give input and output file:");
        puts("Usage: ./bin/ex3sndfile <input_file> <output_file>");
		exit (1);
    } ;

    SNDFILE *infile, *outfile;
    SF_INFO sfinfo;

    memset (&sfinfo, 0, sizeof (sfinfo));

    if (! (infile = sf_open (argv[1], SFM_READ, &sfinfo))){
        printf("Error : could not open file : %s\n", argv[1]);
		puts(sf_strerror (NULL));
		exit(1);
    }

    // o formato deve estar bem mas fica aqui para referência
    if (!sf_format_check (&sfinfo)){	
        sf_close(infile);
		printf("Invalid encoding\n");
        puts("finishing program...");
		return 0;
    }

    if(!(outfile = sf_open (argv[2], SFM_WRITE, &sfinfo)))
	{	printf("Error : could not open file : %s\n", argv[2]);
		puts(sf_strerror(NULL));
		exit(1);
	};

    static float buffer [BUFFER_LEN];
    int readcount;

    while((readcount = (int) sf_read_float(infile, buffer, BUFFER_LEN)) > 0)
		sf_write_float(outfile, buffer, readcount);

	sf_close(infile);
	sf_close(outfile);

    return 0;
}