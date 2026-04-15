#include <stdio.h>
#include "s2html_event.h"
#include "s2html_conv.h"

int main (int argc, char *argv[])
{
    FILE *sfp, *dfp;
    pevent_t *event;
    char dest_file[100];

    if(argc < 2)
    {
        printf("Usage: ./a.out <file>\n");
        return 1;
    }

    sfp = fopen(argv[1], "r");
    if(!sfp)
    {
        printf("File open error\n");
        return 1;
    }

    sprintf(dest_file, "%s.html", argv[1]);
    dfp = fopen(dest_file, "w");

    html_begin(dfp, HTML_OPEN);

    do
    {
        event = get_parser_event(sfp);
        source_to_html(dfp, event);
    } while(event->type != PEVENT_EOF);

    html_end(dfp, HTML_CLOSE);

    fclose(sfp);
    fclose(dfp);

    printf("Output file generated: %s\n", dest_file);
}