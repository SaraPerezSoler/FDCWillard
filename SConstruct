import os

VariantDir('build', 'src', duplicate=0)

env = Environment(CC='gcc', CCFLAGS='-Wall -Wextra', CPPPATH='include', ENV={'PATH': os.environ['PATH']}, tools=['mingw'])

env.Program(target='bin/FDCWillard', source = Glob('build/*.c'))