from distutils.core import setup, Extension

rc4 = Extension('rc4', sources = ['rc4.c'])

setup (name = 'AlyShmahell-InfoSecIntro',
        version = '1.0',
        description = 'This is an introduction to information security.',
        ext_modules = [rc4])
