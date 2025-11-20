**Problem Statement**

It is necessary to perform data processing that consists of executing certain computational steps, hereafter simply referred to as computations.

All computations are implemented by a library (developed by a subcontractor) as synchronous functions and can be conditionally divided into "slow" and "fast" ones.

For example, data requests from external resources will take longer to execute than simple local data processing. Therefore, external data requests can be considered "slow", while local simple data processing that operates in linear time can be considered "fast".

There is a certain order between computations. Some computations require that other computations have already been completed and their results obtained. If computation B needs to wait for computation A to complete, we will say that B depends on A. By default, we will assume that if C depends on B, and B depends on A, then C also depends on A (i.e., the "depends on" relation is transitive). If there are no dependencies between computations A and B, they can be executed in any order (first A then B, or vice versa) or concurrently.

Let the notation A(B,C) denote that computation A depends on computations B and C.

For each variant, the following is specified:
- The list of computations that need to be performed;
- Which of these computations are "slow" (the rest are "fast");
- Dependencies between computations (those obtained by transitivity may not be listed).

Develop an execution scheme (what executes in which thread and in what sequence) that optimally performs the entire complex of computations specified in the variant.

By optimality, it is meant that:
1) The total execution time should be minimal on average;
We assume that "slow" computations take 7 seconds on average to execute, while "fast" ones take 1 second. We also assume that the main time consumption comes from executing computations, and we neglect auxiliary operations.
2) While achieving minimal execution time, as few threads as possible should work concurrently;
3) Subject to the previous conditions, it is desirable to minimize the number of thread launches (this will vary depending on the specific variant).

Write a function `work` that performs computations according to the developed scheme and, when everything is completed, outputs the execution time in seconds and the message "Work is done!" to the console. To simplify modeling, assume that:
1) A "slow" computation `name` is executed by the function `slow(const string& name)`, which first sleeps for 7 seconds and then outputs `name` to the console.
2) A "fast" computation `name` is executed by the function `quick(const string& name)`, which first sleeps for 1 second and then outputs `name` to the console.
Instead of these two functions, you can create one universal function that additionally accepts the duration in seconds.
Remember to synchronize the output stream; `osyncstream` can help.

To launch computations in another thread, you should use facilities from the `<future>` library. Using facilities from other "asynchronous" standard or third-party libraries is prohibited.

Write a program that demonstrates the work of the `work` function.

**Submission Requirements:**
Submit: code, screenshot with execution results, a diagram schematically showing the sequence of computations, distribution of computations across threads, and synchronization points (either a photo of a handwritten version or as a diagram in graphic format).

**Example:**
It is necessary to perform computations A, B, C, D. B is "slow". Dependencies are given: B(A), D(B,C).
From the explicitly given dependencies B(A), D(B,C), there is also an implicit dependency D(A), which follows from the previous ones, therefore D and A cannot be executed concurrently.

If each computation is launched in a separate thread with appropriate synchronization, this would minimize time. However, this would launch 5 threads concurrently (main thread plus threads for A, B, C, D). The number of threads here can clearly be minimized (to 2 threads) while maintaining the same overall task execution time (approximately 1+7+1 seconds on average). Moreover, besides the main execution thread, it is sufficient to launch only one additional thread.

**Variant No. 20**
All computations: A1, A2, A3, A4, B1, B2, C
"Slow" computations: A1, A3
Dependencies: B1(A1,A2), C(B1,B2)
