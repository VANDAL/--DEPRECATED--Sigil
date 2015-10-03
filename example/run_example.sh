#!/bin/bash

#Clean up previous runs
rm *.gz

#<SIGIL_PATH>/runsigil_and_gz.py <sigil options> <user binary>
../runsigil_and_gz.py --fair-sched=yes --tool=callgrind --separate-callers=100 --toggle-collect=main --cache-sim=yes --dump-line=no --drw-func=no --drw-events=yes --drw-splitcomp=1 --drw-intercepts=yes --drw-syscall=no --branch-sim=yes --separate-threads=yes --callgrind-out-file=callgrind.out.threads ./FFT -m16 -p8 -l6
../tools/generate_pthread_file.py err.gz
