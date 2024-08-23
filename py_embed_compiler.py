import sys

"""
INPUT INSTUCTIONS:
The arguments. in order [source_file: py file to read-in before compile, 
                         target_file: cpp file to write before compile, 
                         target_function_name: function name defined in cpp file,
                         write_target_name: the output python file name that the cpp function will write to.]
"""
def main(argc, argv):
    if argc != 5:
        print("Error in PEC: Incorrect number of arguments.", file=sys.stderr)
        return 1

    source_file_path = argv[1]
    target_file_path = argv[2]
    target_function_name = argv[3]
    write_target_name = argv[4]

    try:
        with open(source_file_path, 'r') as source_file, open(target_file_path, 'w') as target_file:
            # Write the header of the target file
            target_file.write('#include <fstream>\n')
            target_file.write('#include <iostream>\n')
            target_file.write('#include <string>\n')
            target_file.write('#include <filesystem>\n')
            target_file.write(f'#ifndef PEC_{target_function_name}_HPP_\n')
            target_file.write(f'#define PEC_{target_function_name}_HPP_\n')
            # function definition
            target_file.write(f'inline std::filesystem::path {target_function_name}(std::filesystem::path temp_dir = "./") {{\n')
            target_file.write('std::ofstream write_target;\n')
            target_file.write(f'std::filesystem::path output_path = temp_dir / "{write_target_name}";\n')
            target_file.write('write_target.open(output_path);\n')
            target_file.write('if (!write_target.is_open()) {\n')
            target_file.write(f'throw std::runtime_error("Error in PEC function \\"{target_function_name}\\": cannot open file\\"{write_target_name}\\".");\n')
            target_file.write('}\n')

            # Write the content of the source file
            for line in source_file:
                line = line.rstrip()  # Keeps leading spaces/tabs
                line = line.replace('\\', '\\\\').replace('"', '\\"')
                target_file.write(f'write_target << "{line}" << std::endl;\n')

            # Write the end of the target file
            target_file.write('write_target.close();\n')
            target_file.write(f'return output_path;\n')
            target_file.write('}\n')
            target_file.write('#endif\n')
    except FileNotFoundError:
        print(f"Error in PEC: cannot open source file {source_file_path} or target file {target_file_path}.", file=sys.stderr)
        return 1

    return 0

if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))

