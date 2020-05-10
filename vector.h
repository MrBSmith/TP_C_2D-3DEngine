#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

typedef struct vector2{
    float x;
    float y;
} vector2;

vector2 linear_interpolate(vector2 in_vec, vector2 dest_vec, float weight);
vector2 sum_vectors(vector2 v1, vector2 v2);

#endif // VECTOR_H_INCLUDED
