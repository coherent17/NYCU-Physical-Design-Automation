#!/usr/bin/env python3
import argparse
import matplotlib.pyplot as plt
import matplotlib.patches as patches

global module_Name
global module_Width
global module_Height
global chip_width
global chip_height
global output_module_Name
global output_module_x_coordinate
global output_module_y_coordinate
global ouptut_module_Rotate

def parse_arguments():
    parser = argparse.ArgumentParser(
        description='A script that processes input files & output files and generates a floorplan image.',
        usage='%(prog)s -i Input_Name -o Output_Name -p IMAGES_Name'
    )
    # Add the argument for input file
    parser.add_argument('-i', '--input', type=str, help='Input file path', required=True)
    # Add the argument for output file
    parser.add_argument('-o', '--output', type=str, help='Output file path', required=True)
    # Add the argument for output images name
    parser.add_argument('-p', '--images', type=str, help='images name', required=True)
    # Parse the command-line arguments
    args = parser.parse_args()
    return args

def Parse_Input(filename):
    global module_Name
    global module_Width
    global module_Height

    with open(filename, 'r') as file:
        next(file)

        for line in file:
            words = line.split()
            name = str(words[0])
            width = int(words[1])
            height = int(words[2])
            print(name, width, height)
            module_Name.append(name)
            module_Width.append(width)
            module_Height.append(height)

def Parse_Output(filename):
    global chip_width
    global chip_height
    global output_module_Name
    global output_module_x_coordinate
    global output_module_y_coordinate
    global ouptut_module_Rotate

    with open(filename, 'r') as file:
        area_line = file.readline()
        area = float(area_line.split()[2])
        aspect_ratio_line = file.readline()
        aspect_ratio = float(aspect_ratio_line.split()[2])
        chip_width = int((area * aspect_ratio) ** 0.5)
        chip_height = int(area / chip_width)
        for line in file:
            words = line.split()
            output_module_Name.append(words[0])
            output_module_x_coordinate.append(int(words[1]))
            output_module_y_coordinate.append(int(words[2]))

            # check rotate
            if(len(words) == 4):
                ouptut_module_Rotate.append(True)
            else:
                ouptut_module_Rotate.append(False)

def Plot_Floorplan(filename):
    global chip_width
    global chip_height
    global output_module_Name
    global output_module_x_coordinate
    global output_module_y_coordinate
    global ouptut_module_Rotate
    global module_Name
    global module_Width
    global module_Height

    fig, ax = plt.subplots()
    ax.set_xlabel('chip width')
    ax.set_ylabel('chip height')
    plt.rc('font', size=6)
    print(chip_width)
    print(chip_height)
    ax.plot(chip_width, chip_height, 'r*', markersize=1)
    plt.text(chip_width, chip_height, '({}, {})'.format(chip_width, chip_height))
    ax.set_xlim(0, chip_width)
    ax.set_ylim(0, chip_height)

    x_list = []
    y_list = []
    for name, x, y, rotate in zip(output_module_Name, output_module_x_coordinate, output_module_y_coordinate, ouptut_module_Rotate):
        x_list.append(x)
        y_list.append(y)
        w = 0
        h = 0
        for index, m_name in enumerate(output_module_Name):
            print(m_name, name)
            if name == m_name:
                w = module_Width[index]
                h = module_Height[index]
                if rotate:
                    w = module_Height[index]
                    h = module_Width[index]
                break
        print(x, y, w, h)
        cx = x + w / 2.0
        cy = y + h / 2.0
        rect = patches.Rectangle((x, y), w, h, edgecolor='black', fill=True)
        tag = str(name) + '\n' + str(w) + ', ' + str(h)
        ax.annotate(tag, (cx, cy), color='white', ha='center', va='center')
        ax.add_patch(rect)

    ax.plot(x_list, y_list, 'r*')
    for x, y in zip(x_list, y_list):
        plt.text(x, y, '({}, {})'.format(x, y))

    plt.savefig(filename)
    print('finish floorplan visualizer' + filename)

if __name__ == '__main__':
    # Parse command-line arguments
    args = parse_arguments()

    # Access the values using the attributes of the args object
    input_filename = args.input
    output_filename = args.output
    images_name = args.images

    # Initialize global variables
    module_Name = []
    module_Width = []
    module_Height = []
    chip_width = 0
    chip_height = 0
    output_module_Name = []
    output_module_x_coordinate = []
    output_module_y_coordinate = []
    ouptut_module_Rotate = []

    Parse_Input(input_filename)
    Parse_Output(output_filename)
    Plot_Floorplan(images_name)
