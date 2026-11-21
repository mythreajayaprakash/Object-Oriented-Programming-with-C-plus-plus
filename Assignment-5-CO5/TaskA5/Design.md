# Task A5 – Recovery, rethrowing and RAII

Catch close to the layer that can add useful context or recover. A service boundary may log an exception and use `throw;` to preserve its dynamic type. The top-level application catches known billing errors and reports a clear message to the user; a final `catch(...)` can prevent an exception from escaping the program boundary.

Stack unwinding destroys automatic objects in reverse construction order as an exception leaves scopes. RAII objects such as `std::string`, `std::vector`, `std::unique_ptr` and file streams release resources in their destructors. Manual `delete` in every catch block duplicates cleanup and creates leak paths when new exceptions are added.

`throw;` rethrows the currently handled exception. `throw e;` throws a new exception object based on the static type of `e` and can slice a derived exception caught through a base reference.
