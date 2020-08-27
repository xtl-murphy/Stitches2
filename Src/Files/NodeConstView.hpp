#pragma once

#include <cstdint>
#include <variant>
#include <string>
#include <vector>

namespace Stitches {
class Node;
/**
 * @brief Class that is returned from a {@link Node} when getting constant properties. This represents a key tree from a parent,
 * this allows reads of large trees with broken nodes to not need to generate new content.
 */
class NodeConstView {
	friend class Node;
protected:
	using Key = std::variant<std::string, uint32_t>;

	NodeConstView() = default;
	NodeConstView(const Node *parent, Key key, const Node *value);
	NodeConstView(const NodeConstView *parent, Key key);

public:
	enum class Type : uint8_t {
		Object, Array, String, Boolean, Integer, Decimal, Null, Token, Unknown
	};

	bool has_value() const noexcept { return value != nullptr; }
	const Node *get() const { return value; }

	explicit operator bool() const noexcept { return has_value(); }
	operator const Node &() const { return *value; }

	const Node &operator*() const { return *value; }
	const Node *operator->() const { return value; }

	template<typename T>
	T GetName() const;

	template<typename T>
	T Get() const;
	template<typename T>
	T Get(const T &fallback) const;
	template<typename T>
	bool Get(T &dest) const;
	template<typename T, typename K>
	bool Get(T &dest, const K &fallback) const;

	std::vector<NodeConstView> GetProperties(std::string_view name) const;
	NodeConstView GetPropertyWithBackup(std::string_view name, std::string_view backupName) const;
	NodeConstView GetPropertyWithValue(std::string_view propertyName, std::string_view propertyValue) const;

	NodeConstView operator[](std::string_view key) const;
	NodeConstView operator[](uint32_t index) const;

	std::vector<Node> GetProperties() const;
	
	std::string GetName() const;

	Type GetType() const;
	
protected:
	const Node *parent = nullptr;
	const Node *value = nullptr;
	std::vector<Key> keys;
};
}
