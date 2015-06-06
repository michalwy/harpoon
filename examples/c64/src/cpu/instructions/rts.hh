#ifndef CPU_INSTRUCTIONS_RTS_HH
#define CPU_INSTRUCTIONS_RTS_HH

#include "mos_6510_instruction.hh"

namespace commodore {
namespace cpu {
namespace instructions {

class rts : public mos_6510_nullary_instruction<0x60, 6> {
public:
	void execute() {
		get_cpu()->pop(get_cpu()->get_registers().PC);
		get_cpu()->get_registers().PC++;
	}
};

}
}
}

#endif

