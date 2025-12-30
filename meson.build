project(
  'rofi-xdph',
  'cpp',
  version: '0.0.1',
  default_options: ['warning_level=3'],
  license: 'MIT',
)

# select either qt6 or qt5
qtdep = dependency('qt6', 'qt5', modules: ['Widgets'])
qtver = qtdep.version()
qt = import('qt' + qtver[0])

hyprutils_dep = dependency('hyprutils')

sources = files([
  'src/locale.cpp',
  'src/locale.h',
  'src/main.cpp',
  'src/windows.cpp',
  'src/windows.h',
])

executable('rofi-xdph',
  sources,
  dependencies: [qtdep, hyprutils_dep],
  install: true
)
