project('tinymath', 'c', version: '0.0.1', license: 'MIT')

inc = include_directories('include')

sources = []
source_files = ['tinyrand.c']
foreach source : source_files
    sources += ['src/' + source]
endforeach

tinymath = library('tinymath', sources, include_directories: inc)

# Library Dependency for tests
tinymathdep = declare_dependency(link_with: tinymath, include_directories: inc)

# Testing framework (munit)
munit = dependency('munit', fallback: ['munit', 'munit_dep'])

tests = {'testrand': 'test_tinyrand.c'}
foreach test_name, test_file : tests
    e = executable(
        test_name,
        'test/' + test_file,
        dependencies: [tinymathdep, munit],
    )
    test(test_name, e)
endforeach
