CS3790 Lab Assignment3---The server that computes the prime number by communication of pipe
Zhihong Liu(5088806)
25/10/2024

1.The source code file should be compiled under UNIX environment
2.The server will ignore the "empty user request",and the client needs to be restarted manually

The server will create a named pipe and will wait for a request to sent over thenamed pipe. The user request will have the form RANGE XX YY, where XX is thelower bound and YY is the upper bound. The server will then proceed to compute allprimes in that range and return them to the process that made the request. If therequest is malformed, the server will return a "malformed request" message. requestscan come from any number of processes.
