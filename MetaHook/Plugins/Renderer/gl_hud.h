#pragma once

#include "enginedef.h"

#define MAX_GAUSSIAN_SAMPLES 16
#define LUMIN1x1_BUFFERS 3
#define DOWNSAMPLE_BUFFERS 2
#define LUMIN_BUFFERS 3
#define BLUR_BUFFERS 3

typedef struct
{
	int program;
	int tex;
}pp_downsample_program_t;

typedef struct
{
	int program;
	int texelsize;
	int tex;
}pp_downsample2x2_program_t;

typedef struct
{
	int program;
	int texelsize;
	int tex;
}pp_lumin_program_t;

typedef struct
{
	int program;
	int texelsize;
	int tex;
}pp_luminlog_program_t;

typedef struct
{
	int program;
	int texelsize;
	int tex;
}pp_luminexp_program_t;

typedef struct
{
	int program;
	int curtex;
	int adatex;
	int frametime;
}pp_luminadapt_program_t;

typedef struct
{
	int program;
	int tex;
	int lumtex;
}pp_brightpass_program_t;

typedef struct
{
	int program;
	int tex;
	int du;
}pp_gaussianblurv_program_t, pp_gaussianblurh_program_t;

typedef struct
{
	int program;
	int basetex;
	int blurtex;
	int lumtex;
	int blurfactor;
	int exposure;
	int darkness;
	int gamma;
}pp_tonemap_program_t;

extern cvar_t *r_hdr;
extern cvar_t *r_hdr_debug;

void R_InitBlur(const char *vs_code, int samples);
void R_BeginHUDQuad(void);

void R_DownSample(FBO_Container_t *src, FBO_Container_t *dst, qboolean filter2x2);
void R_LuminPass(FBO_Container_t *src, FBO_Container_t *dst, int logexp);
void R_LuminAdaptation(FBO_Container_t *src, FBO_Container_t *dst, FBO_Container_t *ada, double frametime);
void R_BrightPass(FBO_Container_t *src, FBO_Container_t *dst, FBO_Container_t *lum);
void R_BlurPass(FBO_Container_t *src, FBO_Container_t *dst, qboolean vertical);
void R_BrightAccum(FBO_Container_t *blur1, FBO_Container_t *blur2, FBO_Container_t *blur3, FBO_Container_t *dst);
void R_ToneMapping(FBO_Container_t *src, FBO_Container_t *dst, FBO_Container_t *blur, FBO_Container_t *lum);
void R_BlitToScreen(FBO_Container_t *src);
void R_BlitToFBO(FBO_Container_t *src, FBO_Container_t *dst);

void GLBeginHud(void);