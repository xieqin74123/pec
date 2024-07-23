# pec
python code embedder for C++.  
This programme can read in python file and write out as a function in hpp file for other code to save python code in binary.

# license
This programme distributes under MIT license

# compilation
g++ -o pec *.cpp

# usage
./pec <source_file> <target_file> <target_function_name> <write_target_name>  
 - source_file: python file to be read-in
 - target_file: the output cpp/hpp file
 - target_function_name: the function name define in "target_file" to write the python code
 - write_target_name: the name of python file that "target_function_name" will output

**This programme should be compiled before the main code and run in makefile to generate cpp/hpp that preferred
