#ifndef SUPPORT_FUNCTIONS_H
#define SUPPORT_FUNCTIONS_H


//		Transitioning works as follows:
//
//		updates
//		  ||
//		  \/			
//		new_leds -> actual_leds -> old_leds
//		
//		Begin transition sends updates -> new_leds
//
//		repeat


// Increase or decrease LEDStruct's delay based on boolean direction
void delay_change(LEDStruct& leds, bool delay_direction) {
	if (delay_direction) {
		leds.this_delay++;
	}
	else {
		if (leds.this_delay == 1) { leds.this_delay = 1; }
		else { leds.this_delay--; }
	}
	constrain(leds.this_delay, 1, 1000);
}


// Find index of current (target) palette
void updatePaletteIndex(LEDStruct& leds) {
	for (int i = 0; i < palette_count; i++) {
		if (leds.target_palette == palette_array[i]) {
			leds.palette_index = i;
			break;
		}
	}
}


// Increase or decrease LEDSstruct's palette based on boolean direction
void palette_change(LEDStruct& leds, bool direction) {
	updatePaletteIndex(leds);
	if (direction) { leds.palette_index++; }
	else {
		if (leds.palette_index == 0) { leds.palette_index = palette_count - 1; }
		else { leds.palette_index--; }
	}
	if (leds.palette_index > palette_count - 1) { leds.palette_index = 0; }
	leds.target_palette = palette_array[leds.palette_index];
}

//// May not need this, if structA = structB works:
//void copy_led_struct(LEDStruct& a, LEDStruct& b) {
//	a.start_index = b.start_index;
//	a.this_inc = b.this_inc;
//	a.this_index = b.this_index;
//	a.this_dir = b.this_dir;
//	a.this_phase = b.this_phase;
//	a.this_speed = b.this_speed;
//	a.this_bright = b.this_bright;
//	a.this_rot = b.this_rot;
//	a.all_freq = b.all_freq;
//	a.this_delay = b.this_delay;
//	a.this_cutoff = b.this_cutoff;
//	a.this_fade = b.this_fade;
//	a.this_diff = b.this_diff;
//	a.bg_clr = b.bg_clr;
//	a.bg_bri = b.bg_bri;
//	a.bg_sat = b.bg_sat;
//	a.that_phase = b.that_phase;
//	a.that_speed = b.that_speed;
//	a.that_hue = b.that_hue;
//	a.that_rot = b.that_rot;
//	a.this_hue = b.this_hue;
//	a.this_sat = b.this_sat;
//	a.that_sat = b.that_sat;
//	a.current_palette = b.current_palette;
//	a.current_blending = b.current_blending;
//	a.target_palette = b.target_palette;
//	a.palette_index = b.palette_index;
//	a.led_mode = b.led_mode;
//	for (int i = 0; i < NUM_LEDS; i++) {
//		a.strip[i] = b.strip[i];
//	}
//	a.led_mode = b.led_mode;
//	a.numdots = b.numdots;
//	a.numdots_ring = b.numdots_ring;
//	a.this_beat = b.this_beat;
//	for (int i = 0; i < 4; i++) {
//		a.ringBeat[i] = b.ringBeat[i];
//	}
//	for (int i = 0; i < STRIP_LENGTH; i++) {
//		a.heat[i] = b.heat[i];
//		for (int r = 0; r > 4; r++) {
//			a.heat_ring[i][r] = b.heat_ring[i][r];
//		}
//	}
//	for (int i = 0; i < STRIP_LENGTH / 2; i++) {
//		a.heat_mirror[i] = b.heat_mirror[i];
//		for (int r = 0; r < 4; r++) {
//			a.heat_mirror_ring[i][r] = b.heat_mirror_ring[i][r];
//		}
//	}
//	a.cooling = b.cooling;
//	a.sparking = a.cooling;
//	for (int r = 0; r < 4; r++) {
//		a.cooling_columns[r] = b.cooling_columns[r];
//		a.sparking_columns[r] = b.sparking_columns[r];
//	}
//	a.prev_pos = b.prev_pos;
//	a.combo = b.combo;
//}

// Check if we're in a combo and update new_leds.combo value if so
//void combo_check() {
//	if (std::find(std::begin(combo_modes), std::end(combo_modes), new_leds.led_mode) != std::end(combo_modes)) { // check if led_mode is in list of modes that use combo LEDStructs 
//		new_leds.combo = 1;
//	}
//	else { new_leds.combo = 0; }
//	combo_num = new_leds.combo + old_leds.combo;
//}
//
//// Wipe new variables and copy relevant info, only called during mode-change
//void combo_handling() {
//	if (combo_num == 1) { // only new_leds is using a combo mode
//		comboA_leds = new_leds;
//		comboB_leds = new_leds;
//		//copy_led_struct(comboA_leds, new_leds);
//		//copy_led_struct(comboB_leds, new_leds);
//	}
//	if (combo_num == 2) {
//		comboC_leds = new_leds;
//		comboD_leds = new_leds;
//		//copy_led_struct(comboC_leds, new_leds);
//		//copy_led_struct(comboD_leds, new_leds);
//	}
//}
#endif