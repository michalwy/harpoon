#ifndef HARPOON_MEMORY_CHUNKED_MEMORY_HH
#define HARPOON_MEMORY_CHUNKED_MEMORY_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/memory.hh"

#include <vector>

namespace harpoon {
namespace memory {

class chunked_memory : public memory {
public:
	using chunk_item = std::uint8_t;
	using chunk_ptr = std::shared_ptr<chunk_item>;
	using chunk_container = std::vector<chunk_ptr>;
	using chunk_index = chunk_container::size_type;
	using chunk_offset = std::size_t;
	using chunk_length = std::size_t;

	chunked_memory(const std::string &name = {}, const address_range &address_range = {},
	               chunk_length chunk_length = 65536)
	    : memory(name, address_range), _chunk_length(chunk_length) {}
	chunked_memory(const chunked_memory &) = delete;
	chunked_memory &operator=(const chunked_memory &) = delete;

	virtual void prepare() override;
	virtual void cleanup() override;

	virtual void serialize(serializer::serializer &serializer) override;
	virtual void deserialize(deserializer::deserializer &deserializer) override;

	virtual ~chunked_memory() override;

protected:
	virtual void get_cell(address address, uint8_t &value) override;
	virtual void set_cell(address address, uint8_t value) override;

	chunk_index get_chunk_index(address address) const {
		return static_cast<chunk_index>(get_offset(address) / _chunk_length);
	}

	chunk_offset get_chunk_offset(address address) const {
		return get_offset(address) % _chunk_length;
	}

	const chunk_ptr &get_chunk(address address) const {
		return _memory[get_chunk_index(address)];
	}

	chunk_ptr &get_chunk(address address) {
		return _memory[get_chunk_index(address)];
	}

	inline void allocate_chunk(chunk_ptr &chunk, address address);

private:
	chunk_length _chunk_length{};
	chunk_container _memory{};
};

} // namespace memory
} // namespace harpoon

#endif
