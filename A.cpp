/* Link: https://youtu.be/HjIpFuQpCkM?si=n2p_GcR9Rgp-Yk74 */

/* Notes:
   Illusion of Concurrency: When there is a single core , which 
handles multiple tasks at once from a single task queue

   Hardware level Concurrency: 
   Single Processor Dual Core:
   There will be two task queues so both queues can be 
   worked on parallely

   Multiple Processor and multiple cores:
   These will use Hardware + Illusion Concurrency

   How is concurrency performed:
   1. using processes
   2. using threads
   Disadvantage of threads: They use shared memory so 
   context switching is easier. But if one thread corrupts, 
   all threads will get corrupt and thus whole process

   A process has its own memory meaning it will store 
   Processor registers, Program counters, Stack pointers, 
   memory pages 
   Interprocess Communication is harder
   Isliye Multithreading is commonly used
*/

