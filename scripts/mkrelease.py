import zipfile
import argparse
import os

parser = argparse.ArgumentParser(prog='mkrelease',description='Utility to make a release zipfile')


parser.add_argument('-v', '--version', required=True)
parser.add_argument('-f', '--file', required=True)
parser.add_argument('-n', '--name', required=True)
parser.add_argument('-o', '--outfilename', required=True)

args = parser.parse_args()
distfile = os.path.abspath(os.path.join('dist', f'{args.name}.{args.version}.zip'))

print(f'Making release distribution:\n\t{args.version=}\n\t{args.file=}\n\t{distfile=}\n\t{args.outfilename=}')
try:
    os.mkdir('dist')
except FileExistsError:
    pass
with zipfile.ZipFile(distfile,'w') as zip:
    zip.write(os.path.abspath(args.file),f'SKSE/Plugins/{args.outfilename}.dll')