#ifndef C64_HH
#define C64_HH

#include "harpoon/computer_system.hh"
#include "harpoon/memory/memory.hh"
#include "harpoon/log/log.hh"

namespace commodore {

class c64 : public harpoon::computer_system {
public:
	c64(const harpoon::log::log_ptr& log);

	virtual ~c64();

	void create();

	virtual void prepare();

private:
	void create_execution_unit();
	void create_memory();

	harpoon::memory::memory_weak_ptr _kernal{};
};

}

#endif
