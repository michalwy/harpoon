#ifndef HARPOON_EXECUTION_PROCESSING_UNIT_HH
#define HARPOON_EXECUTION_PROCESSING_UNIT_HH

#include "harpoon/harpoon.hh"
#include "harpoon/hardware_component.hh"
#include "harpoon/execution/execution_unit.hh"
#include "harpoon/execution/cycle.hh"

#include <thread>
#include <atomic>

namespace harpoon {
namespace execution {

class processing_unit : public hardware_component {
public:

	using hardware_component::hardware_component;

	virtual void prepare();

	virtual void boot();
	virtual void shutdown();

	virtual void run();

	cycle wait_for_cycle(std::uint_fast64_t cycles = 1);

	cycle wait_for_next_cycle() {
		return wait_for_cycle(1);
	}

	virtual std::uint_fast64_t fetch() = 0;
	virtual std::uint_fast64_t execute() = 0;

	bool is_running() const {
		return _running;
	}

	execution_unit_ptr get_execution_unit() const {
		return _execution_unit.lock();
	}

	cycle get_cycle() const {
		return _cycle;
	}

	std::uint_fast64_t get_executed_instructions() const {
		return _executed_instructions;
	}

	virtual void log_state(log::message::Level level = log::message::Level::DEBUG) const;
	virtual void log_registers(log::message::Level level) const;

	virtual ~processing_unit();

private:
	execution_unit_weak_ptr _execution_unit{};
	std::atomic_bool _running{false};
	std::unique_ptr<std::thread> _thread{};
	clock::tick _last_tick{};
	atomic_cycle _cycle{};
	std::atomic_uint_fast64_t _executed_instructions{};
};

using processing_unit_ptr = std::shared_ptr<processing_unit>;
using processing_unit_weak_ptr = std::weak_ptr<processing_unit>;

}
}

#endif
