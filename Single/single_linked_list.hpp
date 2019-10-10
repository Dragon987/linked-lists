#pragma once

#include <exception>
#include <stdexcept>

namespace linked_lists
{
    namespace single
    {
        template <typename T>
        class holder
        {
        private:
            T *m_current;
            holder<T> *m_next;

        public:
            inline holder(T *current, holder<T> *next) noexcept
                : m_current(current), m_next(next) {}

            inline explicit holder(T *current) noexcept
                : m_current(current) { m_next = nullptr; }


            inline holder() noexcept = default;
            inline holder(const holder<T>& other) = default;
            inline holder<T>& operator=(const holder<T>& other) = default;
            inline holder(holder<T>&& other) noexcept = default;
            inline holder<T>& operator=(holder<T>&& other) noexcept = default;

            inline ~holder() noexcept
            {
                delete m_current;
            }

            inline T &get() const noexcept { return *m_current; }
            inline holder<T> &get_next() const noexcept { return *m_next; };

            inline void set(T* newCurrent) noexcept { m_current = newCurrent; }

            inline void set_next_delete_old(T* new_next) noexcept
            {
                delete m_next;
                m_next = new holder<T>(new_next);
            }

            inline void set_next_delete_old(holder<T>* new_next) noexcept
            {
                delete m_next;
                m_next = new_next;
            }

            inline void set_next(T* new_next) noexcept { m_next = new holder<T>(new_next); }
            inline void set_next(holder<T>* new_next) noexcept { m_next = new_next; }
        };

        template <typename T>
        class linked_list
        {
        private:
            holder<T> *m_first;
            int m_size;

            inline void add_to_end_impl(T* new_elem)
            {
                if (new_elem == nullptr)
                    throw std::invalid_argument("new_elem must not be nullptr(NULL)!");

                if (m_first == nullptr)
                {
                    m_first = new holder<T>(new_elem);

                    m_size = 1;
                    return;
                }

                holder<T> *curr = m_first;
                for (int i = 1; i < m_size; i++)
                    curr = &curr->get_next();

                curr->set_next(new_elem);

                m_size++;
            }

            inline void add_to_front_impl(T* new_elem)
            {
                if (new_elem == nullptr)
                    throw std::invalid_argument("new_elem must not be nullptr(NULL)!");

                if (m_first == nullptr)
                {
                    m_first = new holder<T>(new_elem);

                    m_size = 1;
                    return;
                }

                m_first = new holder<T>(new_elem, m_first);

                ++m_size;
            }

            inline void add_to_position_impl(T* new_elem, const int position)
            {
                if (new_elem == nullptr)
                    throw std::invalid_argument("new_elem must not be nullptr(NULL)!");

                if (position > m_size || position < 0)
                {
                    delete new_elem;
                    throw std::invalid_argument("Argument position is invalid!");
                }

                if (position == 0)
                {
                    add_to_front(new_elem);
                    return;
                }

                if (position == m_size)
                {
                    add_to_end(new_elem);
                    return;
                }

                holder<T> *prev = m_first;
                for (int i = 1; i < position; ++i)
                    prev = &prev->get_next();

                holder<T> *new_holder = new holder<T>(new_elem, &prev->get_next());

                prev->set_next(new_holder);
                ++m_size;
            }
        public:
            inline explicit linked_list(T *first) noexcept
            {
                m_first = new holder<T>(first);
                m_size = 1;
            }

            inline constexpr linked_list() noexcept
            {
                m_first = nullptr;
                m_size = 0;
            }

            inline linked_list(const linked_list<T>& other) = default;
            inline linked_list<T>& operator=(const linked_list<T>& other)  = default;

            inline linked_list(linked_list<T>&& other) noexcept = default;
            inline linked_list<T>& operator=(linked_list<T>&& other) noexcept = default;

            inline T &operator[](const int idx)
            {
                if (idx >= m_size || idx * -1 > m_size)
                    throw std::range_error("idx is out of range");

                if (idx >= 0)
                {
                    holder<T> *rv = m_first;

                    for (int i = 0; i < idx; i++)
                        rv = &rv->get_next();

                    return rv->get();
                }
                return (*this)[m_size + idx];
            }

            template<typename ...t_args>
            inline void add_front(t_args ...constructor_parameters)
            {
                add_to_front_impl(new T(constructor_parameters...));
            }

            template<typename ...t_args>
            inline void add_back(t_args ...constructor_parameters)
            {
                add_to_end_impl(new T(constructor_parameters...));
            }

            template<typename ...t_args>
            inline void add_position(int position, t_args ...constructor_parameters)
            {
                add_to_position_impl(new T(constructor_parameters...), position);
            }

            inline void remove_front() noexcept
            {
                holder<T> *caught = &m_first->get_next();

                delete m_first;

                m_first = caught;
                --m_size;
            }

            inline void remove_back() noexcept
            {
                holder<T> *curr = m_first;
                while (&curr->get_next() != nullptr)
                    curr = &curr->get_next();
                delete curr;
                --m_size;
            }

            inline void remove_position(const int position)
            {
                if (position < 0 || position >= m_size)
                    throw std::invalid_argument("Argument position is not valid!");

                if (position == 0)
                {
                    remove_front();
                    return;
                }

                if (position == m_size - 1)
                {
                    remove_back();
                    return;
                }

                holder<T>* curr = m_first;
                for (int i = 1; i < position; ++i)
                    curr = &curr->get_next();
                
                holder<T> *caught = &(curr->get_next().get_next());

                curr->set_next_delete_old(caught);
                m_size--;
            }

            inline int get_size() const noexcept { return m_size; }

            inline ~linked_list() noexcept
            {
                holder<T> **last = new holder<T> *[m_size];

                last[0] = m_first;
                for (int i = 1; i < m_size; i++)
                    last[i] = &last[i - 1]->get_next();

                for (int i = m_size - 1; i >= 0; i--)
                    delete last[i];

                delete[] last;
            }
        };

        template<typename linked_list_type>
        auto make_linked_list() noexcept -> linked_list<linked_list_type>
        {
            return { new linked_list_type() };
        }

        template<typename linked_list_type, typename ...type_constructor_param>
        auto make_linked_list(type_constructor_param ...param) noexcept -> linked_list<linked_list_type>
        {
            return linked_list<linked_list_type>(new linked_list_type(param...));
        }

    } // namespace single
} // namespace linked_lists