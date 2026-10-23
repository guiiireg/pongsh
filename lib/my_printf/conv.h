#ifndef CONV_H_
#define CONV_H_

#include "out.h"
#include <stdarg.h>

void conv_char(out_ctx_t *ctx, va_list *ap);
void conv_str(out_ctx_t *ctx, va_list *ap);
void conv_int(out_ctx_t *ctx, va_list *ap);

#endif /* CONV_H_ */
