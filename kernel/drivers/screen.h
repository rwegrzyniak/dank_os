#define VGA_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define SUPREMACY_TTY_COLOR 0x0f
#define RED_ON_WHITE 0xf4

/* Screen i/o ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/* Public kernel API */
void clear_screen();
void k_print_at(char *message, int col, int row);
void k_print(char *message);
