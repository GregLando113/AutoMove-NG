# coding: utf-8
from glob import glob

print('set(SOURCES')
for v in glob('src/**/*.cpp', recursive=True):
    print('\t',v.replace('\\','/'))
print(')') 
print('set(HEADERS')
for v in glob('src/**/*.h', recursive=True):
    print('\t',v.replace('\\','/'))
print(')')
