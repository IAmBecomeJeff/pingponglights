/*
 Name:		pingponglights.ino
 Created:	5/8/2019 2:00:45 PM
 Author:	JeffKarle
*/

#include "FastLED.h"
//#include <algorithm>	// for searching if led mode is in a combo mode
//#include <iterator>		// for searching if led mode is in a combo mode
//#include "Bounce2.h"	// Debouncing the KY-040 rotary switch
#include "variables.h"
#include "LEDStruct.h"
#include "gradient_palettes.h"
#include "support_functions.h"
#include "one_sin_pal.h"
#include "confetti.h"
#include "juggle.h"
#include "fire.h"
#include "colorwave.h"

void setup() {
	delay(2000);
	LEDS.setBrightness(max_bright);
	LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(actual_leds.strip, NUM_LEDS);
	set_max_power_in_volts_and_milliamps(5, 5000);	// TODO update this for live values
	random16_set_seed(4832);
	random16_add_entropy(analogRead(2));
	new_leds.isNew = 1;
	actual_leds.target_palette = RainbowColors_p;
	strobe_mode(actual_leds, 1);

}

void loop() {

	EVERY_N_MILLISECONDS(50) {	// Palette blending
		uint8_t maxChanges = 24;
		if (transitioning > 0) {	// If transitioning, update new and old palettes
			nblendPaletteTowardPalette(new_leds.current_palette, new_leds.target_palette, maxChanges);
			nblendPaletteTowardPalette(old_leds.current_palette, old_leds.target_palette, maxChanges);
		}
		else {		// If not transitioning, update actual leds palette, which it gained from new_leds at the end of transitioning
			nblendPaletteTowardPalette(actual_leds.current_palette, actual_leds.target_palette, maxChanges);
		}
	}

	EVERY_N_SECONDS(20) {		// Transition every N seconds
		old_leds = actual_leds; //  copy_led_struct(old_leds, actual_leds);	// copy the currently running leds into old_leds
		new_leds.led_mode = random8(max_mode + 1);
		transitioning = 1;
		//combo_check();
		strobe_mode(new_leds, 1);			// fill new_leds with the next animation
	}

	EVERY_N_MILLIS_I(old_timer, old_leds.this_delay) {	// Keep a timer for the old leds to function independently of new leds
		if (transitioning > 0) {
			old_timer.setPeriod(old_leds.this_delay);
			strobe_mode(old_leds, 0);
		}
	}

	EVERY_N_MILLIS_I(new_timer, new_leds.this_delay) {	// timer for new leds
		if (transitioning > 0) {
			new_timer.setPeriod(new_leds.this_delay);
			strobe_mode(new_leds, 0);
		}
	}

	EVERY_N_MILLIS_I(actual_timer, actual_leds.this_delay) {	// timer for actual leds in regular mode
		actual_timer.setPeriod(actual_leds.this_delay);
		if (!transitioning) {
			strobe_mode(actual_leds, 0);
		}
	}

	if (transitioning > 0) {						// TODO, update with multiple transition types
		if (transition_wait) {
			blending_ratio += 1;
		}
		for (int i = 0; i < NUM_LEDS; i++) {
			actual_leds.strip[i] = blend(old_leds.strip[i], new_leds.strip[i], blending_ratio);
		}
		if (blending_ratio >= 255) {
			actual_leds = new_leds; // copy_led_struct(actual_leds, new_leds);
			transitioning = 0;
			blending_ratio = 0;
			fill_solid(old_leds.strip, NUM_LEDS, CRGB(0, 0, 0));
			fill_solid(new_leds.strip, NUM_LEDS, CRGB(0, 0, 0));
		}
		transition_wait = !transition_wait;
	}

	show_at_max_brightness_for_power();
}

void strobe_mode(LEDStruct& leds, bool mc) {
	if (mc) {
		fill_solid(leds.strip, NUM_LEDS, CRGB(0, 0, 0));
		//combo_handling();
	}

	switch (leds.led_mode) { // keep combo_modes array updated to include led_mode values that use a combo LEDStruct (combo[A,B,C,D]_leds)
		case 0:
			if (mc) { leds.this_delay = 15; leds.target_palette = RainbowColors_p; leds.all_freq = 4; leds.this_bright = 255; leds.start_index = 0; leds.this_inc = 16; leds.this_cutoff = 200; leds.this_rot = 10; leds.this_speed = 3; }
			one_sin_pal(leds);
			break;

		case 1:
			if (mc) { leds.this_delay = 15; leds.target_palette = ForestColors_p; leds.all_freq = 16; leds.this_bright = 255; leds.start_index = 64; leds.this_inc = 2; leds.this_cutoff = 224; leds.this_rot = 0; leds.this_speed = 6; }
			one_sin_pal(leds);
			break;

		case 2:
			if (mc) { leds.this_delay = 15; leds.target_palette = LavaColors_p; leds.all_freq = 32; leds.this_bright = 255; leds.start_index = 0; leds.this_inc = 4; leds.this_cutoff = 180; leds.this_rot = 2; leds.this_speed = 4; }
			one_sin_pal(leds);
			break;

		case 3:
			if (mc) { leds.this_delay = 20; leds.target_palette = PartyColors_p; leds.this_inc = 1; leds.this_fade = 2; leds.this_diff = 32; leds.this_bright = 255; }
			confetti_pal(leds);
			break;

		case 4:
			if (mc) { leds.this_delay = 15; leds.cooling = 65; leds.sparking = 100; }
			fire(leds);
			break;

		case 5:
			if (mc) { leds.this_delay = 15; leds.cooling = 35; leds.sparking = 40; leds.target_palette = LavaColors_p; leds.this_bright = 255; }
			fire_pal(leds);
			break;

		case 6:
			if (mc) { leds.this_delay = 10; leds.cooling = 50; leds.sparking = 50; }
			fire_mirror(leds);
			break;

		case 7:
			if (mc) { leds.this_delay = 20; leds.cooling = 10; leds.sparking = 120; leds.target_palette = BlacK_Blue_Magenta_White_gp; }
			fire_mirror_pal(leds);
			break;

		case 8:
			if (mc) { leds.this_delay = 20; leds.target_palette = palette_array[random8(palette_count - 1)]; }
			colorwave(leds);
			break;

		case 9:
			if (mc) { leds.this_delay = 10; leds.this_fade = 55; leds.numdots = 4; leds.this_beat = 16; leds.target_palette = palette_array[random8(palette_count - 1)]; leds.this_diff = 8;  }
			juggle(leds);
			break;

		case 10:
			if (mc) { leds.this_delay = 10; leds.this_dir = 0; leds.this_fade = 55; leds.numdots = 4; leds.this_beat = 16; leds.target_palette = palette_array[random8(palette_count - 1)]; leds.this_diff = 8; }
			juggle_onedir(leds);
			break;

		case 11:
			if (mc) { leds.this_delay = 10; leds.this_dir = 1; leds.this_fade = 16; leds.numdots = 4; leds.this_beat = 16; leds.target_palette = palette_array[random8(palette_count - 1)]; leds.this_diff = 8; }
			juggle_onedir(leds);
			break;

		case 12:
			if (mc) { leds.this_delay = 15; leds.this_fade = 32;  leds.this_sat = 240;  }
			sinelon_rainbow(leds);
			break;
	}
}