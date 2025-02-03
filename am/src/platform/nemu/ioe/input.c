#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  kbd->keycode = inl(KBD_ADDR);
  if ((kbd->keycode & KEYDOWN_MASK) == 0x8000) {
    kbd->keydown = 1;
    kbd->keycode = kbd->keycode ^ KEYDOWN_MASK;
    return;
  }
  kbd->keydown = 0;
}
