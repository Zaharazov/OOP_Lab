
template <typename T, typename Alloc = std::allocator<T>>
class List
{
private:
 
    struct Item 
    {
        Item* next;
        T value;
    };
 
    using Alloc_traits = std::allocator_traits<Alloc>;
    using Alloc_Item = typename Alloc_traits::template rebind_alloc<Item>;
    using Alloc_Item_traits = std::allocator_traits<Alloc_Item>;
    Item* _m_head;
    Item* _m_tail;
    size_t _m_size;
    Alloc_Item _m_alloc;
 
public:
    using value_type = T;
 
    class Iterator
    {
 
    private:
 
        friend List;
        Item* m_item;
 
    public:
 
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag; 
 
        Iterator() : m_item()
        {
        }
 
        Iterator(Item* p) : m_item(p)
        {
        }
 
        Iterator(Item& p) : m_item(p.m_item)
        {
        }
 
        ~Iterator() = default;
 
        reference operator *() const
        {
            return m_item->value;
        }
 
        pointer operator ->()
        {
            return &m_item->value;
        }
 
        Iterator &operator++()
        {
            m_item = m_item->next;
            return *this;
        }
 
        Iterator operator++(int)
        {
            Iterator new_one = *this;
            m_item = m_item->next;
            return new_one;
        }
 
        bool operator==(const Iterator &other) const
        {
            return (m_item == other.m_item);
        }
 
        bool operator!=(const Iterator &other) const
        {
            return (m_item != other.m_item);
        }
    };
 
    class Const_Iterator
    {
 
    private:
 
        friend List;
        const Item* m_item;
 
    public:
 
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag; 
 
        Const_Iterator(): m_item()
        {
        }
 
        Const_Iterator(const Item* p) : m_item(p)
        {
        }
 
        Const_Iterator(const Item& p) : m_item(p.m_item)
        {
        }
 
        ~Const_Iterator() = default;
 
        reference operator*() const
        {
            return m_item->value;
        }
 
        pointer operator->() const
        {
            return &m_item->value;
        }
 
        Const_Iterator &operator++()
        {
            m_item = m_item->next;
            return *this;
        }
 
        Const_Iterator operator++(int)
        {
            Const_Iterator new_one = *this;
            m_item = m_item->next;
            return new_one;
        }
 
        bool operator==(const Const_Iterator &other) const
        {
            return (m_item == other.m_item);
        }
 
        bool operator!=(const Const_Iterator &other) const
        {
            return (m_item != other.m_item);
        }
    };
 
    List(): _m_alloc()
    {
        _m_head = Alloc_Item_traits::allocate(_m_alloc, 1);
        _m_head->next = nullptr;
        _m_head->value = 0;
        _m_tail = _m_head;
 
        _m_size = 0;
    }
 
    List(size_t n, const T & val = T()) : _m_alloc()
    {
        Item* data[n + 1];
        for (size_t i = 0; i <= n; ++i)
        {
            data[i] = Alloc_Item_traits::allocate(_m_alloc, 1);
        }
        _m_head = data[0]; 
        _m_tail = data[n];
        _m_head->next = data[1];
        _m_head->value = val;
 
        for (int i = 1; i < n; ++i) 
        {
            data[i]->next = data[i + 1];
            data[i]->value = val;
        }
        _m_tail->next = nullptr;
        _m_size = n;
    }
 
    List(const std::initializer_list<T>& l): _m_alloc()
    {
        Item* data [l.size() + 1];
        for (int i = 0; i <= l.size(); ++i) 
        {
            data[i] = Alloc_Item_traits::allocate(_m_alloc, 1);
        }
        _m_head = data[0]; 
        _m_tail = data[l.size()];
        _m_tail->next = nullptr;
        _m_head->next = data[1];
 
        auto itr = l.begin();
        _m_head->value = *itr;
        ++itr;
        for (int i = 1; i < l.size(); ++i) 
        {
            data[i]->next = data[i + 1];
            data[i]->value = *itr++;
        }
 
        _m_size = l.size();
    }
 
    List(const List<T, Alloc>& other): _m_alloc() {
        Item* data [other.size() + 1];
        for (int i = 0; i <= other.size(); ++i) 
        {
            data[i] = Alloc_Item_traits::allocate(_m_alloc, 1);
        }
 
        _m_head = data[0]; _m_tail = data[other.size()];
        _m_head->next = data[1];
 
        auto itr = other.begin();
        _m_head->value = *itr;
        ++itr;
        for (int i = 1; i < other.size(); ++i) 
        {
            data[i]->next = data[i + 1];
            data[i]->value = *itr++;
        }
 
        _m_size = other.size();
    }
 
    ~List() noexcept 
    {
        Iterator i = this->begin();
        while (i != this->end()) 
        {
            Iterator tmp(i.m_item->next);
            i->~T();
            Alloc_Item_traits::deallocate(_m_alloc, i.m_item, 1);
            i = tmp;
        } 
        Alloc_Item_traits::deallocate(_m_alloc, i.m_item, 1);
 
        _m_size = 0;
    }
 
    void resize(size_t n)
    {
        
        Iterator itr = this->end();
        for (int i = _m_size; i < n; ++i) 
        {
            Iterator tmp(Alloc_Item_traits::allocate(_m_alloc, 1));
            itr.m_item->next = tmp.m_item;
            itr = tmp;
        }
        _m_tail = itr.m_item;
        itr.m_item->next = nullptr;
        _m_size = n;
    }
 
    Iterator insert(Iterator itr, const T & val) {
        Iterator result(Alloc_Item_traits::allocate(_m_alloc, 1));
        result.m_item->next = itr.m_item;
        Iterator result2;
        if (itr != this->begin())
        {
            while (result2->next != result)
            {
                result2++;
            }
        }
        result2.m_item->next = result.m_item;
        
        Iterator itr2;
        while (itr2->next != itr)
        {
            itr2++;
        }
        itr2.m_item = result.m_item;
        result.m_item->value = val;
        if (itr == this->begin()) 
        {
            _m_head = result.m_item;
        }
        ++_m_size;
        return result;
    } 
 
   Iterator push_back(const T& val) 
   {
        Iterator result = this->end();
        _m_tail = Alloc_Item_traits::allocate(_m_alloc, 1);
        result.m_item->value = val;
        result.m_item->next = _m_tail;
        ++_m_size;
        return result;
    }
 
    Iterator pop_back() 
    {
        if (this->empty())
            throw std::underflow_error("The List is empty");
        
        Iterator result = --this->end();
        Alloc_Item_traits::deallocate(_m_alloc, _m_tail, 1);
        _m_tail = result.m_item;
        _m_tail->next = nullptr;
        --_m_size;
        return result;
    }
 
    Iterator erase(Iterator itr) 
    { 
        if (this->empty())
            throw std::underflow_error("The List is empty");
        
        Iterator result = itr.m_item->next;
        Iterator itr2;
        if (itr != this->begin())
            {
                while (itr2->next != itr)
                {
                    itr2++;
                }
                itr.m_item->next = result.m_item;
            }
        else 
        {
            _m_head = result.m_item;
        }

        Iterator result2;
        while (result2->next != result)
        {
            result2++;
        }
        result2.m_item = itr2.m_item;
        
        Alloc_Item_traits::deallocate(_m_alloc, itr.m_item, 1);
        --_m_size;
        return result;
    }           
 
    List& operator=(const List<T, Alloc>& other) 
    {
        if (this->size() != other.size()) 
        {
            this->resize(other.size());
        }
        auto itr1 = this->begin(), itr2 = other.begin();
        while (itr1 != this->end() && itr2 != other.end()) 
        {
            *itr1 = *itr2;
            ++itr1; ++itr2;
        }
        return *this;
    }
 
    size_t size() const noexcept 
    {
        return _m_size;
    }
 
    bool empty() const noexcept 
    {
        return _m_size == 0;
    }
 
    Iterator begin() noexcept 
    {
        return Iterator(_m_head);
    }

    Const_Iterator begin() const noexcept 
    {
        return Const_Iterator(_m_head);
    }
 
    Iterator end() noexcept 
    {
        return Iterator(_m_tail);
    }

    Const_Iterator end() const noexcept 
    {
        return Const_Iterator(_m_tail);
    }
 
    Const_Iterator cbegin() const noexcept 
    {
        return Const_Iterator(_m_head);
    }
 
    Const_Iterator cend() const noexcept 
    {
        return Const_Iterator(_m_tail);
    }
 
};
