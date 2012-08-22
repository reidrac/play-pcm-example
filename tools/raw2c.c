/*
 * Convert a RAW 8bits 8KHz sample in a C include.
 *
 *  Juan J. Martinez <jjm@usebox.net>
 *  https://github.com/reidrac/play-pcm-example
 */
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    FILE *fd_in, *fd_out;
    unsigned char byt;
    char name[16], *p;
    unsigned short length = 0;

    if(argc!=3)
    {
        fprintf(stderr, "usage: %s infile.raw outfile.h\nThe raw file is expected to contain raw audio data (8bits 8KHz).\n", argv[0]);
        return 1;
    }

    fd_in = fopen(argv[1], "r");
    if(!fd_in)
    {
        fprintf(stderr, "failed to open %s\n", argv[1]);
        return 1;
    }

    fd_out = fopen(argv[2], "w");
    if(!fd_out)
    {
        fclose(fd_in);
        fprintf(stderr, "failed to open %s\n", argv[2]);
        return 1;
    }

    printf("Converting %s into %s...\n", argv[1], argv[2]);

    for(byt=0, p=argv[2]; *p && *p!='.' && byt<16; byt++, p++)
    {
        name[byt] = *p;
    }

    name[byt] = 0;

    fprintf(fd_out, "/* converted from %s */\n", argv[1]);
    fprintf(fd_out, "const unsigned char %s[] PROGMEM = { ", name);

    while(!feof(fd_in))
    {
       byt = fgetc(fd_in);
       fprintf(fd_out, "0x%x", byt);
       length++;
       if(!feof(fd_in))
          fprintf(fd_out, ", ");
    }

    fprintf(fd_out, " };\n");
    fprintf(fd_out, "const unsigned short %s_len = %d;\n", name, length);

    fclose(fd_in);
    fclose(fd_out);

    printf("done!\n");

    return 0;
}
