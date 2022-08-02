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
 * non-preemptive SPN
 */
#ifndef SPNSCHEDULING_POLICY_HPP
#define SPNSCHEDULING_POLICY_HPP

#include "SchedulingSystem.hpp"
#include <queue>
#include <string>

// forward declaration needed for circular references
class SchedulingSystem;

using namespace std;

/// @brief More descriptive name for things that hold process
///   identifiers.  We use int values for our processes identifiers
///   in this simulation.
typedef int Pid;

/** @class SPNSchedulingPolicy
 * @brief SPNSchedulingPolicy abstract base class
 *
 * This class defines the interface or API for the helper page
 * replacement scheme.  A PagingSystem simulation will instanciate
 * a derived class of this API, and will expect it to implement the
 * interface defined by this abstract base class.
 */
class SPNSchedulingPolicy : public SchedulingPolicy
{
private:
  /// @brief The ready queue for the SPN policy, keeps track of
  ///   which process arrived first for dispatching.
  queue<Pid> readyQueue;

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