#ifndef __GLAD_H_
#define __GLAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <glad/gl.h>

typedef GLADloadfunc GLADloadproc;

static inline int gladLoadGLLoader(GLADloadproc load) {
    return gladLoadGL(load);
}

#ifdef __cplusplus
}
#endif

#endif // __GLAD_H_
