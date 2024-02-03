typedef int sig_atomic_t;


typedef void signal_handler_t(int sig);

#define SIGINT 0
#define SIG_DFL 0

signal_handler_t* signal(int sig, signal_handler_t* handler);
