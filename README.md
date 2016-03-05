#**Deprecated soon -- being replaced by [SIGIL2](https://github.com/mdlui/Sigil2)**

#What is Sigil?

#####Overview

Sigil is a Valgrind tool designed to help the HW/SW partitioning problem.

This is a modified version of Sigil for use in the [SynchroTrace] framework.
For information on the previous version of Sigil, please see: 
https://github.com/snilakan/Sigil

#####Building Sigil

We offer a setup script to automatically detect missing package
dependencies and build the tool. 

```sh
$ cd setup
$ ./setup_sigil.sh
```

If you would rather build the tool manually, you can run the following:
   
```sh
$ cd valgrind-3.10.1
$ ./autogen.sh
$ ./configure
$ ./make check
```

#####Compiling User Programs

Prior to generating traces through executing Sigil on the user program, one 
must compile the synchronization function intercept wrapper script as a
shared object. This wrapper script enables detecting and logging Pthread calls
and OpenMP during trace capture. Currently this wrapper is written to support
common OpenMP 4.0 functions (along with Pthread calls) with gcc 4.9. The source
code to this pthread wrapper is tools/wrapper_openmp.c and must first be
compiled then dynmically preloaded during the trace generation of the user
program. Compiling the wrapper for capturing OpenMP function calls requires 
the source gcc library associated with the locally used gcc binary.

An example of compiling this wrapper script follows:

Download and untar the gcc source library for the locally used gcc binary:

```sh
$cd <SIGIL_PATH>/tools
$wget http://www.netgull.com/gcc/releases/gcc-4.9.2/gcc-4.9.2.tar.gz
$tar zxf gcc-4.9.2.tar.gz && rm gcc-4.9.2.tar.gz
```
Compile the wrapper script:

```sh
$cd <SIGIL_PATH>/tools
$gcc -Wall -g -DVGO_linux=1 -fPIC <SIGIL_PATH>/tools/wrapper_openmp.c -I ../valgrind-3.10.1/include/ -I ../valgrind-3.10.1/ -I ../valgrind-3.10.1/callgrind -I gcc-4.9.2/libgomp/ -I gcc-4.9.2/libgcc/ -I gcc-4.9.2/libgomp/config/linux/ -shared -o wrapper.so
```

#####Running Sigil

An included script will run Sigil with the most common options. Note that
the user must first edit this script with some default paths to let it know
where is the sigil directory.

```sh
$ ./runsigil_and_gz.py <sigil options> <user binary>
```

This results in trace files called "sigil.events.out-<thread_number>.gz"
For example if I wanted to get sigil traces for an 8-thread execution of the FFT benchmark:

```sh
$ LD_PRELOAD=<SIGIL_PATH>/tools/wrapper.so ./runsigil_and_gz.py --fair-sched=yes --tool=callgrind --separate-callers=100 --toggle-collect=main --cache-sim=yes --dump-line=no --drw-func=no --drw-events=yes --drw-splitcomp=1 --drw-intercepts=yes --drw-syscall=no --branch-sim=yes --separate-threads=yes --callgrind-out-file=callgrind.out.threads ./FFT -m16 -p8 -l6 -t
```

After the traces are generated, a pthread meta-data file (sigil.pthread.out) must be created by using the generate_pthread_file.py script on the generated err.gz file.

```sh
$ ./generate_pthread_file.py err.gz
```

More information about running the tool and its options can be found in the
provided documentation.

#####Running provided example

We include an FFT example derived from the Splash-2 benchmark suite for a
statically compiled benchmark.
First build Sigil using the instructions above in "Building Sigil" and navigate
back to the main Sigil folder. 
Then follow the instructions below:

```sh
$ cd tools
$ gcc -static -Wall -g -DVGO_linux=1 -c wrapper.c -I ../valgrind-3.10.1/include/ -I ../valgrind-3.10.1/ -I ../valgrind-3.10.1/callgrind -o wrapper.o
$ cd ..
```

The wrapper should now be compiled.

```sh
$ cd example
```

In this example folder you should find a Makefile for the FFT example. Note the CFLAGS variable in the Makefile.
To use Sigil to generate traces, we need the following flags to be added: "-g -static <SIGIL_PATH>/tools/wrapper.o".
Such a line is already provided in the Makefile, but is commented out. Uncomment the appropriate line and comment out the line that is active by default.

```sh
$ make
$ ./run_example.sh
```

run_example.sh is a bash script that contains the lines mentioned above in the
"Running Sigil" section.
If you modified the Makefile correctly, when the bash script finishes, the
folder should contain traces for all the 8 threads (-p8 runs the 8-threaded
version of FFT) and the pthread meta-data file.
This folder can simply be specified for the Replay portion of SynchroTrace.

#####Restrictions

Sigil is a Valgrind tool, and as such, is 
only officially supported in LINUX.

What programs can be profiled by the tool? (Restrictions/Known issues)

As the tool incurs slowdown already, some restrictions were placed
purposefully on the user program, so that writing optimized code would be 
somewhat easier and the memory behavior of the tool is more determinate.

The restrictions are as follows:

   1. The maximum depth of the calltree in the user program (after main) 
      must not exceed the <number> - 10, specified in the
      --separate-callers=<number> option

      The default for <number> in the wrapper script is 400, but it can 
      simply be the maximum depth of the calltree in the user program + 10. 
      The additional 10 is just a buffer for the functions before main() 
      and after exit().

   2. The number of functions in the program must not exceed 10,000. 
      (hardcoded)

   3. Sigil cannot handle address values above 256G currently. 

   4. Applications with a large memory footprint can cause Sigil to exceed 
      memory bounds set by Valgrind or the system. 

      If such an error is encountered, we recommend running with smaller 
      input sets.

   5. Applications with very large call depth can also cause Sigil to exceed 
      memory bounds. Currently, there is no workaround for this, but we are 
      working on a long term solution that could mean tighter integration 
      with Callgrind.
