#!/bin/bash

echo -e "\n#####################################################"
echo -e "#################### Sigil Setup ####################"
echo -e "#####################################################\n"

sigil_path=$(readlink -m ..)

lineheader=">>>>>"
valgrind="valgrind-3.10.1"
if [[ ! $(ls $sigil_path | grep $valgrind) ]]
then
	echo "$lineheader Could not find '$valgrind'!"
	read -p "$lineheader Specify sigil directory [$sigil_path]:"
	sigil_path=$(readlink -m $REPLY)
fi

if [[ ! $(ls $sigil_path 2>/dev/null | grep $valgrind) ]]
then
	echo "$lineheader Could not find Sigil directory ..."
	echo "$lineheader Aborting!"
	exit 1
fi

####################################
# Build valgrind 3.10.1 with sigil #
####################################
cd $sigil_path/$valgrind
./autogen.sh && ./configure && make -j6 --quiet
if ! [[ $? == 0 ]]
then
	echo "$lineheader ERROR| Sigil build failed!"
	exit 1
fi
echo "$lineheader Sigil build complete!"

################################
# Modify run script paths #
################################
echo "$lineheader Modifying Sigil run script paths"
runscript_path="$sigil_path/runsigil_and_gz.py"

cd $sigil_path

runscript_blank="vg_in_place = \"\""
runscript_vg="vg_in_place = \"$sigil_path/$valgrind/vg-in-place\""

sed -i "s|$runscript_blank|$runscript_vg|" $runscript_path

echo "$lineheader Sigil setup complete"

#########################
#  Example using sigil  #
#########################
#read -p "$lineheader Would you like to run the example tests? [Y/n]:" 
#if ! [[ "$REPLY" == "" || $(echo $REPLY | grep -i "^y$\|^yes$") ]]
#then
#	echo "$lineheader All done!"
#	exit 0
#fi
#
#echo "$lineheader Running example..."
#
#exe_file_path="$sigil_path/examples"
#g++ $exe_file_path/sigil_test.c -o $exe_file_path/sigil_test
#
#$sigil_path/$valgrind/vg-in-place --tool=callgrind --sigil-tool=yes --separate-callers=100 --cache-sim=yes --drw-func=yes $exe_file_path/sigil_test #--drw-events=yes,
#$sigil_path/$valgrind/vg-in-place --tool=callgrind --cache-sim=yes --branch-sim=yes --callgrind-out-file=callgrind_out $exe_file_path/sigil_test
#$sigil_path/postprocessing/aggregate_costs_gran.py sigil.totals.out-1 --trim-tree --cgfile=callgrind_out --gran-mode=metric > $exe_file_path/postprocessing_result_math
#
#echo "$lineheader Finished running example! Check $exe_file_path"
