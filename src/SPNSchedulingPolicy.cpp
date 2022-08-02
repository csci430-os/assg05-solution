/** @file SPNSchedulingPolicy.hpp
 * @brief SPNSchedulingPolicy class implementation file
 *
 * @author Student Name
 * @note   cwid: 123456
 * @date   Fall 2019
 * @note   ide:  g++ 8.2.0 / GNU Make 4.2.1
 *
 * Implementation file for our SPNSchedulingPolicy class.  The
 * SPNSchedulingPolicy class is an abstract base class that defines the
 * interface for implementing different job scheduling policies.
 * Basically any scheduling policy needs to be notified when a
 * newProcess() arrives, a process runs a runCpuCycle(), and when a
 * process finished().  The main method of this stategy abstraction is
 * the dispatch() method, which is called by the scheduling simulator
 * whenever the cpu is idle, and the scheduling policy needs to make a
 * decision.
 */
#include "SPNSchedulingPolicy.hpp"
#include <queue>

using namespace std;

/**
 * @brief constructor
 *
 * The basic constructor is called by the PagingSystem when setting up/creating
 * the paging scheme to use for a simulation.  We keep track of the paging system
 * instance we are associated with, so we can call the paging system to get
 * needed information to make replacment decisions.
 */
SPNSchedulingPolicy::SPNSchedulingPolicy()
  : SchedulingPolicy()
{
  sys = NULL;
  resetPolicy();
}

/**
 * @brief destructor
 *
 * Define a concrete destructor.  This destructor has no work to do, but
 * base classes that need a destructor should define their own.
 */
SPNSchedulingPolicy::~SPNSchedulingPolicy() {}

/** new process
 * Handle new process arrivals.  When a new process arrives it is
 * put in a ready to run state.  We add it to the end of our
 * ready queue.
 *
 * @param pid The process identifier (pid) of the newly arriving
 *   process that should now be managed by this policy.
 */
void SPNSchedulingPolicy::newProcess(Pid pid)
{
  // put the new process on the end of the ready queue
}

/** dispatch a process
 * When the cpu is idle, the scheduling simulator calls this
 * method of the policy object to select which process to
 * dispatch and schedule and run next on the cpu.  The
 * First Come First Serve (SPN) policy simply selects the
 * process that has been waiting the longest, and thus was the
 * first to "come" into the system.
 *
 * @returns pid Returns the process identifier of the process
 *   we select to run next.
 */
Pid SPNSchedulingPolicy::dispatch()
{
  return IDLE;
}

/**
 * @brief preemption
 *
 * Determine if current running processes needs to be preempted.
 * SPN is a non-preempting policy, so we have nothing to
 * do here but always return false to mean we shouldn't preempt
 * now.
 *
 * @returns bool Always returns false to indicate SPN never
 *   preempts.
 */
bool SPNSchedulingPolicy::preempt()
{
  return false;
}

/** reset policy
 * Reset or initialize the scheduling policty to an initial state,
 * in preparation for beginning a simulation.  For SPN this means
 * we want to clear out the ready queue and make sure it is
 * empty to begin with.
 */
void SPNSchedulingPolicy::resetPolicy()
{
  // make sure the queue is empty, swap a queue with a known
  // empty queue will free up the old queue and ensure we start
  // with an empty one.
}
