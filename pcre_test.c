#include <stdlib.h>
#include <pcre.h>

#define NGX_REGEX_CASELESS    PCRE_CASELESS

typedef struct {
    pcre        *code;
    pcre_extra  *extra;
} ngx_regex_t;


int main()
{

    pcre  *re;
    char       *errstr;
    int  erroff;

    int captures =0, named_captures, name_size;
    char  *name;

    //char  *data = "(?<gggg>dddd)(?<abcdefchijk>adsfasdf)(?=eeeee)(?<abbc> exception)(?<adfa>xydz)(ddddd)\\k<abbc>\\1\\2";
    //char  *data = ("message (\\d\\d\\d).*Codeword is '(?<cw>\\w+)'");
    char  *data = ("abc");
    int n, i;
    char  *p; 
    int        ngx_captures[300];


    printf("%s \n", data);

    p = data;

    printf("%s \n", p);

    re = pcre_compile(data, PCRE_CASELESS, &errstr, &erroff, NULL);

    //n = pcre_exec(re, NULL, "This is message 123. Codeword is 'foobar'.This is message 123. Codeword is 'foobar'.", \
     //       strlen("This is message 123. Codeword is 'foobar'.This is message 123. Codeword is 'foobar'."), 0, 0,ngx_captures, 300);

    n = pcre_exec(re, NULL, "abc abc", \
            strlen("abc abc"), 0, 0,ngx_captures, 300);
    if(NULL == re)
    {
        printf("compile pcre failed\n");

        return 0;
    }


    n = pcre_fullinfo(re, NULL, PCRE_INFO_CAPTURECOUNT, &captures);

    if(n < 0)
    {
        printf("pcre_fullinfo PCRE_INFO_CAPTURECOUNT failed %d \n", n);

        return 0;

    }         

    printf(" captures %d \n", captures);


    n = pcre_fullinfo(re, NULL, PCRE_INFO_NAMECOUNT, &named_captures);

    if(n < 0)
    {
        printf("pcre_fullinfo PCRE_INFO_NAMECOUNT failed %d \n", n);

        return 0;

    }

    printf("named_captures %d \n", named_captures);

    n = pcre_fullinfo(re, NULL, PCRE_INFO_NAMEENTRYSIZE, &name_size);

    if(n < 0)
    {
        printf("pcre_fullinfo PCRE_INFO_NAMEENTRYSIZE failed %d \n", n);

        return 0;

    }


    printf("name_size %d \n", name_size);


    n = pcre_fullinfo(re, NULL, PCRE_INFO_NAMETABLE, &name);
    if(n < 0)
    {
        printf("pcre_fullinfo PCRE_INFO_NAMETABLE failed %d \n", n);

        return 0;

    }


    p =name;
    int j;
    for(j = 0; j < named_captures; j++)
    {
        for(i = 0; i <2; i++)
        {

            printf("%x ", p[i]);      
        }



        printf("%s \n", &p[2]);
        p += name_size;


    }
    return 1;
}
