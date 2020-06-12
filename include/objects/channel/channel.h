#pragma once

#include "modules/thread/types/mutex.h"
#include "modules/thread/types/conditional.h"

namespace love
{
    class Channel: public Object
    {
        // for the Wrapper
        friend int PerformAtomic(lua_State * L);

        public:
            static love::Type type;

            Channel();
            ~Channel();

            uint64_t Push(const Variant & variant);

            // Blocking push
            bool Supply(const Variant & variant);

            bool Supply(const Variant & variant, double timeout);

            bool Pop(Variant * variant);

            // Blocking pop
            bool Demand(Variant * variant);

            bool Demand(Variant * variant, double timeout);

            bool Peek(Variant * variant);

            int GetCount() const;

            bool HasRead(uint64_t id) const;

            void Clear();

        private:
            void LockMutex();
            void UnlockMutex();

            thread::MutexRef mutex;
            thread::ConditionalRef condition;
            std::queue<Variant> queue;

            uint64_t sent;
            uint64_t received;
    };
}