/** @file HRRNSchedulingPolicy.hpp
 * @brief HRRNSchedulingPolicy class API/Includes
 *
 * @author Student Name
 * @note   cwid: 123456
 * @date   Summer 2022
 * @note   ide:  g++ 8.2.0 / GNU Make 4.2.1
 *
 * Header include file for our HRRNSchedulingPolicy class.
 * This is a concrete child class implementation of a
 * SchedulingPolicy strategy.  This policy implements a
 * the non preemptive highest response ration next
 * (HRRN) scheduling policy.
 */
#ifndef HRRNSCHEDULING_POLICY_HPP
#define HRRNSCHEDULING_POLICY_HPP

#include "SchedulingSystem.hpp"
#include <string>
#include <queue>

// forward declaration needed for circular references
class SchedulingSystem;

using namespace std;


/** @class HighestResponseRatioNext
 * @brief Highest Response Ratio Next priority_queue comparator 
 *
 * A wrapper class to create a comparison of response ratio
 * for process objects.  The operator is called by a 
 * stl priority_queue to determine priority of processes.  We
 * order processes by their response ratio in order to implement
 * selecting the shortest remaining time process next from
 * the priority queue when we need to dispatch.
 */
struct HighestResponseRatioNext
{
  bool operator()(const Process* lhs, const Process* rhs) const
  {
    return lhs->responseRatio < rhs->responseRatio;
  }
};

/** @class HRRNSchedulingPolicy
 * @brief HRRNSchedulingPolicy abstract base class
 *
 * This class defines the interface or API for the helper scheduling
 * policy instance.
 */
class HRRNSchedulingPolicy : public SchedulingPolicy
{
private:
  /// @brief The list of waiting processes currently in the system
  priority_queue<Process*, vector<Process*>, HighestResponseRatioNext> processQueue;

public:
  HRRNSchedulingPolicy();

  // virtual function, concrete subclasses can override if needed
  virtual ~HRRNSchedulingPolicy();

  // virtual functions, concrete subclasses must implement
  void newProcess(Pid pid);
  Pid dispatch();
  bool preempt();
  void resetPolicy();
};


#endif // HRRNSCHEDULING_POLICY_HPP
