# Fibonacci, but with THREADS!!!

Yes.
We're getting crazy up in here.
You never thought it would happen.
But, oh, it is!
Fibonacci with threads; it's on.

- **TODO 1:**
	Write the `thread_onacci` function to create a thread for each recursive call of `thread_onacci`.
	Note, this function is *not* just calling `fib`.
	It is implementing the logic for fibonacci, but creating new threads.
- **Question 1:**
	Observe the relative overheads for function calls, forks, and threads.
	Do they match up with your assumptions?
	Why do they have the relative costs that they do?
