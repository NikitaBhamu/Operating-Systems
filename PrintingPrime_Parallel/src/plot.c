#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>


int main(){
    FILE *gnuplotpipe;
    gnuplotpipe = popen("gnuplot -persistent", "w");
    fprintf(gnuplotpipe, "set title \"Time taken by ith thread\"\n");
    fprintf(gnuplotpipe, "set terminal png\n");
    fprintf(gnuplotpipe, "set output \"../output/plot.png\"\n");
    fprintf(gnuplotpipe, "set xlabel \"i\"\n");
    fprintf(gnuplotpipe, "set ylabel \"Naive\"\n");
    fprintf(gnuplotpipe, "set y2label \"Load Balanced\"\n");
    fprintf(gnuplotpipe, "set y2range [0:1]\n");
    fprintf(gnuplotpipe, "set y2tics border nomirror\n");
    fprintf(gnuplotpipe, "set ytics border nomirror\n");
    fprintf(gnuplotpipe, "plot '../output/naive_threadTime.txt' using 1:2 w lp axis x1y1 title 'Naive', '../output/load_balanced_threadTime.txt' using 1:2 w lp axis x1y2 title 'Load balanced'\n");
    fclose(gnuplotpipe);
    return 0;
}
