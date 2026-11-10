// Hello world para PS2 con gsKit: un cuadrado que rebota en pantalla.
// Sirve para comprobar que el toolchain compila y que el .elf corre en PCSX2 / PS2 real.
#include <kernel.h>
#include <stdio.h>
#include <gsKit.h>
#include <dmaKit.h>

int main(void)
{
    GSGLOBAL *gs = gsKit_init_global();
    gs->ZBuffering = GS_SETTING_OFF;        // juego 2D: sin z-buffer (ahorra VRAM)
    gs->PrimAlphaEnable = GS_SETTING_OFF;

    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

    gsKit_init_screen(gs);
    gsKit_mode_switch(gs, GS_ONESHOT);

    u64 bg = GS_SETREG_RGBAQ(0x10, 0x10, 0x20, 0x00, 0x00);
    u64 fg = GS_SETREG_RGBAQ(0xE0, 0x30, 0x30, 0x80, 0x00);

    const float size = 64.0f;
    float x = 50.0f, y = 50.0f, dx = 4.0f, dy = 3.0f;
    unsigned frames = 0;

    printf("ps2-hello: %dx%d\n", gs->Width, gs->Height);

    for (;;) {
        gsKit_clear(gs, bg);
        gsKit_prim_sprite(gs, x, y, x + size, y + size, 1, fg);

        x += dx; y += dy;
        if (x < 0 || x + size > gs->Width)  dx = -dx;
        if (y < 0 || y + size > gs->Height) dy = -dy;

        gsKit_queue_exec(gs);
        gsKit_sync_flip(gs);                // espera al vsync y cambia de buffer

        if (++frames % 600 == 0) printf("frames: %u\n", frames);
    }
    return 0;
}
