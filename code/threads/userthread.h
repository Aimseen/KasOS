extern int do_UserThreadCreate(int f, int arg);
extern void do_UserThreadExit();
extern void do_UserThreadJoin(int id);

struct s_farg{
  int f;
  int arg;
};
