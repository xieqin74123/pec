/**
 * @dir sup_source
 * @file py_embed_compiler.cpp
 * 
 * @brief This file contains the implementation of embedding python file into binary when compiling.
 *        this file will be compiled as a separate programme and run during compiling.
 *        this separated programme will not be neccessary in the final binary.
 * 
 * @version prealpha
 * @date 2024-08-15 16:49
 * @author Qin Xie
 * 
 * @note created by Qin Xie on 2024-06-10
*/

#include <iostream>
#include <fstream>

/**
 * @brief This function is used to embed python file into cpp function when compiling.
 * 
 * @param argc The number of arguments.
 * @param argv The arguments. in list [source_file: py file to read-in before compile, 
 *                                     target_file: cpp file to write before compile, 
 *                                     target_function_name: function name defined in cpp file,
 *                                     write_target_name: the output python file name that the cpp function will write to.]
 * 
 * @return The status of the program.
*/
int main (const int argc, const char* argv[]) {
    std::ifstream source_file(argv[1]);
    std::ofstream target_file(argv[2]);
    std::string target_function_name = argv[3];
    std::string write_target_name = argv[4];

    // check pointer
    if (!source_file.is_open()) {
        std::cerr << "Error in PEC: cannot open source file." << std::endl;
        return 1;
    }
    if (!target_file.is_open()) {
        std::cerr << "Error in PEC: cannot open target file." << std::endl;
        return 1;
    }

    // write the header of the target file
    target_file << "#include <fstream>\n";
    target_file << "#include <iostream>\n";
    target_file << "#ifndef PEC_" << target_function_name << "_HPP_\n";
    target_file << "#define PEC_" << target_function_name << "_HPP_\n";
    target_file << "inline int " << target_function_name << "() {\n";
    target_file << "std::ofstream write_target;\n";
    target_file << "write_target.open(\"" << write_target_name << "\");\n";
    target_file << "if (!write_target.is_open()) {\n";
    target_file << "throw std::runtime_error(\"Error in PEC function \\\"" << target_function_name 
        << "\\\": cannot open file\\\"" << write_target_name << "\\\".\");\n";
    target_file << "}\n";
    // write the content of the source file
    for (std::string line; std::getline(source_file, line);) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '\"') {
                line.insert(i, "\\");
                i++;
            }
            else if (line[i] == '\\') {
                line.insert(i, "\\");
                i++;
            }
        }
        target_file << "write_target << \"" << line << "\" << std::endl;\n";
    }
    // write the end of the target file
    target_file << "write_target.close();\n";
    target_file << "return 0;\n";
    target_file << "}\n";
    target_file << "#endif\n";

    // close file
    source_file.close();
    target_file.close();

    return 0;
}