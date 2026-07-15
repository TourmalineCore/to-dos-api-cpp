# API Performance Testing Research

## Test Types

Several types of performance tests exist, each answering a different question about API behavior under load:
| Test type                | Purpose                                                                                                                   |
| ------------------------ | ------------------------------------------------------------------------------------------------------------------------- |
| Load testing             | Checks the behavior of the API with a stable expected workload.                                                           |
| Stress testing           | Gradually increases the load until the system fails or fails.                                                             |
| Spike testing            | Checks the behavior during a sudden, short burst of traffic significantly exceeding the normal level.                     |
| Soak / endurance testing | Provides stable boot over a long period of time to detect memory leaks, connections, and gradual performance degradation. |
| Scalability testing      | Measures how performance changes as new instances or resources are added.                                                 |

### Load Testing

Load testing checks whether the API meets performance expectations with a stable workload.

Example:
* 50 virtual users.
* Stable loading for 10 minutes.
* Run representative API read, write, and authentication streams.
* Check the functionality and performance thresholds.

Example of threshold values:
* Frequency of failed requests: less than 1%.
* Response time: less than 300 ms.
* There are no unexpected timeouts or connection errors.
* Resources are used less than 100%.

### Stress testing

Stress testing gradually increases the load until the system reaches a state of degradation or failure.

Example:
* 10 virtual users.
* Increase the number of virtual users by 10-25 every 1-2 minutes.
* Continue until the failure criterion is reached.
* Reduce traffic and monitor API recovery.

The point of failure may be:
* the delay exceeds the set limit, for example, 1 second.
* The frequency of unsuccessful requests exceeds 5%.
* Timeouts or connection failures become permanent.
* The load on the processor, memory, database connections, or other dependencies is overloaded.
* The API becomes unavailable or does not recover after the load is reduced.

### Spike Testing
Spike testing checks whether the API can withstand a unexpected, short burst of traffic much higher than the normal download level.

Example:
* 20 virtual users.
* Instantly jump to 300–500 virtual users for 30–60 seconds.
* Drop to 20 virtual users.

### Soak / Endurance Testing

Endurance testing is performed under moderate, stable load over a long period of time to identify problems that only appear over time.

Example:

* 50-100 virtual users within 2-8 hours.
* Provide a realistic mix of read and write requests.

### Scalability Testing

Scalability testing measures how API performance changes when computing resources are added, i.e. it checks how efficiently the system scales horizontally (more instances per load balancer) or vertically (more CPU/RAM per instance).

Example:
* Capture the same test scenario and load profile (for example, a stress test with a gradual increase in RPS).
* Run the script on configuration A: 1 API instance.
* Run the same scenario on configuration B: 2 API instances behind the load balancer.
* If necessary, run the C: 4 instance configuration.

For each configuration, fix the maximum sustained RPS until the same failure criteria are reached as in the stress test (for example, error rate > 5%).

## Main Metrics

| Metric                                                       | What measures                                                               |
| ------------------------------------------------------------ | --------------------------------------------------------------------------- |
| Throughput, RPS                                              | Shows the number of requests processed per second.                          |
| Response time: average, p50, p95, p99, max                   | Shows typical latency, tail latency, and worst requests.                    |
| Success and failure rate                                     | Identifies the proportion of failed requests under load.                    |
| HTTP status distribution                                     | Separates expected client errors from server-side failures, especially 5xx. |
| Timeouts and connection errors                               | Detects overload, unavailable dependencies, and networking limits.          |
| Active virtual users                                         | Connects observed behavior to the applied load profile.                     |
| CPU usage                                                    | Helps identify CPU saturation in the API, database, or load generator.      |
| Memory usage                                                 | Helps detect excessive memory use, memory growth, and OOM conditions.       |
| Database connection-pool usage                               | Identifies connection exhaustion and waiting requests.                      |
| Database query latency and errors                            | Confirms whether the database is the limiting component.                    |

### p50, p95, p99 meaning

These are latency percentiles describing the distribution of response time, not a single average value:
* p50 (median) - half of all requests are completed faster than this value, and half are slower; this reflects the typical user experience.
* p95 - 95% of requests complete faster than this value, 5% slower; this reflects the experience of most users, including some slower ones.
* p99 - 99% of requests complete faster than this value, and only 1% are slower; this results in a worst-case scenario with latency averaging hide.

## Tool Comparison

**Karate (+ Gatling)**
Scripting via Gherkin .feature files reused for both functional and performance tests. 
Strengths: reuses existing API tests, full response assertions rather than just status codes, readable scenarios. 
Weaknesses: heavier setup (Java/Gatling), local load-generator throughput limited by the default thread pool.

**k6**
Scripting via JavaScript-based scripts. 
Strengths: CLI-first, lightweight, high generator throughput, strong CI/threshold support. 
Weaknesses: requires writing separate scripts. Weaker support for complex multi-step business flows compared to Gherkin-style scenarios. Large scripts can get harder to structure and read. Native reporting is minimal out of the box.

**JMeter**
Scripting via GUI-built or XML .jmx plans. 
Strengths: mature, large plugin ecosystem, visual test design. 
Weaknesses: XML format complicates code review, GUI unsuitable for real high load.

## Selection Criteria and Decision

The team already maintains functional API tests written in Karate for C++ API. Karate-Gatling can execute this same set of feature tests under concurrent load.

Given this existing investment, the decisive selection criterion is reuse of existing test scenarios: k6 and JMeter would each require writing new request flows from scratch, duplicating logic already implemented and maintained in Karate. Only Karate with Gatling integration allows the same .feature files to serve both functional and performance testing, which minimizes duplicated effort and keeps functional and performance checks in sync.

## Scope

* Use Karate with Gatling integration to run performance experiments against the C++ API and NestJS API.
* Load testing: validate API behavior under a stable, expected workload.
* Stress testing: increase load gradually to find the first degradation or failure point.
* Reuse existing Karate scenarios where they are safe for parallel execution.
* Add performance-specific scenarios only where existing tests are unsuitable, for example when they share mutable test data.
* Run APIs manually outside the load-testing environment.
* Execute tests locally and collect Gatling reports.

## Out of Scope
* Soak / endurance testing: excluded, since it requires long-running tests to detect memory leaks, connection leaks, and gradual degradation, which does not fit the task time.
* Scalability testing: excluded, since tests run on one laptop. Multiple local API instances would share the same CPU, memory, disk, and network resources, so results would not represent real horizontal scalability. It can be done with CI/CD integration but its not fit the task time.
* Spike testing: excluded from this iteration. Not required for the immediate goal of finding the failure point via gradual load increase.
