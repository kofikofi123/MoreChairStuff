#include <stdlib.h>
#include <unistr.h>
#include "VMUtils.h"
#include "UnicodeBuffer.h"
#include "Utils.h"
#include "KString.h"
///


ecmaString* newString(uint16_t* buffer, uint64_t length){
	ecmaString* string = malloc(sizeof(ecmaString));

	if (string == NULL) return NULL;

	string->Buffer = buffer;
	string->Length = length;

	return string;
}

ecmaString*	convertAsciiToString(const char* source){
	uint64_t sourceLength = stringLength(source);
	size_t lengthp;
	uint16_t* buffer = u8_to_u16((uint8_t*)source, sourceLength, NULL, &lengthp);

	if (buffer == NULL) return NULL;

	return newString(buffer, lengthp);
}

ecmaString* convertUniToString(uint32_t* source){
	uint64_t length = scanU32Buffer(source);
	size_t lengthp;
	uint16_t* buffer = u32_to_u16(source, length, NULL, &lengthp);

	if (buffer == NULL) return NULL;

	return newString(buffer, lengthp);
}

void freeString(ecmaString* string){
	free(string->Buffer);
	free(string);
}