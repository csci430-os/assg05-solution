/** @file SPNSchedulingPolicy.hpp
 * @brief SPNSchedulingPolicy class implementation file
 *
 * @author Student Name
 * @note   cwid: 123456
 * @date   Fall 2019
 * @note   ide:  g++ 8.2.0 / GNU Make 4.2.1
 *
 * Implementation file for our SPNSchedulingPolicy class.  The
 * SPNSchedulingPolicy is a concrete child class implementation of
 * a SchedulingPolicy strategy.  This policy implements the
 * non-preemptive shortest process next (SPN) policy.
 */
#include "SPNSchedulingPolicy.hpp"
#include <climits>
#include <queue>
#include <iostream>

using namespace std;


/**
 * @brief constructor
 *
 * The default constructor is called when a SPN policy instance
 * is created.  This policy has not system/meta parameters,
 * so no parameters are needed when creating the policy instance.
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
SPNSchedulingPolicy::~SPNSchedulingPolicy()
{
}


/** 
 * @brief new process
 *
 * Handle new process arrivals.  When a new process arrives we
 * put it in a list of waiting processes, so we can search the
 * list to determine the shortest process currently waiting
 * when needed.
 *
 * @param pid The process identifier (pid) of the newly arriving
 *   process that should now be managed by this policy.
 */
void SPNSchedulingPolicy::newProcess(Pid pid)
{
  // get a reference to the process to add to the priority queue
  Process* processTable = sys->getProcessTable();
  Process newProcess = processTable[pid];

  // add this process to the processQueue priority queue
  processQueue.push(newProcess);
}


/** 
 * @brief dispatch a process
 *
 * When the cpu is idle, the scheduling simulator calls this
 * method of the policy object to select which process to
 * dispatch and schedule and run next on the cpu.  The SPN
 * policy has to search the waiting processes to determine
 * which process that is waiting has the shorted service
 * time.
 *
 * @returns Pid Returns the process identifier of the process
 *   we select to run next.
 */
Pid SPNSchedulingPolicy::dispatch()
{
  // make sure the process queue is not empty, if it is return IDLE to
  // indicate we can't dispatch at this time
  if (processQueue.empty())
  {
    return IDLE;
  }
  // otherwise dispatch shortest process from the processQueue priority queue
  // as next process to run
  else
  {
    Process process = processQueue.top();
    processQueue.pop();
    return process.pid;
  }
}


/**
 * @brief preemption
 *
 * SPN is a non-preemptive policy.  So we always return false
 * to indicate we should not preempt.
 *
 * @returns bool Always returns false to indicate SPN never
 *   preempts.
 */
bool SPNSchedulingPolicy::preempt()
{
  return false;
}


/** 
 * @brief reset policy
 *
 * Reset or initialize the scheduling policty to an initial state,
 * in preparation for beginning a simulation.  For FCFS this means
 * we want to clear out the ready queue and make sure it is
 * empty to begin with.
 */
void SPNSchedulingPolicy::resetPolicy()
{
}
