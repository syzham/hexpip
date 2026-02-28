#include "Registry.h"

#include <ranges>

Entity Registry::create()
{
    if (!m_freeList.empty()) {
        const uint32_t e = m_freeList.back();
        m_freeList.pop_back();
        return e;
    }
    return m_nextEntity++;
}

void Registry::destroy(const Entity id)
{
  for (const auto &store: m_storages | std::views::values)
    store->erase(id);

  m_freeList.push_back(id);
}

void Registry::clear()
{
	m_storages.clear();
	m_freeList.clear();
	m_nextEntity = 0;
}