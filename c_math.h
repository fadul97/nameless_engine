#ifndef C_MATH_H
#define C_MATH_H

#include "defines.h"


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

// Return distance between Vec a and b
INLINE d64 vec3_distance(Vec3 a, Vec3 b)
{ return vec3_length(vec3_create(a.x - b.x, a.y - b.y, a.z - b.z)); }

// Return if Vec3 a and b are equal
INLINE b8 vec3_is_equal(Vec3 a, Vec3 b)
{ return (a.x == b.x) && (a.y == a.y) && (a.z == b.z); }

// Print Vec3: (x, y);
INLINE void vec3_print(Vec3 a)
{ printf("(%f, %f, %f)", a.x, a.y, a.z); }

INLINE Vec4 mat4_mult_vec3(Mat4 a, Vec4 b)
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