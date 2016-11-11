import argparse
from os import path, makedirs
import re


def patch_init_name(src, module_path):
    current_name = module_path[-1]
    new_name = '__'.join(module_path)
    dst = re.sub(
        r'(PyMODINIT_FUNC (?:init|PyInit_))' + re.escape(current_name),
        '\\1' + re.escape(new_name),
        src,
    )
    return dst


def patch_module_name(src, module_path):
    current_name = module_path[-1]
    new_name = '.'.join(module_path)
    dst = re.sub(
        r'(__pyx_moduledef.*?"){}"'.format(re.escape(current_name)),
        '\\1{}"'.format(new_name),
        src,
        flags=re.DOTALL,
    )
    dst = re.sub(
        r'(Py_InitModule4\("){}"'.format(re.escape(current_name)),
        '\\1{}"'.format(new_name),
        dst,
    )
    return dst


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('src')
    parser.add_argument('dst')
    parser.add_argument('--start-depth', type=int, default=0)
    args = parser.parse_args()

    src_filename = path.normpath(args.src)
    dst_filename = path.normpath(args.dst)

    module_name = path.splitext(src_filename)[0]
    module_path = module_name.split(path.sep)[args.start_depth:]
    module_name = '.'.join(module_path)

    with open(src_filename) as stream:
        src = stream.read()

    if len(module_path) > 1:
        tmp = patch_init_name(src, module_path)
        tmp = patch_module_name(tmp, module_path)
        dst = tmp
    else:
        dst = src

    dst_dir = path.dirname(dst_filename)
    if dst_dir and not path.exists(dst_dir):
        makedirs(dst_dir)

    with open(dst_filename, 'w') as stream:
        stream.write(dst)


if __name__ == '__main__':
    main()
