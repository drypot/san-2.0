																																								/*
--------------------------------------------------------------------------------
   pub/cnt.hpp
   copyright(c) kyuhyun park
   1993.06.02
--------------------------------------------------------------------------------                                        */

#ifdef def_pub_cnt_hpp
#error 'pub/cnt.hpp' duplicated.
#endif

#define def_pub_cnt_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_inline_hpp
#include <pub/inline.hpp>
#endif

#ifndef def_pub_process_hpp
#include <pub/process.hpp>
#endif

/*
   not yet completed ...
*/

template<class T>
class base_index_representation
{
   protected:

      T base;
      word index;
      word cnt;

   public:
      base_index_representation(T s, word c) : base(s), cnt(c), index(0)
      {
         mac_assert( index<cnt );
      }

      operator T ()
      {
         return base+index;
      }

      T operator = (T new_val)
      {
         index=(word)(new_val-base);
         mac_assert( index<cnt );
         mac_assert( new_val == base+index );
         return base+index;
      }
};

template<class T>
class circular : public base_index_representation<T>
{
   public:

      circular(T s, T e,word) : base_index_representation<T>(s,index_num_between(s,e))
      {
         mac_assert( e >= s );
      }

      circular(T s, word c) : base_index_representation<T>(s,c)
      {
      }

      circular(word c) : base_index_representation<T>(T(0),c)
      {
      }

      T operator -= (word c)
      {
         mac_assert( index<cnt );
         c %= cnt;
         index >= c  ? index-=c : index += cnt - c;
         return *this;
      }

      T operator += (word c)
      {
         mac_assert( index<cnt );
         c%=cnt;
         cnt > index+c  ? index+=c : index+= c - cnt;
         return *this;
      }

      T dec(word c=1) { return operator-=(c); }
      T inc(word c=1) { return operator+=(c); }
};

template<class T>
class non_circular : public base_index_representation<T>
{

   public:

      non_circular(T s, T e,word) : base_index_representation<T>(s,index_num_between(s,e))
      {
         mac_assert( e >= s );
      }

      non_circular(T s, word c) : base_index_representation<T>(s,c)
      {
      }

      non_circular(word c) : base_index_representation<T>(T(0),c)
      {
      }

      T operator = (const T new_val)
      {
         return base_index_representation<T>::operator=(new_val);
      }

      T operator -= (word c)
      {
         mac_assert( index<cnt );
         index >= c  ? index-=c : index = 0;
         return *this;
      }

      T operator += (word c)
      {
         mac_assert( index<cnt );
         c%=cnt;
         cnt > index+c  ? index+=c : index= cnt-1;
         return *this;
      }

      T dec(word c=1) { return operator-=(c); }
      T inc(word c=1) { return operator+=(c); }
};
