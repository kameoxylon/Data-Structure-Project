#include "FSet.h"
#include "FSetOp.h"

template<typename T>
class LockFreeHashTable
{
	class HNode
	{
		public:
			FSet<T> buckets;
			int size;
			HNode pred;

			HNode(FSet<T> buckets, int size, HNode pred)
			{
				this->buckets = buckets;
				this->size = size;
				this->pred = pred;
			}
	};

	public:
		FSet<T> fset;
		FSetOp<T> fsetOp;
		HNode head;

		LockFreeHashTable()
		{
			head = new HNode(new FSet<T>(), 1, NULL);
			head.buckets[0] = FSet();
		}

		bool insert(int k)
		{
			bool resp = apply(INS, k);
			//Apply resize heuristic here
			if (true)
			{
				resize(true);
			}
			return resp;
		}

		bool remove(int k)
		{
			bool resp = apply(REM, k);
			//Apply resize heuristic here
			if (true)
			{
				resize(false);
			}
			return resp;
		}

		bool contains(int k)
		{
			HNode temp = head;
			FSet<T> b = temp.buckets[k % temp.size]
			if (b == NULL)
			{
				HNode s = temp.pred;
				if (s != NULL)
				{
					b = s.buckets[k % s.size];
				}
				else
				{
					b = temp.buckets[k % temp.size];
				}
			}	
			return hasMember(b, k);
		}

		void resize(bool grow)
		{
			HNode temp = head;
			if (temp.size > 1 || grow)
			{
				for (int i = 0; i < temp.size; i++)
				{
					initBucket(temp, i);
				}
				temp.pred = null;

				if (grow)
				{
					int size = temp.size * 2;
				}
				else
				{
					int size = temp.size / 2;
				}

				FSet<T> buckets = new FSet();
				HNode tempPrime = new HNode(buckets, size, temp);
				//COMPARE AND SWAP
			}
		}

		bool apply(enum type, int k)
		{
			FSetOp<T> op = new FSetOp(type, k, false)
			while(true)
			{
				HNode temp = head;
				FSet<T> b = temp.buckets[k % temp.size];
				if (b == NULL)
				{
					b = initBucket(temp, k % temp.size);
				}
				if invoke(b, op)
				{
					return getResponse(op);
				}
			}
		}

		FSet<T> initBucket(HNode temp, int i)
		{
			FSet<T> b = temp.buckets[i];
			HNode s = temp.pred;
			if (b == NULL && s != NULL)
			{
				if (temp.size == (s.size * 2))
				{
					FSet<T> m = s.buckets[i % s.size];
					//SET FREEZE
				}
				else
				{
					FSet<T> m = s.buckets[i];
					FSet<T> n = s.buckets[i + temp.size];
					//SET FREEZE
				}
				HNode bPrime = new FSet();
				//COMPARE AND SWAP.
			}
			return temp.buckets[i];
		}

		bool getResponse(FSetOp<T> &op)
		{
			return op.resp;
		}

		bool hasMember(FSet<T> b, int k)
		{
			return b.find(k) != b.end();
		}

		bool invoke(FSet<T> b, FSetOp<T> op)
		{
			if (b.ok && !op.done)
			{
				if (op.typeOp == INS)
				{
					op.resp = !hasMember(b, op.key);
					b.set.insert(op.key);
				}
				else if (op.typeOp == REM)
				{
					op.resp = hasMember(b, op.key);
					b.set.erase(op.key);
				}
				op.done = true;
			}
			return op.done;
		}

		std::set<int> freeze(FSet<T> b)
		{
			if (b.ok)
			{
				b.ok = false;
			}
			return b.set;
		}
};