class test
{
   public:

   static void func();

   test();
};

test::test()
{
   void (*pfunc)() = func;
}
