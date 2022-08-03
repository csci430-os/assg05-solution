/** @file RRSchedulingPolicy.hpp
 * @brief RRSchedulingPolicy class implementation file
 *
 * @author Student Name
 * @note   cwid: 123456
 * @date   Fall 2019
 * @note   ide:  g++ 8.2.0 / GNU Make 4.2.1
 *
 * Implementation file for our RRSchedulingPolicy class.  The
 * RRSchedulingPolicy class is an abstract base class that defines the
 * interface for implementing different job scheduling policies.
 * Basically any scheduling policy needs to be notified when a
 * newProcess() arrives, a process runs a runCpuCycle(), and when a
 * process finished().  The main method of this stategy abstraction is
 * the dispatch() method, which is called by the scheduling simulator
 * whenever the cpu is idle, and the scheduling policy needs to make a
 * decision.
 */
#include "RRSchedulingPolicy.hpp"
#include <queue>

using namespace std;


/**
 * @brief constructor
 *
 * The default constructor is called by the PagingSystem when setting up/creating
 * the paging scheme to use for a simulation.  We keep track of the paging system
 * instance we are associated with, so we can call the paging system to get
 * needed information to make replacment decisions.
 *
 * @param quantum The system time slice quantum to use for round robin
 *   preemption.  This defaults to 1 if not specified.
 */
RRSchedulingPolicy::RRSchedulingPolicy(int quantum)
  : SchedulingPolicy()
{
  // set the system time slice quantum
  this->quantum = quantum;

  sys = NULL;
  resetPolicy();
}


/**
 * @brief destructor
 *
 * Define a concrete destructor.  This destructor has no work to do, but
 * base classes that need a destructor should define their own.
 */
RRSchedulingPolicy::~RRSchedulingPolicy()
{
}


/** new process
 * Handle new process arrivals.  When a new process arrives it is
 * put in a ready to run state.  We add it to the end of our
 * ready queue.
 *
 * @param pid The process identifier (pid) of the newly arriving
 *   process that should now be managed by this policy.
 */
void RRSchedulingPolicy::newProcess(Pid pid)
{
  // put the new process on the end of the ready queue
  readyQueue.push(pid);
}


/** dispatch a process
 * When the cpu is idle, the scheduling simulator calls this
 * method of the policy object to select which process to
 * dispatch and schedule and run next on the cpu.  The
 * round robin (RR) policy implements a time slicing
 * discipline.  Scheduling is FCFS, but processes
 * are given a time slice quantum, and are preempted and
 * returned to the end of the ready queue when their time
 * slice expires.
 *
 * @returns pid Returns the process identifier of the process
 *   we select to run next.
 */
Pid RRSchedulingPolicy::dispatch()
{
  // make sure the ready queue is not empty, if it is we
  // can't dispatch at this time
  if (readyQueue.empty())
  {
    return IDLE;
  }
  // otherwise pop the front item and return it
  else
  {
    // get the next process to run
    currentProcess = readyQueue.front();
    readyQueue.pop();

    // process should start out with 0 time slice quantum used so far
    runningTimeSliceQuantum = 0;

    return currentProcess;
  }
}


/**
 * @brief preemption
 *
 * Determine if current running processes needs to be preempted.
 * FCFS is a non-preempting policy, so we have nothing to
 * do here but always return false to mean we shouldn't preempt
 * now.
 *
 * @returns bool Always returns false to indicate FCFS never
 *   preempts.
 */
bool RRSchedulingPolicy::preempt()
{
  // increment the running processes time slice quantum
  runningTimeSliceQuantum++;

  // we are called to check whether we should preempt every cycle.
  // If process has equaled or exceeded its time slice quantum,
  // then preempt it.  We fist put it back on the end
  // of the ready queue, then return true to preempt it.
  if (runningTimeSliceQuantum >= quantum)
  {
    readyQueue.push(currentProcess);
    currentProcess = IDLE;

    return true;
  }
  // otherwise let the process keep running
  else
  {
    return false;
  }
}


/** reset policy
 * Reset or initialize the scheduling policty to an initial state,
 * in preparation for beginning a simulation.  For FCFS this means
 * we want to clear out the ready queue and make sure it is
 * empty to begin with.
 */
void RRSchedulingPolicy::resetPolicy()
{
  // reset any remaining time slice back to 0
  runningTimeSliceQuantum = 0;
  currentProcess = IDLE;

  // make sure the queue is empty, swap a queue with a known
  // empty queue will free up the old queue and ensure we start
  // with an empty one.
  queue<Pid> empty;
  swap(readyQueue, empty);
}