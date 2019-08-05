"""
This script convert all images in assets folder to hex format that can be read
by display script
"""
import os
import math
import sys
import glob
from PIL import Image

ASSETS_DIR = \
    os.path.abspath(os.path.join(os.path.basename(__file__), '..', 'assets'))


def image_to_bytearray(im):
    # the output data
    outdata = bytearray()
    
    w = 8 * math.ceil(im.width / 8)
    h = im.height

    # first byte width
    outdata.append(im.width & 0xFF)
    # second byte height
    outdata.append(h & 0xFF)
    # third byte stride
    outdata.append(w & 0xFF)

    # extract bytes from content
    next_byte = 0x0
    
    for y in range(0, h):
        for x in range(0, w):
            value = True if x >= im.width else im.getpixel((x, y))
            # uncomment this line to see some pixel art
            # sys.stdout.write("0" if value else "1")
            next_byte = (next_byte << 1) | (not bool(value))
            if (x + 1) % 8 == 0:
                outdata.append(next_byte)
                next_byte = 0x0
    return outdata

for image_path in glob.iglob(os.path.join(ASSETS_DIR, "*.png")):
    filename, file_extension = os.path.splitext(image_path)
    target_filename = os.path.join(ASSETS_DIR, "{}.bin".format(filename))
    im = Image.open(image_path)
    im = im.convert("1")
    print("Converting {}".format(image_path))
    with open(target_filename, 'wb') as f:
        f.write(image_to_bytearray(im))
    
print("Done!")


        