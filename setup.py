from distutils.core import setup, Extension

chibi_module = Extension('_chibi_scheme',
                    define_macros = [('MAJOR_VERSION', '0'),
                                     ('MINOR_VERSION', '1')],
                    include_dirs = ['/Users/adam/personal/proj/scheme/chibi/pychibi/chibi-scheme-0.7/build/include'],
                    libraries = ['chibi-scheme'],
                    library_dirs = ['/Users/adam/personal/proj/scheme/chibi/pychibi/chibi-scheme-0.7/build/lib'],
                    sources = ['pychibi.c'])

setup (name = 'pychibi',
       version = '0.1',
       description = 'chibi scheme extension module',
       author = 'Adam Feuer',
       author_email = 'adam@adamfeuer.com',
       url = 'http://github.com/adamfeuer/pychibi',
       long_description = '''
chibi-scheme extension module for python
''',
       ext_modules = [chibi_module])
