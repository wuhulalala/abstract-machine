#include <am.h>
#include <nemu.h>

#define AUDIO_FREQ_ADDR      (AUDIO_ADDR + 0x00)
#define AUDIO_CHANNELS_ADDR  (AUDIO_ADDR + 0x04)
#define AUDIO_SAMPLES_ADDR   (AUDIO_ADDR + 0x08)
#define AUDIO_SBUF_SIZE_ADDR (AUDIO_ADDR + 0x0c)
#define AUDIO_INIT_ADDR      (AUDIO_ADDR + 0x10)
#define AUDIO_COUNT_ADDR     (AUDIO_ADDR + 0x14)

static size_t p = 0;

void __am_audio_init() {
}

void __am_audio_config(AM_AUDIO_CONFIG_T *cfg) {
  cfg->present = inl(AUDIO_INIT_ADDR);
  cfg->bufsize = inl(AUDIO_SBUF_SIZE_ADDR);
}

void __am_audio_ctrl(AM_AUDIO_CTRL_T *ctrl) {
  outl(AUDIO_FREQ_ADDR, ctrl->freq);
  outl(AUDIO_CHANNELS_ADDR, ctrl->channels);
  outl(AUDIO_SAMPLES_ADDR, ctrl->samples);
}

void __am_audio_status(AM_AUDIO_STATUS_T *stat) {
  stat->count = inl(AUDIO_COUNT_ADDR);
}

void __am_audio_play(AM_AUDIO_PLAY_T *ctl) {
  int bufsize = inl(AUDIO_SBUF_SIZE_ADDR);
  int count = inl(AUDIO_COUNT_ADDR);
  int len = ctl->buf.end - ctl->buf.start;
  while (bufsize - count < len) {
    count = inl(AUDIO_COUNT_ADDR);
  }

  uint8_t *fb = (uint8_t*)(uintptr_t)(AUDIO_SBUF_ADDR);
  for (int i = 0; i < len; i++) {
    int px;
    if (p + i >= bufsize) {
      px = (p + i) % bufsize;
    } else {
      px = p + i;
    }
    fb[px] = ((uint8_t *)(ctl->buf.start))[i];
  }
  
  p = (p + len) % bufsize;

}
