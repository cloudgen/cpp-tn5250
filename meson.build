# meson.build — second build.
# Compiles the same sources as ./build.sh.
# project() version matches src/main/cpp/project.h and project.ini (1.0.0).
# The tn5250 protocol library stays 0.19.0 (config.h VERSION).

project('cpp-tn5250', 'cpp',
    version: '1.0.0',
    license: 'MIT',
    default_options: [
        'warning_level=1',
        'buildtype=debugoptimized',
        'cpp_std=c++17',
    ]
)

gtk_dep = dependency('gtk+-3.0', required: true)
ssl_dep = dependency('libssl', required: true)
crypto_dep = dependency('libcrypto', required: true)
thread_dep = dependency('threads', required: true)

inc = include_directories('.', 'lib5250', 'src/main/cpp')
common_args = ['-DSYSCONFDIR="/usr/local/etc"']

lib_files = files(
    'lib5250/buffer.cpp',
    'lib5250/conf.cpp',
    'lib5250/dbuffer.cpp',
    'lib5250/debug.cpp',
    'lib5250/display.cpp',
    'lib5250/field.cpp',
    'lib5250/macro.cpp',
    'lib5250/menu.cpp',
    'lib5250/printsession.cpp',
    'lib5250/record.cpp',
    'lib5250/scrollbar.cpp',
    'lib5250/scs.cpp',
    'lib5250/session.cpp',
    'lib5250/sslstream.cpp',
    'lib5250/stream.cpp',
    'lib5250/telnetstr.cpp',
    'lib5250/terminal.cpp',
    'lib5250/utility.cpp',
    'lib5250/version.cpp',
    'lib5250/window.cpp',
    'lib5250/wtd.cpp',
)

app_files = files(
    'src/main/cpp/main.cpp',
    'src/main/cpp/logger.cpp',
    'src/main/cpp/gtkterm.cpp',
    'src/main/cpp/gnome_app.cpp',
)

lib5250 = static_library('5250',
    sources: lib_files,
    include_directories: inc,
    cpp_args: common_args,
    dependencies: [ssl_dep, crypto_dep],
)

executable('cpp-tn5250',
    sources: app_files,
    include_directories: inc,
    cpp_args: common_args + ['-Wextra', '-Werror'],
    dependencies: [
        gtk_dep,
        ssl_dep,
        crypto_dep,
        thread_dep,
    ],
    link_with: lib5250,
    install: true,
    install_dir: get_option('bindir')
)
