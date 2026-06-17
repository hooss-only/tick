typedef struct {
        void (*init)(void);
        void (*update)(void);
        void (*render)(void);
} screen_t;
