//Jimmy Lauchoy CS3224-B
//HW1

#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];  //buffer
char store[512][512];   //stored from read
int inX[512];   //x coordinates
int inY[512];   //y coordinates
int lines = 10;

void tail(int fd, char * name) {
    int i, j, c, x, y, m, n;
        //i and j used in for loops
        //c used to count number of lines
        //x and y are coordinates of new lines
        //m and n are coordinates assigned to start print
    inX[0] = 0; inY[0] = 0;
    j = -1;      x = 0;      y = 0;
    while((n = read(fd, buf, sizeof(buf))) > 0) {
        j++;
        j%=512;
        for(i = 0; i < n; i++) {
                    store[j][i] = buf[i];
            if(buf[i] == '\n') {
                x++;    y++;    c++;
                x%=lines+1;
                y%=lines+1;
                inX[x] = j;
                inY[y] = i;
            }
                    m=i;
        }
    }
    if(n < 0) {
        printf(1, "tail: read error\n");
        exit();
    }
    inX[x] = j;
    inY[y] = m;
    m = x+1;
    n = y +1;
    if(c-lines >= 0){
        m%=lines;
        n%=lines;
    }
    i = inX[m];
    j = inY[n];
    if(store[i][j] == '\n') { j++; }
    while(i < inX[x]) {
        while(j < 512) {
            printf(1, "%c", store[i][j]);
            j++;
        }
        i++;
        j=0;
    }
    while(j <= inY[y]) {
        printf(1, "%c", store[i][j]);
        j++;
    }
}
int main(int argc, char * argv[]) {
    int fd, l, i;
    char *argA;
    if (argc <= 1) {
        tail(0, "");
        exit();
    }
    argA = argv[1];
    if (argA[0] == '-') {
        l = atoi(argA + 1);
        if (l == 0) {
            exit();
        }
        lines = l+1;
        if( argc <= 2) {
            tail(0, "");
            exit();
        }
        i = 2;
    }
    else {
        i=1;
    }
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "tail: cannot open %s\n", argv[i]);
      exit();
    }
    tail(fd, argv[i]);
    close(fd);
    exit();
}
