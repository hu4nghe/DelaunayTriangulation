from ctypes import *
from pathlib import Path
import os

def open_dll(name='delaunay.dll'):
    lib_path = Path().absolute().parent
    lib_path = lib_path / 'delaunay' / name
    return CDLL(lib_path.as_posix())

if __name__ == '__main__':
    c_lib = open_dll()

    c_lib.delaunay()

os.system('delaunay.geo')