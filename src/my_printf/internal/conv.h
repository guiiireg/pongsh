#ifndef CONV_H_
#define CONV_H_

#include "out.h"
#include <stdarg.h>

enum { KIND_CHAR, KIND_STR, KIND_PTR, KIND_NUM };

typedef struct conv_s {
    char spec;
    char kind;
    char sign;
    const char *base;
    int base_len;
    void (*fn)(out_ctx_t *ctx, va_list *ap, const struct conv_s *conv);
} conv_t;

void handle_spec(out_ctx_t *ctx, const char *format, int *i, va_list *ap);

#endif /* CONV_H_ */
