#include "vector.h"

vector2 linear_interpolate(vector2 in_vec, vector2 dest_vec, float weight){
    vector2 out_vec;
    out_vec.x = in_vec.x * (1.0 - weight) + dest_vec.x * weight;
    out_vec.y = in_vec.y * (1.0 - weight) + dest_vec.y * weight;
    return out_vec;
}

vector2 sum_vectors(vector2 v1, vector2 v2){
    vector2 result_v;

    result_v.x = v1.x + v2.x;
    result_v.y = v1.y + v2.y;

    return result_v;
}
