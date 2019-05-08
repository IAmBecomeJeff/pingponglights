// confetti.h

#ifndef CONFETTI_h
#define CONFETTI_h

void confetti_pal(LEDStruct& leds) {
	fadeToBlackBy(leds.strip, NUM_LEDS, leds.this_fade);
	int pos = random16(NUM_LEDS);
	leds.strip[pos] = ColorFromPalette(leds.current_palette, leds.this_index + random8(leds.this_diff) / 4, leds.this_bright, leds.current_blending);
	leds.this_index += leds.this_inc;
} // confetti_pal()


#endif

