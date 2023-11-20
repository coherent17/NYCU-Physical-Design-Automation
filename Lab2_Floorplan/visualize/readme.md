# floorplan visualize

## Package
*   Make sure that argparse & matplotlib are installed
```bash=
$ pyinstaller --onefile floorplan_visualize.py
```

## Usage
```bash=
$ ./floorplan_visualize -i [input_filename] -o [output_filename] -p [image filename] [-d]

A script that processes input files & output files and generates a floorplan
image.

optional arguments:
  -h, --help            show this help message and exit
  -i INPUT, --input INPUT
                        Input file path
  -o OUTPUT, --output OUTPUT
                        Output file path
  -p IMAGES, --images IMAGES
                        Images name
  -d, --detail          Output detailed information

```