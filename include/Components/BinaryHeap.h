#ifndef __BINARYHEAP_H
#define __BINARYHEAP_H


#include <vector>
#include <list>

namespace Components
{

	typedef void* HeapElemPtr;

	/** Binary Heap Class. 
			This class represents an ordinary binary heap, however there are some
			notable details. The actual values are stored in a linked list.
			An array of iterators is the data structure that is actually heapified.

			This implementation has an important feature: The heap insert 
			function returns a pointer to the place where the inserted element is 
			stored. It is never moved (because only elements in a list of iterators
			are actually moved), hence using this pointer we can decrease the key of 
			the element at a later time. This is important if we are implementing
			Sethian's Fast Marching Method.
	*/

	template<class KT, class VT>
	class BinaryHeap
	{
		struct Element
		{
			KT k;   // Key 
			VT v;   // Value
			int pi; // Position in heap

			Element(){}
			Element(KT _k, const VT& _v, int _pi): 
				k(_k), v(_v), pi(_pi) {}
		};

		/** List of elements. The use of a linked list is to ensure
				that elements don't move around in memory - even if we erase
				or add elements.	*/
		typedef std::list<Element> ElementList;
		ElementList elems; 

		/// Array of iterators pointing to element. This is the heap
		std::vector<typename ElementList::iterator> perm;

		/** Move element down inside the heap. The element is pushed down until
				its position is correct - i.e. until the heap property is fulfilled. */
		void downheap(int i);
	
		/** Move element up until the heap property is fulfilled */
		void upheap(int i);

		/// Index of last element in heap.
		int last_element;
	
		/// Increase number of elements in heap by one
		void increase()
		{
			last_element++;
			perm.resize(last_element+1);
		}

		/// Decrease number of elements in heap by one.
		void decrease()
		{
			last_element--;
			perm.resize(last_element+1);
		}
	
	public:

		/// Construct an empty Binary heap
		BinaryHeap();

		/// Clear the binary heap (make empty)
		void clear();
	
		/** Insert an element in the heap. The two arguments are (key,value)
				insert returns a pointer to the position of the element in the 
				element list */
		HeapElemPtr insert(const KT, const VT&);

		/** Decrease key of element. Given an element pointer (see insert) 
				and a key, this function moves it up in the heap until the 
				heap property is fulfilled. If the new key is larger than the old
				this is a noop */
		bool decrease_key(HeapElemPtr,KT);
	
		/// Extract smallest element and maintain heap property 
		bool extract_min(KT&, VT&);

	};

	template<class KT, class VT>
	BinaryHeap<KT,VT>::BinaryHeap(): elems(), perm(1), last_element(0) {}

	template<class KT, class VT>
	void BinaryHeap<KT,VT>::clear()
	{
		elems.clear();
		perm.resize(1);
		last_element=0;
	}
	

	template<class KT, class VT>
	void BinaryHeap<KT,VT>::downheap(int i)
	{
		for(;;)
			{
				int lft = i<<1;     // Left = i*2
				int rgt = (i<<1)|1; // Right = i*2+1
				int smallest;
			
				if (lft <= last_element && (*perm[lft]).k < (*perm[i]).k)
					smallest = lft;
				else 
					smallest = i;

				if (rgt <= last_element && (*perm[rgt]).k < (*perm[smallest]).k )
					smallest = rgt;
      
				if (smallest != i)
					{
						ElementList::iterator tmp = perm[i];

						perm[i] = perm[smallest];
						(*perm[i]).pi = i;

						perm[smallest] = tmp;
						(*perm[smallest]).pi = smallest;

						i = smallest;
					}
				else break;
			}
	}


	template<class KT, class VT>
	void BinaryHeap<KT,VT>::upheap(int i)
	{
		int j=i;
		ElementList::iterator orig = perm[i];
		while(j>1 && (*perm[j>>1]).k > (*orig).k)
			{
				int parent = j>>1;
				perm[j] = perm[parent];
				(*perm[j]).pi = j;
				j = parent;
			}
		perm[j] = orig;
		(*perm[j]).pi = j;
	}


	template<class KT, class VT>
	HeapElemPtr BinaryHeap<KT,VT>::insert(const KT key, const VT& val)
	{
		increase();
		elems.push_front(Element(key,val,last_element));
		perm[last_element] = elems.begin();
		upheap(last_element);
		return HeapElemPtr(&elems.front());
	}


	template<class KT, class VT>
	bool BinaryHeap<KT,VT>::extract_min(KT& key, VT& val)
	{
		if (last_element==0) 
			return false;

		key = (*perm[1]).k;
		val = (*perm[1]).v;

		elems.erase(perm[1]);

		// Put largest element on top and move it down to its proper
		// place to maintain heap property.
		perm[1] = perm[last_element];
		(*perm[1]).pi = 1;
		decrease();
		downheap(1);
		return true;
	}

	template<class KT, class VT>
	bool BinaryHeap<KT,VT>::decrease_key(HeapElemPtr _hep, KT key)
	{
		Element* hep = static_cast<Element*>(_hep);
		if (hep != 0 && hep->k > key)
			{
				hep->k = key;
				upheap(hep->pi);
				return true;
			}
		return false;
	}

}

namespace CMP = Components;


#endif
