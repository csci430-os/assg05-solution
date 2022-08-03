/** @file HRRNSchedulingPolicy.hpp
 * @brief HRRNSchedulingPolicy class implementation file
 *
 * @author Student Name
 * @note   cwid: 123456
 * @date   Summer 2022
 * @note   ide:  g++ 8.2.0 / GNU Make 4.2.1
 *
 * Implementation file for our HRRNSchedulingPolicy class.  The
 * HRRNSchedulingPolicy is a concrete child class implementation of
 * a SchedulingPolicy strategy.  This policy implements the
 * non preemptive highest response ratio next (HRRN)
 * scheduling policy.
 */
#include "HRRNSchedulingPolicy.hpp"
#include <climits>
#include <queue>
#include <iostream>

using namespace std;


/**
 * @brief constructor
 *
 * The default constructor is called when a HRRN policy instance
 * is created.  This policy has no system/meta parameters,
 * so no parameters are needed when creating the policy instance.
 */
HRRNSchedulingPolicy::HRRNSchedulingPolicy()
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
HRRNSchedulingPolicy::~HRRNSchedulingPolicy()
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
void HRRNSchedulingPolicy::newProcess(Pid pid)
{
  // get a reference to the process to add to the priority queue
  Process* processTable = sys->getProcessTable();
  Process* newProcess = &processTable[pid];

  // add this process to the processQueue priority queue
  processQueue.push(newProcess);
}


/** 
 * @brief dispatch a process
 *
 * When the cpu is idle, the scheduling simulator calls this
 * method of the policy object to select which process to
 * dispatch and schedule and run next on the cpu.  The HRRN
 * policy selects the ready process in the process priority
 * queue with the current highest response ratio.
 *
 * @returns Pid Returns the process identifier of the process
 *   we select to run next.
 */
Pid HRRNSchedulingPolicy::dispatch()
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
    // KLUDGE: this is a kludge, need to fix it, but take out all processes and reinsert
    // them so the heap reorders using current response ratio
    priority_queue<Process*, vector<Process*>, HighestResponseRatioNext> q;
    while (not processQueue.empty())
    {
      q.push(processQueue.top());
      processQueue.pop();
    }
    swap(q, processQueue);

    Process* process = processQueue.top();
    processQueue.pop();
    return process->pid;
  }
}


/**
 * @brief preemption
 *
 * HRRN is a non preemptive policy, so simply always return
 * false if asked to preempt.
 *
 * @returns bool Return true if a new process is arriving at the
 *   current time.
 */
bool HRRNSchedulingPolicy::preempt()
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
void HRRNSchedulingPolicy::resetPolicy()
{
}
