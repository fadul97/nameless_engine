#ifndef C_MATH_H
#define C_MATH_H

#include "defines.h"

/*
    Resources: 
        Kohi Game Engine by Travis Vroman
            https://github.com/travisvroman/kohi
*/

// #include <intrin.h>
#include <x86intrin.h>

#include <math.h>
#include <stdio.h>

/* Math Types */


// Vec2 structure
typedef union Vec2_u
{
    f32 elements[2];
    struct
    {
        union
        {
            f32 x, s, u; 
        };
        union
        {
            f32 y, t, v;
        };
    };
} Vec2;

// Vec3 structure
typedef union Vec3_u
{
    f32 elements[3];
    struct
    {
        union
        {
            f32 x, r, s, u; 
        };
        union
        {
            f32 y, g, t, v;
        };
        union
        {
            f32 z, b, p, w;
        };
    };
} Vec3;

// Vec4 structure
typedef union Vec4_u
{
    f32 elements[4];
    struct
    {
        union
        {
            f32 x, r, s; 
        };
        union
        {
            f32 y, g, t;
        };
        union
        {
            f32 z, b, p;
        };
        union
        {
            f32 w, a, q;
        };
    };
} Vec4;

// Mat4 structure
typedef struct Mat4 {
	union {
		__m256 chunk[2];
		__m128 column[4];
		Vec4 column_vector[4];
		f32 data[16];
        f32 m[4][4];
	};
} Mat4;


/* Vector 2 */

// Return Vec2 created
INLINE Vec2 vec2_create(f32 x, f32 y)
{ return (Vec2){x, y}; }

// Return Vec2(0.0f, 0.0f)
INLINE Vec2 Vec2_zero()
{ return (Vec2){0.0f, 0.0f}; }

// Return Vec2(1.0f, 1.0f)
INLINE Vec2 Vec2_one()
{ return (Vec2){1.0f, 1.0f}; }

// Return Vec2(0.0f, 1.0f)
INLINE Vec2 Vec2_up()
{ return (Vec2){0.0f, 1.0f}; }

// Return Vec2(0.0f, -1.0f)
INLINE Vec2 Vec2_down()
{ return (Vec2){0.0f, -1.0f}; }

// Return Vec2(1.0f, 0.0f)
INLINE Vec2 Vec2_right()
{ return (Vec2){1.0f, 0.0f}; }

// Return Vec2(-1.0f, 0.0f)
INLINE Vec2 Vec2_left()
{ return (Vec2){-1.0f, 0.0f}; }

/* Vector 3 */

// Return Vec3 created
INLINE Vec3 vec3_create(f32 x, f32 y, f32 z)
{ return (Vec3){x, y, z}; }

// Return Vec3(0.0f, 0.0f, 0.0f)
INLINE Vec3 vec3_zero()
{ return (Vec3){0.0f, 0.0f, 0.0f}; }

// Return Vec3(1.0f, 1.0f)
INLINE Vec3 vec3_one()
{ return (Vec3){1.0f, 1.0f}; }

// Return Vec3(0.0f, 1.0f, 0.0f)
INLINE Vec3 vec3_up()
{ return (Vec3){0.0f, 1.0f, 0.0f}; }

// Return Vec3(0.0f, -1.0f, 0.0f)
INLINE Vec3 vec3_down()
{ return (Vec3){0.0f, -1.0f, 0.0f}; }

// Return Vec3(1.0f, 0.0f, 0.0f)
INLINE Vec3 vec3_right()
{ return (Vec3){1.0f, 0.0f, 0.0f}; }

// Return Vec3(-1.0f, 0.0f, 0.0f)
INLINE Vec3 vec3_left()
{ return (Vec3){-1.0f, 0.0f, 0.0f}; }

// Return Vec3(0.0f, 0.0f, -1.0f)
INLINE Vec3 vec3_forward()
{ return (Vec3){0.0f, 0.0f, -1.0f}; }

// Return Vec3(0.0f, 0.0f, 1.0f)
INLINE Vec3 vec3_back()
{ return (Vec3){0.0f, 0.0f, 1.0f}; }

// Return 'new' Vec3 b added to a
INLINE Vec3 vec3_add(Vec3 a, Vec3 b)
{ return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z}; }

// Add Vec3 a and b
INLINE void vec3v_add(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    v->x += b.x;
    v->y += b.y;
    v->z += b.z;
}

// Return 'new' Vec3 a subtracted by b
INLINE Vec3 vec3_minus(Vec3 a, Vec3 b)
{ return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z}; }

// Subtract Vec3 b from a
INLINE void vec3v_minus(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    v->x -= b.x;
    v->y -= b.y;
    v->z -= b.z;
}

// Return 'new' Vec3 a multiplied by b
INLINE Vec3 vec3_multiply(Vec3 a, Vec3 b)
{ return (Vec3){a.x * b.x, a.y * b.y, a.z * b.z}; }

// Multiply Vec3 a and b
INLINE void vec3v_multiply(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    v->x *= b.x;
    v->y *= b.y;
    v->z *= b.z;
}

// Return 'new' Vec3 a divided by b
INLINE Vec3 vec3_divide(Vec3 a, Vec3 b)
{ return (Vec3){a.x / b.x, a.y / b.y, a.z / b.z}; }

// Divide Vec3 a by b
INLINE void vec3v_divide(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    v->x /= b.x;
    v->y /= b.y;
    v->z /= b.z;
}

// Return Vec3 a multiplied by scalar k
INLINE Vec3 vec3_multiply_by_scalar(Vec3 a, f32 k)
{ return (Vec3){a.x * k, a.y * k, a.z * k}; }

// Multiply Vec3 a by scalar k
INLINE void vec3v_multiply_by_scalar(Vec3 a, f32 k)
{
    Vec3 *v = &a;
    v->x *= k;
    v->y *= k;
    v->z *= k;
}

// Return Vec3 a divided by scalar k
INLINE Vec3 vec3_divide_by_scalar(Vec3 a, f32 k)
{ return (Vec3){a.x / k, a.y / k, a.z / k}; }

// Divide Vec3 a by scalar k
INLINE void vec3v_divide_by_scalar(Vec3 a, f32 k)
{
    Vec3 *v = &a;
    v->x /= k;
    v->y /= k;
    v->z /= k;
}

INLINE Vec3 vec3_mul_mat4(Vec3 v, Mat4 m) {
    return (Vec3){
        v.x * m.data[0] + v.y * m.data[4] + v.z * m.data[8] + m.data[12],
        v.x * m.data[1] + v.y * m.data[5] + v.z * m.data[9] + m.data[13],
        v.x * m.data[2] + v.y * m.data[6] + v.z * m.data[10] + m.data[14]};
}

// Return Vec3 a magnitude/length
INLINE d64 vec3_length(Vec3 a)
{ return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z)); }

// Return squared length of Vec3 a
INLINE d64 vec3_length_squared(Vec3 a)
{ return (a.x * a.x) + (a.y * a.y) + (a.z * a.z); }

// Return normalized Vec3 a
INLINE Vec3 vec3_normalize(Vec3 a)
{ return vec3_divide_by_scalar(a, (f32)vec3_length(a)); }

// Normalize Vec3 a
INLINE void vec3v_normalize(Vec3 a)
{ vec3v_divide_by_scalar(a, (f32)vec3_length(a)); }

// Return dot product of a and b
INLINE d64 vec3_dot_product(Vec3 a, Vec3 b)
{ return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }

// Return cross product of Vec3 a and b
INLINE Vec3 vec3_cross_product(Vec3 a, Vec3 b)
{ return (Vec3){a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x};
}

// Caculate cross product of Vec3 a and b in Vec3 a
INLINE void vec3v_cross_product(Vec3 a, Vec3 b)
{
    Vec3 *v = &a;
    float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;
	v->x = x;
	v->y = y;
	v->z = z;
}

INLINE Vec3 vec3_from_vec4(Vec4 a)
{ return (Vec3){a.x, a.y, a.z}; }

// Return distance between Vec a and b
INLINE d64 vec3_distance(Vec3 a, Vec3 b)
{ return vec3_length(vec3_create(a.x - b.x, a.y - b.y, a.z - b.z)); }

// Return if Vec3 a and b are equal
INLINE b8 vec3_is_equal(Vec3 a, Vec3 b)
{ return (a.x == b.x) && (a.y == a.y) && (a.z == b.z); }

// Print Vec3: (x, y);
INLINE void vec3_print(Vec3 a)
{ printf("(%f, %f, %f)", a.x, a.y, a.z); }

// FIXME: Check calculations, make it similar to mat4_mult_vec4
INLINE Vec3 mat4_mult_vec3(Mat4 a, Vec3 b)
{
    Vec3 v;

    // printf("%.2f*%.2f + %.2f*%.2f + %.2f*%.2f + %.2f*%.2f\n",
        // a.data[0] , b.x , a.data[1] , b.y , a.data[2] , b.z , a.data[3] , b.w);
    v.x = a.data[0] * b.x + a.data[4] * b.y + a.data[8]  * b.z + a.data[12];
    v.y = a.data[1] * b.x + a.data[5] * b.y + a.data[9]  * b.z + a.data[13];
    v.z = a.data[2] * b.x + a.data[6] * b.y + a.data[10] * b.z + a.data[14];

    f32 w = a.data[3] * b.x + a.data[7] * b.y + a.data[11] * b.z + a.data[15];

    if(w != 0.0f)
        v = vec3_divide_by_scalar(v, w);

    return v;

    /*
    Vec3 v;

    // printf("%.2f*%.2f + %.2f*%.2f + %.2f*%.2f + %.2f*%.2f\n",
        // a.data[0] , b.x , a.data[1] , b.y , a.data[2] , b.z , a.data[3] , b.w);
    v.x = b.x * a.m[0][0] + b.y * a.m[1][0] + b.z * a.m[2][0] + a.m[3][0];
    v.y = b.x * a.m[0][1] + b.y * a.m[1][1] + b.z * a.m[2][1] + a.m[3][1];
    v.z = b.x * a.m[0][2] + b.y * a.m[1][2] + b.z * a.m[2][2] + a.m[3][2];

    f32 w = b.x * a.m[0][3] + b.y * a.m[1][3] + b.z * a.m[2][3] + a.m[3][3];

    if(w != 0.0f)
        v = vec3_divide_by_scalar(v, w);

    return v;
    */
}

INLINE Vec4 mat4_mult_vec4(Mat4 a, Vec4 b)
{
    Vec4 v;

    // printf("%.2f*%.2f + %.2f*%.2f + %.2f*%.2f + %.2f*%.2f\n",
        // a.data[0] , b.x , a.data[1] , b.y , a.data[2] , b.z , a.data[3] , b.w);
    v.x = a.data[0] * b.x + a.data[1] * b.y + a.data[2] * b.z + a.data[3] * b.w;
    v.y = a.data[4] * b.x + a.data[5] * b.y + a.data[6] * b.z + a.data[7] * b.w;
    v.z = a.data[8] * b.x + a.data[9] * b.y + a.data[10] * b.z + a.data[11] * b.w;
    v.w = a.data[12] * b.x + a.data[13] * b.y + a.data[14] * b.z + a.data[15] * b.w;

    return v;
}


/* Vector 4 */

INLINE Vec4 vec4_create(f32 x, f32 y, f32 z, f32 w)
{ return (Vec4){x, y, z, w}; }

INLINE Vec4 vec4_red()
{ return (Vec4){1.0f, 0.0f, 0.0f, 1.0f}; }

INLINE Vec4 vec4_green()
{ return (Vec4){0.0f, 1.0f, 0.0f, 1.0f}; }

INLINE Vec4 vec4_blue()
{ return (Vec4){0.0f, 0.0f, 1.0f, 1.0f}; }

// Return 'new' Vec4 b added to a
INLINE Vec4 vec4_add(Vec4 a, Vec4 b)
{ return (Vec4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }

// Return Vec4 a divided by scalar k
INLINE Vec4 vec4_divide_by_scalar(Vec4 a, f32 k)
{ return (Vec4){a.x / k, a.y / k, a.z / k, a.w / k}; }

// Return Vec4 a magnitude/length
INLINE d64 vec4_length(Vec4 a)
{ return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z) + (a.w * a.w)); }

// Return 'new' Vec4 a subtracted by b
INLINE Vec4 vec4_minus(Vec4 a, Vec4 b)
{ return (Vec4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }

// Subtract Vec4 b from a
INLINE void vec4v_minus(Vec4 a, Vec4 b)
{
    Vec4 *v = &a;
    v->x -= b.x;
    v->y -= b.y;
    v->z -= b.z;
    v->w -= b.w;
}

INLINE Vec4 mat4_mul_vec4(Mat4 m, Vec4 v) {
    return (Vec4){
        v.x * m.data[0] + v.y * m.data[1] + v.z * m.data[2] + v.w * m.data[3],
        v.x * m.data[4] + v.y * m.data[5] + v.z * m.data[6] + v.w * m.data[7],
        v.x * m.data[8] + v.y * m.data[9] + v.z * m.data[10] + v.w * m.data[11],
        v.x * m.data[12] + v.y * m.data[13] + v.z * m.data[14] + v.w * m.data[15]};
}

// Return normalized Vec4 a
INLINE Vec4 vec4_normalize(Vec4 a)
{ return vec4_divide_by_scalar(a, (f32)vec4_length(a)); }

INLINE Vec4 vec4_from_vec3(Vec3 a)
{ return (Vec4){a.x, a.y, a.z, 1.0f}; }

// Print Vec3: (x, y);
INLINE void vec4_print(Vec4 a)
{ printf("(%f, %f, %f, %f)", a.x, a.y, a.z, a.w); }

/* Matrix 4 */

#define LF_DEG2RAD M_PI / 180.0f

INLINE Mat4 mat4_identity()
{
    Mat4 m;
    m.column[0] = _mm_setr_ps(1, 0, 0, 0);
    m.column[1] = _mm_setr_ps(0, 1, 0, 0);
    m.column[2] = _mm_setr_ps(0, 0, 1, 0);
    m.column[3] = _mm_setr_ps(0, 0, 0, 1);
    return m;
}

INLINE Mat4 mat4_translate(Mat4 a, Vec3 b)
{
    Mat4 *v = &a;

    __m128 c = _mm_setr_ps(v->column[3][0], v->column[3][1], v->column[3][2], v->column[3][3]);
    // printf("%.2f, %.2f, %.2f, %.2f\n", v->column[3][0], v->column[3][1], v->column[3][2], v->column[3][3]);

    // v->column[0] = _mm_setr_ps(1, 0, 0, 0);
    // v->column[0] = _mm_setr_ps(1, 0, 0, 0);
    // v->column[0] = _mm_setr_ps(1, 0, 0, 0);
    v->column[3] = _mm_setr_ps(c[0]+b.x, c[1]+b.y, c[2]+b.z, 1);

    return *v;
}

INLINE f32 to_radians(f32 degree)
{
    return degree * LF_DEG2RAD;
}

INLINE Mat4 mat4_perspective(f32 fov, f32 aspect_ratio, f32 near_plane, f32 far_plane)
{
    f32 rad = fov * LF_DEG2RAD;

    f32 zoom = tan(rad * 0.5f);

    Mat4 m;
    m.column[0] = _mm_setr_ps((1.0f / zoom * aspect_ratio), 0, 0,  0);
	m.column[1] = _mm_setr_ps(0, (1.0f / zoom), 0,  0);
	m.column[2] = _mm_setr_ps(0, 0, -((far_plane+near_plane)/(far_plane-near_plane)), -1);
	m.column[3] = _mm_setr_ps(0, 0, -((2.0f*far_plane*near_plane)/(far_plane-near_plane)),  0);
    
    return m;
}

INLINE Mat4 look_at(Vec3 position, Vec3 target, Vec3 up)
{
    Vec3 forward = vec3_normalize(vec3_minus(target, position));
    Vec3 right = vec3_normalize(vec3_cross_product(forward, up));
    up = vec3_normalize(vec3_cross_product(right, forward));

    // Since I'm not multiplying Vec3 forward by -1, I need to invert its values
    // when passing to the matrix
    Mat4 m;
    m.column[0] = _mm_setr_ps(right.x, up.x, -forward.x, 0);
    m.column[1] = _mm_setr_ps(right.y, up.y, -forward.y, 0);
    m.column[2] = _mm_setr_ps(right.z, up.z, -forward.z, 0);
    m.column[3] = _mm_setr_ps(-vec3_dot_product(right, position), 
        -vec3_dot_product(up, position), vec3_dot_product(forward, position), 1);

    return m;
}

// TODO: Test projection
INLINE Mat4 mat4_orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near_plane, f32 far_plane)
{
    Mat4 m;

    // f32 lr = 1.0f / (left - right);
    // f32 bt = 1.0f / (bottom - top);
    // f32 nf = 1.0f / (near_plane - far_plane);

    /* KOHI */
    f32 lr = 1.0f / (left - right);
    f32 bt = 1.0f / (bottom - top);
    f32 nf = 1.0f / (near_plane - far_plane);

    m.column[0] = _mm_setr_ps(-2.0f * lr, 0, 0, 0);
    m.column[1] = _mm_setr_ps(0, -2.0f * bt, 0, 0);
    m.column[2] = _mm_setr_ps(0, 0, 2.0f * nf, 0);
    m.column[3] = _mm_setr_ps((left + right) * lr, (top + bottom) * bt, (far_plane + near_plane) * nf, 1);
    
    return m;
}

INLINE Mat4 mat4_scale(Mat4 a, Vec3 b)
{
    Mat4 m = a;

    m.column[0][0] = a.column[0][0] * b.x;
    m.column[1][1] = a.column[1][1] * b.y;
    m.column[2][2] = a.column[2][2] * b.z;

    return m;
}

INLINE Mat4 mat4_translation(Vec3 v)
{
    Mat4 o = mat4_identity();

    o.data[12] = v.x;
    o.data[13] = v.y;
    o.data[14] = v.z;

    return o;
}

INLINE Mat4 mat4_euler_x(f32 angle_radians) {
    Mat4 o = mat4_identity();
    f32 c = cosf(angle_radians);
    f32 s = sinf(angle_radians);

    o.data[5] = c;
    o.data[6] = s;
    o.data[9] = -s;
    o.data[10] = c;

    return o;
}

INLINE Mat4 mat4_euler_y(f32 angle_radians) {
    Mat4 o = mat4_identity();
    f32 c = cosf(angle_radians);
    f32 s = sinf(angle_radians);

    o.data[0] = c;
    o.data[2] = -s;
    o.data[8] = s;
    o.data[10] = c;
    
    return o;
}

INLINE Mat4 mat4_euler_z(f32 angle_radians) {
    Mat4 o = mat4_identity();

    f32 c = cosf(angle_radians);
    f32 s = sinf(angle_radians);

    o.data[0] = c;
    o.data[1] = s;
    o.data[4] = -s;
    o.data[5] = c;

    return o;
}

INLINE Mat4 mat4_mul(Mat4 a, Mat4 b) {
    Mat4 o = mat4_identity();

    const f32 *m1_ptr = a.data;
    const f32 *m2_ptr = b.data;
    f32 *dst_ptr = o.data;

    for (i32 i = 0; i < 4; ++i) {
        for (i32 j = 0; j < 4; ++j) {
            *dst_ptr = m1_ptr[0] * m2_ptr[0 + j] + m1_ptr[1] * m2_ptr[4 + j] +
                       m1_ptr[2] * m2_ptr[8 + j] + m1_ptr[3] * m2_ptr[12 + j];
            dst_ptr++;
        }
        m1_ptr += 4;
    }

    return o;
}

INLINE void mat4_print(Mat4 m)
{
    f32 c0[4] = {m.column[0][0], m.column[0][1], m.column[0][2], m.column[0][3]};
    f32 c1[4] = {m.column[1][0], m.column[1][1], m.column[1][2], m.column[1][3]};
    f32 c2[4] = {m.column[2][0], m.column[2][1], m.column[2][2], m.column[2][3]};
    f32 c3[4] = {m.column[3][0], m.column[3][1], m.column[3][2], m.column[3][3]};
    
    printf("(");
    for(int i = 0; i < 4; i++)
        printf("%.2f ", c0[i]);
    printf(")\n");

    printf("(");
    for(int i = 0; i < 4; i++)
        printf("%.2f ", c1[i]);
    printf(")\n");
        
    printf("(");
    for(int i = 0; i < 4; i++)
        printf("%.2f ", c2[i]);
    printf(")\n");

    printf("(");
    for(int i = 0; i < 4; i++)
        printf("%.2f ", c3[i]);
    printf(")\n");
}

#endif // C_MATH_H