#ifndef JUGGLE_H
#define JUGGLE_H

// Consider removing leds.this_index=0; from each function.   Seems to be what keeps the dots the same color.

// Functions:
//				juggle()
//				juggle_onedir()
//				sinelon_rainbow()

// Variables:	
//				this_index		(auto set to 0, maybe change?) maybe put a flag in 
//				this_fade 
//				numdots_ring
//				this_beat
//				current_palette
//				this_bright
//				current_blending
//				this_diff
//				ringBeat[]		(only used in columns modes)
//				gHue			(auto set; only used in sinelon modes)

void juggle(LEDStruct& leds) {
	leds.this_index = 0;
	fadeToBlackBy(leds.strip, NUM_LEDS, leds.this_fade);
	for (uint8_t i = 0; i < leds.numdots; i++) {
		leds.strip[beatsin16(leds.this_beat + i + leds.numdots, 0, STRIP_LENGTH - 1)] += ColorFromPalette(leds.current_palette, leds.this_index, leds.this_bright, leds.current_blending);
		leds.this_index += leds.this_diff;
	}
}


void juggle_onedir(LEDStruct& leds) {
	leds.this_index = 0;
	fadeToBlackBy(leds.strip, NUM_LEDS, leds.this_fade);
	if (!leds.this_dir) {
		for (uint8_t i = 0; i < leds.numdots; i++) {
			leds.strip[beatsin16_halfdown(leds.this_beat + i + leds.numdots, 0, STRIP_LENGTH - 1)] += ColorFromPalette(leds.current_palette, leds.this_index, leds.this_bright, leds.current_blending);
			leds.this_index += leds.this_diff;
		}
	}
	else {
		for (uint8_t i = 0; i < leds.numdots; i++) {
			leds.strip[beatsin16_halfup(leds.this_beat + i + leds.numdots, 0, STRIP_LENGTH - 1)] += ColorFromPalette(leds.current_palette, leds.this_index, leds.this_bright, leds.current_blending);
			leds.this_index += leds.this_diff;
		}
	}
}



void sinelon_rainbow(LEDStruct & leds) {
	fadeToBlackBy(leds.strip, NUM_LEDS, leds.this_fade);
	int pos = beatsin16(13, 0, STRIP_LENGTH);
	if (pos > leds.prev_pos) {
		for (int i = leds.prev_pos; i < pos + 1; i++) {
			leds.strip[i] = CHSV(gHue, leds.this_sat, leds.this_bright);
		}
	}
	else {
		for (int i = pos; i < leds.prev_pos + 1; i++) {
			leds.strip[i] = CHSV(gHue, leds.this_sat, leds.this_bright);
		}
	}
	gHue++;
}


#endif