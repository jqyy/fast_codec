#include "encoder.h"
#include "encoder_string_ascii.h"

namespace fast_codec
{
	size_t encode_string_ascii(Encoder& e, const char c)
	{
		char str[2];
		str[0] = c;
		str[1] = '\0';
		return encode_string_ascii(e, str, sizeof(str));
	}

	size_t encode_string_ascii(Encoder& e, const char* str, size_t size)
	{
		if (str != NULL && size != 0)
		{
			for (uint32_t i = 0; i < size - 1; ++i)
			{
				if(str[i+1] == '\0')
				{
					// Stop bit
					write_byte(e, str[i] | 0x80);
					return i+1;				
				}
				write_byte(e, str[i]);
			}
			// Stop bit
			write_byte(e, str[size - 1] | 0x80);
			return size - 1;
		}
		else
		{
			write_byte(e, 0x80);
			return 1;
		}
		return 0;
	}

	size_t encode_string_ascii(Encoder& e, const std::string& str)
	{
		return encode_string_ascii(e, str.c_str(), str.size());
	}

	size_t encode_string_ascii_optional(Encoder& e, const char* str, size_t size)
	{
		if(str == NULL)
		{
			// Null
			write_byte(e, 0x80);
			return 1;
		}
		else if (size == 0)
		{
			// Empty string
			write_byte(e, 0x00);
			write_byte(e, 0x80);
			return 2;
		}
		else
		{
			return encode_string_ascii(e, str, size);
		}
	}

	size_t encode_string_ascii_optional(Encoder& e, const string_nt& str)
	{
		if (str.is_null_)
			return encode_string_ascii_optional(e, nullptr, 0);
		else
			return encode_string_ascii_optional(e, str.value_.c_str(), str.value_.size());
	}
} // namespace
