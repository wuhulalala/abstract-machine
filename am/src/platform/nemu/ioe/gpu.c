#include <am.h>
#include <nemu.h>
#include <stdint.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  int w = inw(VGACTL_ADDR + 2), h = inw(VGACTL_ADDR);
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = w, .height = h,
    .vmemsz = w * h
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int wid = inw(VGACTL_ADDR + 2);
  uint32_t *fb = (uint32_t *)(uintptr_t)(FB_ADDR);
  for (int x = 0; x < ctl->w; x++) {
    for (int y = 0; y < ctl->h; y++) {
      int rx = x + ctl->x, ry = y + ctl->y;
      fb[rx + ry * wid] = ((uint32_t*)ctl->pixels)[x + y * ctl->w];
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
