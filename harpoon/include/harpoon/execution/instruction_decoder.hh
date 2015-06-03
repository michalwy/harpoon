#ifndef HARPOON_EXECUTION_INSTRUCTION_DECODER_HH
#define HARPOON_EXECUTION_INSTRUCTION_DECODER_HH

#include "harpoon/harpoon.hh"
#include "harpoon/execution/instruction.hh"
#include "harpoon/execution/instruction_invoker.hh"

namespace harpoon {
namespace execution {

template<typename T, typename CPU>
class instruction_decoder {
public:

	instruction_decoder() {}
	instruction_decoder(const instruction_decoder<T, CPU>&) = default;
	instruction_decoder<T, CPU>& operator=(const instruction_decoder<T, CPU>&) = default;

	std::uint_fast64_t operator()(CPU * cpu, instruction_handler& invoker, std::size_t& length) {
		T instruction;
		instruction.set_cpu(cpu);
		instruction.decode();
		invoker = instruction_invoker<T>(instruction);
		length = T::LENGTH;
		return T::CYCLES_DECODE;
	}
};

template<typename CPU>
using instruction_decode_handler = std::function<std::uint_fast64_t(CPU *, instruction_handler&, std::size_t&)>;

}
}

#endif

