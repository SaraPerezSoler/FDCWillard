import os

VariantDir('obj', 'src', duplicate=0)

env = Environment(CC='gcc', CCFLAGS='-Wall', ENV={'PATH': os.environ['PATH']}, tools=['mingw'])

env.Program(target='bin/FDCWillard', source = Glob('obj/*.c'))