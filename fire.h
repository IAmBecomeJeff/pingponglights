#ifndef FIRE_H
#define FIRE_H

// Functions:
//				fire()			
//				fire_pal()
//				fire_mirror()
//				fire_mirror_pal()

// Variables:
//				cooling
//				sparking
//				current_palete			(only used in pal modes)
//				this_bright				(only used in pal modes)
//				current_blending		(only used in pal modes)


void fire(LEDStruct& leds) {

	for (uint8_t i = 0; i < STRIP_LENGTH; i++) {
		leds.heat[i] = qsub8(leds.heat[i], random8(0, ((leds.cooling * 10) / STRIP_LENGTH) + 2));
	}

	for (int k = STRIP_LENGTH - 3; k >= 2; k--) {
		leds.heat[k] = (leds.heat[k - 1] + leds.heat[k - 2] + leds.heat[k - 2]) / 3;
	}

	if (random8() < leds.sparking) {
		int y = random8(7);
		leds.heat[y] = qadd8(leds.heat[y], random8(160, 255));
	}

	if (leds.this_dir) {
		for (int j = 0; j < STRIP_LENGTH; j++) {
			CRGB hcolor = HeatColor(leds.heat[j]);
			leds.strip[j] = CRGB(hcolor.r, hcolor.g, hcolor.b);
		}
	}
	else {
		for (int j = 0; j < STRIP_LENGTH; j++) {
			CRGB hcolor = HeatColor(leds.heat[j]);
			leds.strip[j] = CRGB(hcolor.r, hcolor.g, hcolor.b);
		}
	}
}

void fire_pal(LEDStruct & leds) {

	for (uint8_t i = 0; i < STRIP_LENGTH; i++) {
		leds.heat[i] = qsub8(leds.heat[i], random8(0, ((leds.cooling * 10) / STRIP_LENGTH) + 2));
	}

	for (int k = STRIP_LENGTH - 3; k >= 2; k--) {
		leds.heat[k] = (leds.heat[k - 1] + leds.heat[k - 2] + leds.heat[k - 2]) / 3;
	}

	if (random8() < leds.sparking) {
		int y = random8(7);
		leds.heat[y] = qadd8(leds.heat[y], random8(160, 255));
	}

	if (leds.this_dir) {
		for (int j = 0; j < STRIP_LENGTH; j++) {
			leds.strip[j] = ColorFromPalette(leds.current_palette, scale8(leds.heat[j], 240), leds.this_bright, leds.current_blending);
		}
	}
	else {
		for (int j = 0; j < STRIP_LENGTH; j++) {
			leds.strip[(STRIP_LENGTH - 1) - j] = ColorFromPalette(leds.current_palette, scale8(leds.heat[j], 240), leds.this_bright, leds.current_blending);
		}
	}
}


void fire_mirror(LEDStruct & leds) {
	for (int i = 0; i < STRIP_LENGTH / 2; i++) {
		leds.heat_mirror[i] = qsub8(leds.heat_mirror[i], random8(0, ((leds.cooling * 10) / (STRIP_LENGTH / 2)) + 2));
	}

	for (int k = (STRIP_LENGTH / 2) - 1; k >= 2; k--) {
		leds.heat_mirror[k] = (leds.heat_mirror[k - 1] + leds.heat_mirror[k - 2] + leds.heat_mirror[k - 2]) / 3;
	}

	if (random8() < leds.sparking) {
		int y = random8(7);
		leds.heat_mirror[y] = qadd8(leds.heat_mirror[y], random8(160, 255));
	}

	if (leds.this_dir) {
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(leds.heat_mirror[j]);
			leds.strip[j] = CRGB(hcolor.r, hcolor.g, hcolor.b);
			leds.strip[STRIP_LENGTH - 1 - j] = CRGB(hcolor.r, hcolor.g, hcolor.b);
		}
	}
	else {
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(leds.heat_mirror[j]);
			leds.strip[(STRIP_LENGTH / 2) - 1 - j] = CRGB(hcolor.r, hcolor.g, hcolor.b);
			leds.strip[(STRIP_LENGTH / 2) + j] = CRGB(hcolor.r, hcolor.g, hcolor.b);
		}
	}
}


void fire_mirror_pal(LEDStruct & leds) {
	for (int i = 0; i < STRIP_LENGTH / 2; i++) {
		leds.heat_mirror[i] = qsub8(leds.heat_mirror[i], random8(0, ((leds.cooling * 10) / (STRIP_LENGTH / 2)) + 2));
	}

	for (int k = (STRIP_LENGTH / 2) - 1; k >= 2; k--) {
		leds.heat_mirror[k] = (leds.heat_mirror[k - 1] + leds.heat_mirror[k - 2] + leds.heat_mirror[k - 2]) / 3;
	}

	if (random8() < leds.sparking) {
		int y = random8(7);
		leds.heat_mirror[y] = qadd8(leds.heat_mirror[y], random8(160, 255));
	}

	if (leds.this_dir) {
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(leds.heat_mirror[j], 240);
			leds.strip[j] = ColorFromPalette(leds.current_palette, colorindex, leds.this_bright, leds.current_blending);
			leds.strip[STRIP_LENGTH - 1 - j] = ColorFromPalette(leds.current_palette, colorindex, leds.this_bright, leds.current_blending);
		}
	}
	else {
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(leds.heat_mirror[j], 240);
			leds.strip[(STRIP_LENGTH / 2) - 1 - j] = ColorFromPalette(leds.current_palette, colorindex, leds.this_bright, leds.current_blending);
			leds.strip[(STRIP_LENGTH / 2) + j] = ColorFromPalette(leds.current_palette, colorindex, leds.this_bright, leds.current_blending);
		}
	}
}




#endif