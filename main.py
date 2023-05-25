def replace_spaces(line):
    line = line.strip()  # Remove leading/trailing whitespaces

    if line.startswith("get_all_movies_count"):
        line = line.replace("get_all_movies_count", "get_all_movies_count_aux obj", 1)

    elif line.startswith("get_all_movies"):
        line = line.replace("get_all_movies", "get_all_movies_aux obj", 1)

    elif line.startswith("get_num_views"):
        line = line.replace("get_num_views", "get_num_views_aux obj", 1)

    elif line.startswith("get_all_movies_count"):
        line = line.replace("get_all_movies_count", "get_all_movies_count_aux obj", 1)

    elif line.startswith("add_movie"):
        line = line.replace("add_movie", "add_movie_aux obj", 1)

    else:
        line = "obj->" + line  # Add "obj->" at the beginning of the line

    line = line.replace(" ", "(", 1)  # Replace the first space with open parentheses "("
    line = line.replace(" ", ", ")  # Replace all other spaces with ", "
    line += ");"  # Add close parentheses ")" at the end

    line = line.replace("False", "false")
    line = line.replace("True", "true")

    return line


def process_file(file_path, output_file):
    with open(file_path, 'r') as input_file, open(output_file, 'w') as output_file:
        for line in input_file:
            processed_line = replace_spaces(line)
            print(processed_line, file=output_file)


if __name__ == '__main__':
    import sys

    if len(sys.argv) < 3:
        print("Please provide the path to the input file and the output file.")
        sys.exit(1)

    input_file_path = sys.argv[1]
    output_file_path = sys.argv[2]
    process_file(input_file_path, output_file_path)

