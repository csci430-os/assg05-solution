/** @file SRTSchedulingPolicy.hpp
 * @brief SRTSchedulingPolicy class API/Includes
 *
 * @author Student Name
 * @note   cwid: 123456
 * @date   Summer 2022
 * @note   ide:  g++ 8.2.0 / GNU Make 4.2.1
 *
 * Header include file for our SRTSchedulingPolicy class.
 * This is a concrete child class implementation of a
 * SchedulingPolicy strategy.  This policy implements a
 * premptive version of selecting the shortest process,
 * by preempting on new process arrivals and then selecting
 * process with shortest remaining time to run.
 */
#ifndef SRTSCHEDULING_POLICY_HPP
#define SRTSCHEDULING_POLICY_HPP

#include "SchedulingSystem.hpp"
#include <string>
#include <queue>

// forward declaration needed for circular references
class SchedulingSystem;

using namespace std;


/** @class ShortestRemainingTimeNext
 * @brief Shortest Remaining Time Next priority_queue comparator 
 *
 * A wrapper class to create a comparison of remaining time
 * for process objects.  The operator is called by a 
 * stl priority_queue to determine priority of processes.  We
 * order processes by their remaining time in order to implement
 * selecting the shortest remaining time process next from
 * the priority queue when we need to dispatch.
 */
struct ShortestRemainingTimeNext
{
  bool operator()(const Process& lhs, const Process& rhs) const
  {
    return rhs.remainingTime < lhs.remainingTime;
  }
};

/** @class SRTSchedulingPolicy
 * @brief SRTSchedulingPolicy abstract base class
 *
 * This class defines the interface or API for the helper scheduling
 * policy instance.
 */
class SRTSchedulingPolicy : public SchedulingPolicy
{
private:
  /// @brief The list of waiting processes currently in the system
  priority_queue<Process, vector<Process>, ShortestRemainingTimeNext> processQueue;

public:
  SRTSchedulingPolicy();

  // virtual function, concrete subclasses can override if needed
  virtual ~SRTSchedulingPolicy();

  // virtual functions, concrete subclasses must implement
  void newProcess(Pid pid);
  Pid dispatch();
  bool preempt();
  void preemptRunningProcess();
  void resetPolicy();
};


#endif // SRTSCHEDULING_POLICY_HPP
