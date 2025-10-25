#ifndef __Encoder_H
#define __Encoder_H

typedef enum {
	L_encoder,
	R_encoder,
}Encoder;

void Encoder_Checklevel(void);
void Encoder_Softsimulation(void);
int16_t Encoder_GetSpeed(Encoder direct);

#endif

