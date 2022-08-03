/** @file SPNSchedulingPolicy.hpp
 * @brief SPNSchedulingPolicy class API/Includes
 *
 * @author Student Name
 * @note   cwid: 123456
 * @date   Fall 2019
 * @note   ide:  g++ 8.2.0 / GNU Make 4.2.1
 *
 * Header include file for our SPNSchedulingPolicy class.
 * This is a concrete child class implementation of a
 * SchedulingPolicy strategy.  This policy implements a
 * non-preemptive shortest process next (SPN) policy.
 */
#ifndef SPNSCHEDULING_POLICY_HPP
#define SPNSCHEDULING_POLICY_HPP

#include "SchedulingSystem.hpp"
#include <string>
#include <queue>

// forward declaration needed for circular references
class SchedulingSystem;

using namespace std;

/** @class ShortestProcessNext
 * @brief Shortest Process Next priority_queue comparator 
 *
 * A wrapper class to create a comparison of service time
 * for process objects.  The operator is called by a 
 * stl priority_queue to determine priority of processes.  We
 * order processes by their service time in order to implement
 * selecting the shortest process next from the priority queue
 * when we need to dispatch.
 */
struct ShortestProcessNext
{
  bool operator()(const Process& lhs, const Process& rhs) const
  {
    return rhs.serviceTime < lhs.serviceTime;
  }
};

/** @class SPNSchedulingPolicy
 * @brief SPNSchedulingPolicy abstract base class
 *
 * This class defines the interface or API for the helper scheduling
 * policy instance.
 */
class SPNSchedulingPolicy : public SchedulingPolicy
{
private:
  /// @brief The list of waiting processes currently in the system
  priority_queue<Process, vector<Process>, ShortestProcessNext> processQueue;

public:
  SPNSchedulingPolicy();

  // virtual function, concrete subclasses can override if needed
  virtual ~SPNSchedulingPolicy();

  // virtual functions, concrete subclasses must implement
  void newProcess(Pid pid);
  Pid dispatch();
  bool preempt();
  void resetPolicy();
};


#endif // SPNSCHEDULING_POLICY_HPP
