Naming
------

Source code naming standard:

* File names are composed of lower-case characters and underscores. Like
  this: u-core.c
* Variable and function names are composed of lower-case characters
  and underscores. Like this: u_time_timer_set();
* Variable and function names that are visible outside of their module
  must begin with the name of the module. Like this:
  u_time_timer_set(), which is in the u-time module, declared in
  u-time.h, and implemented in u-time.c.
* C macros are composed of upper-case characters and underscores. Like
  this: U_TASK().
* Configuration definitions begin with the CONF_ . Like
  this: CONF_U_SCHED_OPT.