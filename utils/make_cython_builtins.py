import argparse
from os import path, makedirs


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('sources', nargs='+')
    parser.add_argument('--start-depth', type=int, default=0)
    args = parser.parse_args()

    decls = []
    builtins = []
    for src_filename in args.sources:
        src_filename = path.normpath(src_filename)
        module_name = path.splitext(src_filename)[0]
        module_path = module_name.split(path.sep)[args.start_depth:]
        init_name = 'PyInit_{}'.format('__'.join(module_path))
        decls.append('PyMODINIT_FUNC {}(void);'.format(init_name))
        builtins.append('    {{"{}", {}}}'.format(
            '.'.join(module_path), init_name,
        ))

    builtins.append('    {NULL, NULL}')

    header = '''{}

static struct _inittab builtins[] = {{
{}
}};'''.format(
        '\n'.join(decls),
        ',\n'.join(builtins),
    )

    print(header)


if __name__ == '__main__':
    main()
