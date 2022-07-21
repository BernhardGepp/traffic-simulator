#pragma once
#include "PrecompiledHeadersEdges.h"


namespace bbe {
	template <typename T>
	union PoolChunk {

		T value;
		PoolChunk<T>* nextPoolChunk;

		PoolChunk() {};
		~PoolChunk() {};
	};

	template <typename T, typename Allocator = std::allocator<PoolChunk<T>>>
	class PoolAllocator {
	private:
		static const size_t DEFAULTSIZE = 16384;//8192;//1024; 4096;
		size_t m_openallocations = 0;
		size_t m_size = 0;
		PoolChunk<T>* m_data = nullptr;
		std::queue<T*>m_queueOfAllocatedObjekts;
		Allocator* m_parentAllocator = nullptr;
		bool m_needsToDeleteParentAllocator = false;
		size_t m_serviceInt = 0;

	public:
		PoolChunk<T>* m_head = nullptr;
		PoolChunk<T>* m_maxHead = nullptr;
		PoolChunk<T>* m_minHead = nullptr;
		std::vector<T*>m_vectorOfAllocatedObjekts;
		std::vector<PoolChunk<T>*>m_quarantine;

		explicit PoolAllocator(size_t size = DEFAULTSIZE, Allocator* parentAllocator = nullptr)
			:m_size(size), m_parentAllocator(parentAllocator)
		{
			
			if (parentAllocator == nullptr) {
				m_parentAllocator = new Allocator();
				m_needsToDeleteParentAllocator = true;
			}

			m_data = m_parentAllocator->allocate(m_size);
			m_head = m_data;
			if (m_minHead == nullptr) {
				m_minHead = m_head;
			}

			for (size_t i = 0; i < m_size - 1; i++) {
				m_data[i].nextPoolChunk = std::addressof(m_data[i + 1]);
			}
			m_data[m_size - 1].nextPoolChunk = nullptr;
		}

		PoolAllocator(const PoolAllocator& other) = delete;
		PoolAllocator(const PoolAllocator&& other) = delete;
		PoolAllocator& operator= (const PoolAllocator& other) = delete;
		PoolAllocator&& operator= (const PoolAllocator&& other) = delete;
		~PoolAllocator() noexcept {
			m_parentAllocator->deallocate(m_data, m_size);
			while (!m_queueOfAllocatedObjekts.empty()) {
				m_queueOfAllocatedObjekts.pop();
			}
			m_quarantine.clear();
			m_vectorOfAllocatedObjekts.clear();
			if (m_openallocations != 0) {
				//__debugbreak();
			}
			
			if (m_needsToDeleteParentAllocator) {
				delete m_parentAllocator;
			}
			m_data = nullptr;
			m_head = nullptr;
		}

		template <typename ...arguments>
		T* allocate(arguments&& ... args) {
			if (m_head == nullptr) {
				__debugbreak();
				return nullptr;
			}
			m_openallocations++;
			if (!m_quarantine.empty()) {
				m_serviceInt = 0;
				while (m_serviceInt<m_quarantine.size())
				{
					if (m_quarantine[m_serviceInt] == m_head) {
						m_head = m_maxHead;
						break;
					}
					m_serviceInt++;
				}
			}
			PoolChunk<T>* poolChunk = m_head;
			m_head = m_head->nextPoolChunk;
			T* retVal = new(std::addressof(poolChunk->value)) T(std::forward<arguments>(args)...);
			
			if (m_head > m_maxHead) {
				m_maxHead = m_head;
			}
			m_queueOfAllocatedObjekts.push(retVal);
			
			if (m_queueOfAllocatedObjekts.size() > 97) {
				buildVectorOfObjektPtr();				
			}
			return retVal;
		}
		/*void deallocate(T* data);

		PoolChunk<T>* xxxx(T* data);

		void deallocateClean(T* data);

		void buildVectorOfObjektPtr();*/
		
		void PoolAllocator::deallocate(T* data) {
			PoolChunk<T>* poolChunk = reinterpret_cast<PoolChunk<T>*>(data);
			if (poolChunk != m_head) {
				m_openallocations--;
				data->~T();
				

				poolChunk->nextPoolChunk = m_head;
				m_head = poolChunk;
				
			}
		}

		PoolChunk<T>* PoolAllocator::xxxx(T* data) {
			return reinterpret_cast<PoolChunk<T>*>(data);
		}

		void PoolAllocator::deallocateClean(T* data) {
			if (data != nullptr) {
				m_openallocations--;
				data->~T();
				PoolChunk<T>* poolChunk = reinterpret_cast<PoolChunk<T>*>(data);
				poolChunk->nextPoolChunk = nullptr;
				m_quarantine.push_back(poolChunk);
			}
		}
		
		void PoolAllocator::buildVectorOfObjektPtr() {
			vehicle* vc = nullptr;
			bool serviceBool = false;
			while (!m_queueOfAllocatedObjekts.empty()) {
				vc = m_queueOfAllocatedObjekts.front();
				if (m_vectorOfAllocatedObjekts.empty()) {
					m_vectorOfAllocatedObjekts.push_back(vc);
				}
				else {
					serviceBool = false;
					for (auto &i : m_vectorOfAllocatedObjekts) {
						if (i == vc)
							serviceBool = true;
					}
					if (serviceBool == false) {
						m_vectorOfAllocatedObjekts.push_back(vc);
					}
				}
				m_queueOfAllocatedObjekts.pop();
				vc = nullptr;
			}
		}
	};
}



