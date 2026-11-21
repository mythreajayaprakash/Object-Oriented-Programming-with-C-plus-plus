# Task A4 – Exception strategy

## Error catalogue
- Negative consultation, room, procedure, package or emergency charge: `InvalidCharge`.
- Claim exceeds available insurance cover: `ClaimError`.
- Unknown government package: `UnknownPackage`.
- Missing patient/bill record: `MissingRecord`.
- Allocation failure: standard `std::bad_alloc`.

## Hierarchy
```text
std::exception
  std::runtime_error
    BillingError
      InvalidCharge
      ClaimError
      UnknownPackage
      MissingRecord
```
Functions that validate amounts, calculate claims or look up packages may throw. Constructors may throw if invariants are invalid. Destructors should not throw: an exception escaping a destructor during stack unwinding can terminate the program. Destructors and cleanup functions should be `noexcept` where appropriate.

## Return-code alternative
A function could return a status enum plus an output parameter/error message. The normal path has predictable branching and avoids exception propagation; the error path requires every caller to inspect and forward status. Extra result/status storage is generally O(1) per call. Exceptions separate normal flow from exceptional errors but incur handling/unwinding cost when thrown.
