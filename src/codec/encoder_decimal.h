#ifndef FAST_SIMPLE_CODEC_ENCODER_DECIMAL_HEADER
#define FAST_SIMPLE_CODEC_ENCODER_DECIMAL_HEADER

#include "decimal.h"
#include "nullable_types.h"

namespace fast_simple_codec
{
	struct Encoder;
	int encode_decimal(Encoder& e, const Decimal& d);
	int encode_bcd(Encoder& e, void* bcd);

	int encode_decimal_optional(Encoder& e, const DecimalNullable& d);
	int encode_bcd_optional(Encoder& e, void* bcd);
}

#endif
