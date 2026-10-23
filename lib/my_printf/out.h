#ifndef OUT_H_
#define OUT_H_

#define OUT_INITIAL_CAP 64

typedef struct out_ctx_s {
    char *buf;
    int len;
    int cap;
    int error;
} out_ctx_t;

void out_init(out_ctx_t *ctx);
void out_putchar(out_ctx_t *ctx, char c);
void out_putstr(out_ctx_t *ctx, const char *str);
void out_flush(out_ctx_t *ctx);
void out_free(out_ctx_t *ctx);

#endif /* OUT_H_ */
