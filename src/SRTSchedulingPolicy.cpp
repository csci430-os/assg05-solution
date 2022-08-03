/** @file SRTSchedulingPolicy.hpp
 * @brief SRTSchedulingPolicy class implementation file
 *
 * @author Student Name
 * @note   cwid: 123456
 * @date   Summer 2022
 * @note   ide:  g++ 8.2.0 / GNU Make 4.2.1
 *
 * Implementation file for our SRTSchedulingPolicy class.  The
 * SRTSchedulingPolicy is a concrete child class implementation of
 * a SchedulingPolicy strategy.  This policy implements the
 * preemptive version of selecting the shortest process by
 * preempting on new process arrivals and then selecting process
 * with shortest remaining time to run.
 */
#include "SRTSchedulingPolicy.hpp"
#include <climits>
#include <queue>
#include <iostream>

using namespace std;


/**
 * @brief constructor
 *
 * The default constructor is called when a SRT policy instance
 * is created.  This policy has no system/meta parameters,
 * so no parameters are needed when creating the policy instance.
 */
SRTSchedulingPolicy::SRTSchedulingPolicy()
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
SRTSchedulingPolicy::~SRTSchedulingPolicy()
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
void SRTSchedulingPolicy::newProcess(Pid pid)
{
  // get a reference to the process to add to the priority queue
  Process* processTable = sys->getProcessTable();
  Process newProcess = processTable[pid];

  // add this process to the processQueue priority queue
  processQueue.push(newProcess);

  // then preempt the current running process to get it onto
  // the priority queue after the new process
  preemptRunningProcess();  
}


/** 
 * @brief dispatch a process
 *
 * When the cpu is idle, the scheduling simulator calls this
 * method of the policy object to select which process to
 * dispatch and schedule and run next on the cpu.  The SRT
 * policy has to search the waiting processes to determine
 * which process that is waiting has the shortest remaining
 * time.
 *
 * @returns Pid Returns the process identifier of the process
 *   we select to run next.
 */
Pid SRTSchedulingPolicy::dispatch()
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
 * SRT is a preemptive policy.  So we need to detect when a
 * new process arrives, and cause a preemption to occur.
 * We also need to recalculate the remaining time for the current
 * running process, and add it back to the processQueue
 * priority queue.
 *
 * @returns bool Return true if a new process is arriving at the
 *   current time.
 */
bool SRTSchedulingPolicy::preempt()
{
  // SRT preempts on process arrival, ask sys if process is arriving
  return sys->didProcessArrive();
}

/**
 * @brief preempt the running process
 *
 * Do the actual work of preempting the current running process.  We want to
 * handle putting the preempted process back onto the process queue before the
 * new process is added, to get same results as our textbook.  So this
 * method is called by newProcess() to do work of preempting the current
 * running process.
 */
void SRTSchedulingPolicy::preemptRunningProcess()
{
  // only preempt if there is an actual process running
  if (sys->isCpuIdle())
  {
    // if cpu is idle, nothing to do
    return;
  }

  // otherwise preempt the current running process
  // get the current running process
  Pid runningPid = sys->getRunningPid();
  Process* processTable = sys->getProcessTable();
  Process& runningProcess = processTable[runningPid];
  
  // put this process back onto the process queue
  processQueue.push(runningProcess);
}

/** 
 * @brief reset policy
 *
 * Reset or initialize the scheduling policty to an initial state,
 * in preparation for beginning a simulation.  For FCFS this means
 * we want to clear out the ready queue and make sure it is
 * empty to begin with.
 */
void SRTSchedulingPolicy::resetPolicy()
{
}
