#pragma once

#include <cstddef>

namespace test
{

class thread_group;

namespace this_thread_group
{

__thread thread_group *__singleton;

} // end this_thread_group

class thread_group
{
  public:
    thread_group(int id, int num_threads)
      : m_id(id),m_current_thread_id(-1),m_size(num_threads)
    {
      this_thread_group::__singleton = this;
    }

    virtual ~thread_group(){}

    inline int current_thread_id() const
    {
      return m_current_thread_id;
    }

    virtual void barrier() = 0;

    inline int size()
    {
      return m_size;
    }

    inline int get_id() const
    {
      return m_id;
    }

  protected:
    int next_current_thread_id()
    {
      return (current_thread_id()+1) % size();
    }

    void set_current_thread_id(int id)
    {
      m_current_thread_id = id;
    }

    int set_next_current_thread_id()
    {
      int old_id = current_thread_id();
      m_current_thread_id = next_current_thread_id();
      return old_id;
    }

    void increment_current_thread_id(void)
    {
      ++m_current_thread_id;
    }

  private:
    int m_id;
    int m_current_thread_id;
    int m_size;
}; // end thread_group

namespace this_thread_group
{

inline int current_thread_id()
{
  return __singleton->current_thread_id();
}

inline int get_id()
{
  return __singleton->get_id();
}

inline void barrier()
{
  __singleton->barrier();
}

inline int size()
{
  return __singleton->size();
}

} // end this_thread_group

namespace this_thread
{

inline int get_id()
{
  return this_thread_group::current_thread_id();
}

} // end namespace this_thread

} // end namespace test

#if defined(__GNUC__) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#include "detail/ucontext_thread_group_cpp11.hpp"
#else
#include "detail/ucontext_thread_group_cpp03.hpp"
#endif

