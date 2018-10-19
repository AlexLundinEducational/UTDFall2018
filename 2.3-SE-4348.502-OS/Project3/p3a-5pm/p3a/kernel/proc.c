#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
// added for p3a
#include "pstat.h"
#include "spinlock.h"
// modified for project p3a



// moved ptable here for p3a so entire kernel has access
struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

// added for p3a
struct {
  struct spinlock lock;
  struct pstat pstat[NPROC];
} stable;


static struct proc *initproc;

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

// p3a notes
// when a process is created, alloproc is automatically called
// when user passes argument to kernel argptr can be used to retreive it

int lottery_Total(void){
  struct proc *p;
  int ticket_aggregate=0;
  
  //loop over process table and increment total tickets if a runnable process is found 
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
  {
    if(p->state==RUNNABLE){
      ticket_aggregate+=p->tickets;
    }
  }
  
  return ticket_aggregate;          // returning total number of tickets for runnable processes
}


void
set_current_processes_tickets(int n)
{
  // added for p3a
  struct pstat *st;
  acquire(&ptable.lock);
  acquire(&stable.lock);  
  cprintf("\nSetting tickets to: %d", n);
  
  cprintf("\n\nPtable PID is : %d", proc->pid);
  cprintf("\nTickets : %d", proc->tickets);
  proc->tickets=n;
  cprintf("\nUpdated tickets : %d", proc->tickets);
  
  // create a pointer into the stable
  st = stable.pstat;   
  cprintf("\n\nStable PID is : %d", st->pid[proc->pid]);
  cprintf("\nStable tickets: %d", st->tickets[proc->pid]);
  st->tickets[proc->pid] = n; // the number of tickets this process has
  cprintf("\nUpdated stable tickets: %d", st->tickets[proc->pid]);
  release(&ptable.lock);
  release(&stable.lock);  
}

// set tickets of the calling process with the value from user
int
sys_settickets(void)
{
	
  cprintf("\nsys_settickets tickets called.");
  
  int n;

  // if argint returns anything invalid
  // the value returned from the function into n, will be less than 0
  // so return -1 to whoever called sys_settickets
  if(argint(0, &n) < 0 ){
	  return -1;
  }
    

  // if argint returned a valid number into n
  // check the ticket bounds
  if (n > 1000000){
	  //cprintf("\nN > 1000000.");
	  return -1;
  }
	 
  // if argint returned a valid number into n
  // check the ticket bounds
  if (n <= 0 ){
	  //cprintf("\nN less than or equal to 0. N = %d", n);
	  return -1;
  }
	 
	 
  // if process made it to here, then argint was valid and n is within ticket bounds
  // print n and set tickets to n
  
  // set the current process, proc, tickets to n
  set_current_processes_tickets(n);
  
  cprintf ("\n");
  // return 0 for all sucesses
  return 0;
}

// get info from the passed in pstat pointer
// this process needs access to the stable, so it must stay defined here
int
sys_getpinfo(void)
{
  cprintf("\nsys_getpinfo called.");

  struct pstat *st;
  struct proc *p;
  
  // if argptr returned a pointer less than 0
  if(argptr(0, (void*)&st, sizeof(*st)) < 0){
	  cprintf ("\nBad pointer, -1");
	  return -1;
  }
    
  // if argptr retunred null
  if(st == NULL){
	  cprintf ("\nNull pstat pointer.");
	  return -1;
  }
  
  // if process makes it this far
  // pointer is valid
  // print from the st table with the index's that are inuse
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if (p->state != UNUSED){
		  cprintf ("\nInfo from the statistics table."); 
		  cprintf ("\nProcess In Use Bit: %d", st->inuse[p->pid]);
		  cprintf ("\nNumber of tickets: %d", st->tickets[p->pid]); 
		  cprintf ("\nProcess ID: %d", st->pid[p->pid]); 
		  cprintf ("\nNumber of ticks so far : %d", st->ticks[p->pid]);   
		  cprintf ("\n");		
	}
	  
  }

  return 0;
}

// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;
  // added for p3a
  struct pstat *st;
  
  acquire(&ptable.lock);
  acquire(&stable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;
  release(&ptable.lock);
  release(&stable.lock);
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;
  
  // print from the ptable entry of this process before edits
/*   cprintf ("\nBefore Allproc edits the process table with the st pointer."); 
  cprintf ("\nProcess Name: %s" , p->name);
  cprintf ("\nProcess ID: %d", p->pid); 
  cprintf ("\nNumber of tickets: %d", p->tickets);   
  cprintf ("\nAllproc added the edited process to the p.table with the above information.\n"); */
  
  // edit the process table to include 10 tickets by defaullt
  p->tickets = 10;
  // print from the ptable entry of this process
/*   cprintf ("\nAfter Allproc edited the process table with the st pointer."); 
  cprintf ("\nProcess Name: %s" , p->name);
  cprintf ("\nProcess ID: %d", p->pid); 
  cprintf ("\nNumber of tickets: %d", p->tickets);   
  cprintf ("\nAllproc added the edited process to the p.table with the above information.\n"); */
  
  // edit the stable with process information
  // before releasing locks
  // create a pointer into the stable
  st = stable.pstat;
  
  // use the pid of p to jump into the correct location of the stable
  // add the necessary information from p to the entry in the stable
  // this is very weird because the pstat values are in a table called stable
  // indexed by the pid of the process

  st->inuse[p->pid] = 1; // whether this slot of the process table is in use (1 or 0)
  st->tickets[p->pid] = 10; // the number of tickets this process has
  st->pid[p->pid] = p->pid; // the PID of each process
  st->ticks[p->pid] = 0; // the number of ticks each process has accumulated

  
  // print from the stable entry of this process
  
/*   cprintf ("\nAfter Allproc edited the statistics table with st pointer."); 
  cprintf ("\nProcess In Use Bit: %d", st->inuse[p->pid]);
  cprintf ("\nNumber of tickets: %d", st->tickets[p->pid]); 
  cprintf ("\nProcess ID: %d", st->pid[p->pid]); 
  cprintf ("\nTicks so far : %d", st->ticks[p->pid]);   
  cprintf ("\nAllproc added the edited statistics to the s.table with the above information.\n"); */
  

 
 
  release(&ptable.lock);
  release(&stable.lock);
  
  // Allocate kernel stack if possible.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
	st->inuse[p->pid] = 0;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;
  
  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;
  
  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;


  return p;
}

// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];
  
  p = allocproc();
  acquire(&ptable.lock);
  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  p->state = RUNNABLE;
  release(&ptable.lock);
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  
  sz = proc->sz;
  if(n > 0){
    if((sz = allocuvm(proc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(proc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  proc->sz = sz;
  switchuvm(proc);
  return 0;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;

  // added for p3a
  struct pstat *st;
  st = stable.pstat; 
  

  // Allocate process.
  if((np = allocproc()) == 0)
    return -1;

  // Copy process state from p.
  if((np->pgdir = copyuvm(proc->pgdir, proc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
	// added for p3a
	st->inuse[np->pid] = 0;
    return -1;
  }
  np->sz = proc->sz;
  np->parent = proc;
  
  // p3a
  // set np tickets to the parents tickets
  np->tickets = proc->tickets;
  st->tickets[np->pid] = np->parent->tickets; // the number of tickets this process has
  

  
  *np->tf = *proc->tf;

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(proc->ofile[i])
      np->ofile[i] = filedup(proc->ofile[i]);
  np->cwd = idup(proc->cwd);
 
  pid = np->pid;
  np->state = RUNNABLE;
  safestrcpy(np->name, proc->name, sizeof(proc->name));
  

  return pid;
}

// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
void
exit(void)
{
  struct proc *p;
  int fd;
  // added for p3a
  //struct pstat *st;
  //st = stable.pstat;
  
  
  if(proc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(proc->ofile[fd]){
      fileclose(proc->ofile[fd]);
      proc->ofile[fd] = 0;
    }
  }

  iput(proc->cwd);
  proc->cwd = 0;

  acquire(&ptable.lock);
  
  // added for p3a
  //acquire(&stable.lock);
  
  // Parent might be sleeping in wait().
  wakeup1(proc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == proc){
      p->parent = initproc;
      if(p->state == ZOMBIE)
        wakeup1(initproc);
    }
  }

  // Jump into the scheduler, never to return.
  proc->state = ZOMBIE;
  // p3a
  //st->inuse[proc->pid] = 0; // whether this slot of the process table is in use (1 or 0)
  
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid;
  
  // added for p3a
  //struct pstat *st;
  //st = stable.pstat;
  //acquire(&stable.lock);
  
  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for zombie children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != proc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->state = UNUSED;
		// added for p3a
		//st->inuse[p->pid] = 0;
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        release(&ptable.lock);
		//release(&stable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || proc->killed){
      release(&ptable.lock);
	  //release(&stable.lock);
      return -1;
    }
	//release(&stable.lock);
    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(proc, &ptable.lock);  //DOC: wait-sleep
  }
}

int
myModulus (unsigned int x, int n)
{
	
	int q, p, m;
	q = x / n;
	p = q * n;
	m = x - p;
	
	return m;
}

int 
PRNG(int ceiling)
{
    // our initial starting seed is 5323
     int seed = 5323;
 
    // Take the current seed and generate a new value from it
    // Due to our use of large constants and overflow, it would be
    // hard for someone to casually predict what the next number is
    // going to be from the previous one.
    seed = 83274519 * seed + 2378203;
 
    // Take the seed and return a value between 0 and ceiling
	int random = myModulus(seed, ceiling);
    return random;
}

// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void
scheduler(void)
{
  struct proc *p;
  int count = 0;
  long winningTicketAmount = 0;
  int ticket_aggregate = 0;
  int ceiling = 1;
  for(;;){
    // Enable interrupts on this processor.
    sti();
    ticket_aggregate=0;
  
    winningTicketAmount = 0;
	count = 0;
    ticket_aggregate = 0;
  
    ticket_aggregate = lottery_Total();
	if
		(ticket_aggregate == 0){
		ceiling = 1;
		}
	else{
		ceiling = ticket_aggregate;
	}
	
	winningTicketAmount = PRNG(ceiling);
    //winningTicketAmount = mod(pseudo_rand(seed), ticket_aggregate);
	//cprintf("\nWinning amount threshold is: %d", ticket_aggregate);
    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
	  
      if(p->state != RUNNABLE)
        continue;

	  // count starts and 0
	  if(count + p->tickets < winningTicketAmount){
		  count+=p->tickets;
		  continue;
	  }
      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      proc = p;
      switchuvm(p);
      p->state = RUNNING;
      swtch(&cpu->scheduler, proc->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      proc = 0;
    }
    release(&ptable.lock);

  }
}

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state.
void
sched(void)
{
  int intena;

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(cpu->ncli != 1)
    panic("sched locks");
  if(proc->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = cpu->intena;
  swtch(&proc->context, cpu->scheduler);
  cpu->intena = intena;
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  acquire(&ptable.lock);  //DOC: yieldlock
  proc->state = RUNNABLE;
  
  sched();
  release(&ptable.lock);
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{

  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);
  
  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  if(proc == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");


  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }

  // Go to sleep.
  proc->chan = chan;
  proc->state = SLEEPING;

  sched();

  // Tidy up.
  proc->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
      p->state = RUNNABLE;
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
	    p->state = RUNNABLE;
        
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}

// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  int i;
  struct proc *p;
  char *state;
  uint pc[10];
  
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
    cprintf("%d %s %s", p->pid, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
}
