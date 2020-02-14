#include "Maple.h"

extern Input_State input_state;

Key_State InputKeyStateGet(Input_Key input_key) {
	if (input_state.is_pressed[input_key] && input_state.was_pressed[input_key]) {
		return KS_Hold;
	}
	else if (input_state.is_pressed[input_key] && !input_state.was_pressed[input_key]) {
		return KS_Pressed;
	}
	else if (!input_state.is_pressed[input_key] && input_state.was_pressed[input_key]) {
		return KS_Released;
	}

	return KS_None;
}