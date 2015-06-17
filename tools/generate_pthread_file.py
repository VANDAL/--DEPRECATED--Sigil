#! /usr/bin/env python
import sys
import re
import gzip

def usage() :
	print "Usage:"
	print "\t" + sys.argv[0] + " [<file>]"
	print "\t Cannot continue. Sorry."
	print ""

def main() :
	global filename
	# fi filename
	if len( sys.argv ) != 2 :  # no file name
		usage()
		sys.exit(1)
	else :
		filename = sys.argv[1]

	if ".gz" in filename :
		file = gzip.open( filename, 'r' )
	else :
		file = open( filename, 'r' )

        #Pthread create exit in thread 1 for thread 85985600!
        patString = "^Pthread create exit in thread 1 for thread (\d+)!"
        pattern1 = re.compile( patString )
        #Creating thread 2
        patString = "^Creating thread (\d+)"
        pattern2 = re.compile( patString )
        #Barrier 6901920 in Threadmap 1048574
        patString = "^Barrier (\d+) in Threadmap (\d+)"
        pattern3 = re.compile( patString )

        #List of pthread threads
        pthread_threads =[]
        #List of system threads
        system_threads =[]
        #List of barrier, threadmap tuples
        barrier_threadset = []
        
        for line in file :
            line = line.strip()
            match1 = pattern1.search( line )
            match2 = pattern2.search( line )
            match3 = pattern3.search( line )
            if match1:
                pthread_threads.append(int(match1.group(1)))
            elif match2:
                thread = int(match2.group(1))
                if thread > 1:
                    system_threads.append(thread)
            elif match3:
                barrier_threadset.append((int(match3.group(1)),int(match3.group(2))))
        assert(len(pthread_threads) == len(system_threads))

        #Print output
        outputfile = "sigil.pthread.out"
        f = open(outputfile,'w')
        for i in range(len(pthread_threads)) :
            f.write("##"+str(pthread_threads[i])+","+str(system_threads[i])+"\n") #Print a csv
        #Barrier stuff
        temp_list = []
        for tup in barrier_threadset :
            #First make the list of threads for each barrier
            f.write("**"+str(tup[0])+",")
            temp_list[:] = []
	    #print tup[1]
            for i in range(64) :
                if (tup[1] >> i) & 1 :
		    #print i, tup[1] >> i
                    temp_list.append(i)
                    f.write(str(i+1)+",")
            f.write("\n")
main()
