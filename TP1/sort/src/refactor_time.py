import re

with open('sort_unified.c', 'r') as f:
    content = f.read()

# Add get_wall_time function after includes
content = re.sub(
    r'(#include <pthread\.h>\n)',
    r'\1\ndouble get_wall_time() {\n    struct timespec time;\n    clock_gettime(CLOCK_MONOTONIC, &time);\n    return (double)time.tv_sec + (double)time.tv_nsec * 1e-9;\n}\n',
    content
)

# Replace clock_t start_xyz = clock(); with double start_xyz = get_wall_time();
content = re.sub(r'clock_t\s+(start_[a-zA-Z0-9_]+)\s*=\s*clock\(\);', r'double \1 = get_wall_time();', content)
content = re.sub(r'clock_t\s+(end_[a-zA-Z0-9_]+)\s*=\s*clock\(\);', r'double \1 = get_wall_time();', content)

# Replace exec_times_xyz[i] = (double)(end - start) / CLOCKS_PER_SEC; with exec_times_xyz[i] = end - start;
content = re.sub(r'=\s*\(double\)\s*\((end_[a-zA-Z0-9_]+)\s*-\s*(start_[a-zA-Z0-9_]+)\)\s*/\s*CLOCKS_PER_SEC;', r'= \1 - \2;', content)

with open('sort_unified.c', 'w') as f:
    f.write(content)
