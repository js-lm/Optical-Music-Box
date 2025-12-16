#pragma once

#include <cstdint>
#include <array>

namespace utilities{

    template<typename Type, uint8_t MaxSize>
    class RingBuffer{
    private:
        std::array<Type, MaxSize> buffer_;
        
        uint8_t head_{0};
        uint8_t tail_{0};
        uint8_t size_{0};

    public:
        bool push(Type item){
            if(size_ == MaxSize) return false;
            buffer_[head_] = item;
            head_ = (head_ + 1) % MaxSize;
            size_++;
            return true;
        }

        Type pop(){
            Type item{buffer_[tail_]};
            tail_ = (tail_ + 1) % MaxSize;
            size_--;
            return item;
        }

        uint8_t size() const{ return size_;}
    };

} // namespace utilities