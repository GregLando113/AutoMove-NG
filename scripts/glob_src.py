# coding: utf-8
from glob import glob

def mk_src_cmake_string(
        source_glob='src/**/*.cpp',
        header_glob='src/**/*.h'
):
    out = ''
    out += 'set(SOURCES\n'
    for v in glob(source_glob, recursive=True):
        out += '\t' + v.replace('\\','/') + '\n'
    out += ')\n\n' 
    out += 'set(HEADERS\n'
    for v in glob(header_glob, recursive=True):
        out += '\t' + v.replace('\\','/') + '\n'
    out += ')\n'
    return out

def replace_cmakelists_source_section(replacement, file='CMakeLists.txt', outfile=None):
    start_marker = '### BEGIN SOURCE FILES ###\n'
    end_marker   = '### END SOURCE FILES ###\n'
    contents : list[str] = None
    if outfile is None:
        outfile = file
    
    with open(file, 'r') as fdr:
        contents = fdr.readlines()
    try:
        start_idx = contents.index(start_marker)
        idx = start_idx+1
        while contents[idx] != end_marker:
            del contents[idx]
        contents.insert(start_idx+1, replacement)
    except ValueError:
        raise RuntimeError(f'"{start_marker}" not found in file')
    except IndexError:
        raise RuntimeError(f'"{end_marker}" not found in file')
    
    with open(outfile, 'w') as fdw:
        fdw.write(''.join(contents))

if __name__ == '__main__':
    replace_cmakelists_source_section(mk_src_cmake_string())