#include <stdio.h>
#include "triangle.c"


int main(void) {

    struct Vertex s1, s2, s3;
    s1.x = 0;
    s1.y = 0;
    s2.x = 1;
    s2.y = 0;
    s3.x = 0;
    s3.y = 1;

    struct Vertex vert[3];
    vert[0] = s1;
    vert[1] = s2;
    vert[2] = s3;

    struct Triangle tri1;
    tri1.v1 = 0;
    tri1.v2 = 1;
    tri1.v3 = 2;

    struct Triangle tri[1];
    triangle[0] = tri1;

    struct Mesh2D *test_mesh;
    initialize_mesh2D(test_mesh, 3, 1);
    
    test_mesh->vert = vert;
    test_mesh->tri = tri;

    double area = 0;
    area = area_mesh2D(m);
    printf("Triangle Area = %d\n", area);

   return 0;
}
