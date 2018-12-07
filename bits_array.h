#ifndef BITS_ARRAY
#define BITS_ARRAY
#include <iostream>
#include <vector>

namespace bits
{
	typedef char byte;

	template<class T, std::size_t size_in_bits>
	class Bits_array
	{
	public:
		Bits_array() {};
		std::vector<byte> to_bits(std::vector<T> &arr);
		std::vector<T> to_values(std::vector<byte> &arr);
	private:
		std::size_t round_up(float num);
	};

	template<class T, std::size_t size_in_bits>
	std::vector<byte> Bits_array::to_bits(std::vector<T> &arr)
	{
		std::size_t s = round_up((float) arr.size() * size_in_bits / 8);
		std::vector<byte> res_arr(s);
		std::size_t curr_bit = 1;
		const byte mask = 1;

		for (std::size_t i = 0; i < arr.size(); ++i)
		{
			std::size_t bits_to_record = size_in_bits;
			T value = arr[i];
			byte *raw_value = reiterpret_cast<byte *>(&value);
			std::size_t byte_counter = 0;

			for (; bits_to_record >= 8 && curr_bit == 1; ++byte_counter, ++i)
			{
				T value = arr[i];
				byte curr_byte = raw_value[byte_counter];
				res_arr[i] = curr_byte;
				bits_to_record -= 8;
			}

			for (; curr_bit <= 8 && bits_to_record > 0; ++curr_bit, --bits_to_record)
			{
				res_arr[i] = res_arr[i] | ((mask >> (curr_bit - 1)) && raw_value[byte_counter]));
			}

			if (curr_bit > 8)
				curr_bit = 1;
		}
	}

	template<class T, std::size_t size_in_bits>
	std::vector<T> Bits_array::to_values(std::vector<byte> &arr)
	{
		std::vector<T> res_arr(arr.size() * 8 / size_in_bits);

		std::size_t curr_bit = 1;
		const byte mask = 1;

		for (std::size_t i = 0; i < arr.size(); ++i)
		{
			std::size_t bits_to_record = size_in_bits;
			T value = arr[i];
			byte *raw_value = reiterpret_cast<byte *>(&res_arr[i]);
			std::size_t byte_counter = 0;

			for (; bits_to_record >= 8 && curr_bit == 1; ++byte_counter, ++i)
			{
				T value = arr[i];
				raw_value[byte_counter] = arr[i];
				bits_to_record -= 8;
			}

			for (; curr_bit <= 8 && bits_to_record > 0; ++curr_bit, --bits_to_record)
			{
				raw_value[byte_counter] = arr[i] | ((mask >> (curr_bit - 1)) && arr[i]);
			}

			if (curr_bit > 8)
				curr_bit = 1;
		}
	}

	template<class T, std::size_t size_in_bits>
	std::size_t Bits_array::round_up(float num)
	{
		return num == static_cast<std::size_t>(num) ? static_cast<std::size_t>(num) : static_cast<std::size_t>(num + 1.0);
	}
}

#endif
