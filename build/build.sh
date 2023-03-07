#! /bin/bash

#? BUILD FOR X86 - g++
project_dir=".."
sources_dir="$project_dir/src"
include_dir="$project_dir/include/"
#library_home="/usr/local/lib"
bin_output_dir="$project_dir/bin"
bin_output="${bin_output_dir}/nn" 

export CPLUS_INCLUDE_PATH="${include_dir}:${project_dir}/lib/eigen-3.4.0/Eigen/..:${include_dir}:${project_dir}/lib/curlpp-0.8.1/include/curlpp/.."
printenv CPLUS_INCLUDE_PATH

#Load all .c files into sourceFiles variable
sourceFiles=("")
index=0
for file in "$sources_dir"/*.cpp
do
  sourceFiles[$index]=${file}
  ((index=index+1))
done

#?Debuggin version
echo g++ -Wall -g -o "${bin_output}_dbg.bin" "${sourceFiles[@]}"
     g++ -Wall -g -o "${bin_output}_dbg.bin" "${sourceFiles[@]}" && \
echo "X86_Linux: Debuggin version copilled successful"
echo "------------------------------------------------"

#?Profilling version 
#echo g++ -Wall -pg -o "${bin_output}_prof.bin" "${sourceFiles[@]}"
#     g++ -Wall -pg -o "${bin_output}_prof.bin" "${sourceFiles[@]}" && \
#echo "X86_Linux: Profilling version copilled successful"
#echo "------------------------------------------------"
#
##?Production version - DO NOT DEFINE NDEBUG TO KEEP ASSERTS()
#echo g++ -D QUIET_OUTPUT -Wall -o "${bin_output}.bin" "${sourceFiles[@]}"
#     g++ -D QUIET_OUTPUT -Wall -o "${bin_output}.bin" "${sourceFiles[@]}" && \
#echo "X86_Linux: Production version copilled successful"
#echo "------------------------------------------------"