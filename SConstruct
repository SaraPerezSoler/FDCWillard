import os

VariantDir('build', 'src', duplicate=0)

env = Environment(CC='gcc', CCFLAGS='-Wall -Wextra -std=gnu11', 
                  CPPPATH='include', ENV={'PATH': os.environ['PATH']}, tools=['mingw'],
                  CPPDEFINES=['__USE_MINGW_ANSI_STDIO'])

env.Program(target='bin/FDCWillard', source = Glob('build/*.c'))