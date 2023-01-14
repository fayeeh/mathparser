project('mathparser', 'cpp', 
  version: '1.0',
  default_options : [
    'cpp_std=c++17',
    'buildtype=release',
    'optimization=2',
    'warning_level=2'
  ]
)

inc = include_directories('include')
src = files(
  'src/error.cpp',
  'src/lexer.cpp',
  'src/parser.cpp',
  'src/types.cpp',
  'src/mathparser.cpp'
)



mathparser = library(
  'mathparser', 
  src,
  install : not meson.is_subproject(),
  version : meson.project_version(),
  soversion : '0'
)

mathparser_dep = declare_dependency(
  include_directories : inc,  
  link_with : mathparser,
)

if not meson.is_subproject() 
  pkg = import('pkgconfig')
  pkg.generate(
    mathparser,
    description: 'Mathparser'
  )

  install_headers('include/mathparser/mathparser.h')
endif