                                                                                                                        /*
--------------------------------------------------------------------------------
   cnt/list.hpp
   copyright(C) kyuhyun park
   1994.12.30
--------------------------------------------------------------------------------                                        */

#ifdef def_cnt_list_hpp
#error 'cnt/list.hpp' duplicated.
#endif

#define def_cnt_list_hpp

#ifndef def_pub_config_hpp
#include <pub/config.hpp>
#endif

#ifndef def_pub_memory_hpp
#include <pub/memory.hpp>
#endif

template<class cls_t>
class tem_obj_list
{
   private:

      struct cls_frame
      {
         cls_frame* prev;
         cls_frame* next;
         cls_t data_t;
      };

      struct cls_null_frame
      {
         cls_frame* prev;
         cls_frame* next;
      };

      cls_frame* base;
      cls_frame* cur;
      cls_frame* save;
      int cnt;

   public:

      tem_obj_list  ();
     ~tem_obj_list  ();

      void link();
      void unlink();

      void first();
      void next();
      void prev();

      void save_pos();
      void restore_pos();

      int    get_cnt();
      cls_t* get_pnt();
};

template<class cls_t> tem_obj_list<cls_t>::tem_obj_list ()
{
   base = (cls_frame*) mem_alloc(sizeof(cls_null_frame));
   base->next = base->prev = cur = base;
   save = NULL;
   cnt = 0;
}

template<class cls_t> tem_obj_list<cls_t>::~tem_obj_list ()
{
   cls_frame* cur = base->next;

   while (cur != base)
   {
      cur = cur->next;
      delete cur->prev;
   }
   mem_free(base);
}

template<class cls_t> void tem_obj_list<cls_t>::link()
{
   cls_frame* new_node = new cls_frame();
   new_node->next = cur->next;
   new_node->prev = cur;
   cur->next->prev = new_node;
   cur->next = new_node;
   cur = new_node;
   cnt++;
}

template<class cls_t> void tem_obj_list<cls_t>::unlink()
{
   mac_assert(cur != base);

   cls_frame* del_node = cur;
   cur->next->prev = cur->prev;
   cur->prev->next = cur->next;
   prev();
   delete del_node;
   cnt--;
}

template<class cls_t> void tem_obj_list<cls_t>::first()
{
   cur = base->next;
}

template<class cls_t> void tem_obj_list<cls_t>::next()
{
   cur = cur->next;
   if (cur == base) cur = cur->next;
}

template<class cls_t> void tem_obj_list<cls_t>::prev()
{
   cur = cur->prev;
   if (cur == base ) cur = cur->prev;
}

template<class cls_t> void tem_obj_list<cls_t>::save_pos()
{
   save = cur;
}

template<class cls_t> void tem_obj_list<cls_t>::restore_pos()
{
   mac_assert(save);
   cur = save;
}

template<class cls_t> cls_t* tem_obj_list<cls_t>::get_pnt()
{
   mac_assert(cur != base);
   return &cur->data_t;
}

template<class cls_t> int tem_obj_list<cls_t>::get_cnt ()
{
   return cnt;
}

/*
tem_obj_list<int> list;
*/

