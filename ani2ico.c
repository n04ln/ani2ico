#include <stdio.h>
#include <stdlib.h>

int find_icon(FILE *fp) {
    int cnt = 0;
    int c;
    char cc;

    c = fgetc(fp);
    // Fuxxin' solution
    while(c!=EOF){
        cc = (char)c;
        if (cnt == 0 && c == 'i' ||
            cnt == 1 && c == 'c' ||
            cnt == 2 && c == 'o' ||
            cnt == 3 && c == 'n') {
            cnt++;
        } else {
            cnt = 0;
        }

        if (cnt == 4) {
            return c;
        }
        c = fgetc(fp);
    }
    return EOF;
}

int find_next_icon(FILE *fp, char* tmp) {
    int cnt = 0;
    char cc;
    int c;
    int char_idx = 0;

    c = fgetc(fp);
    // Fuxxin' solution
    // TODO: Support only "6963 6f6e XXXX 0000 .... 6e63 6f6e XXXX 0000 ...." format.
    //       So, if invalid sequence, cannot parse ;<
    while(c!=EOF){
        cc = (char)c;
        if (cnt == 0 && c == 'i' ||
            cnt == 1 && c == 'c' ||
            cnt == 2 && c == 'o' ||
            cnt == 3 && c == 'n') {
            cnt++;
        } else {
            cnt = 0;
        }

        tmp[char_idx] = cc;
        char_idx++;

        if (cnt == 4) {
            printf("%d\n", char_idx);
            return char_idx-5;
        }

        c = fgetc(fp);
    }
    return char_idx-1;
}
 
int main(int argc, char *argv[]){
    if (argc != 3) {
        fprintf(stderr, "usage: ani2ico {src} {dst}\n");
        return -1;
    }
    char *src, *dst;
    src = argv[1];
    dst = argv[2];
    FILE *fp, *wfp;
    int c;
    char cc;

    fp = fopen(src,"r");
    if(fp==NULL){
        printf("faied open ani file");
        return -1;
    }

    find_icon(fp);
    char *tmp;
    int len;
    tmp = (char *)malloc(100000);
    len = find_next_icon(fp, tmp);
    for(int i = 0; i < len; i++) {
        printf("%02x ", tmp[i]);
    }

    fclose(fp);
    
    wfp = fopen(dst,"w");
    if(wfp==NULL){
        printf("faied open output file");
        return -1;
    }

    for(int i = 4; i < len; i++) {
        /* printf("%02x ", tmp[i]); */
        fputc(tmp[i], wfp);
    }
    fputc(EOF, wfp);
    fclose(wfp);
    return 0;
}

