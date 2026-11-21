# Task A2 – Runtime binding

## Early vs late binding
A non-virtual call is resolved using the static type at compile time. A virtual call such as `Bill* b = new OutPatientBill(...); b->total()` is dispatched at run time using the object's dynamic type, so `OutPatientBill::total()` executes.

## Conceptual vtable sketch
```text
Bill vtable:
  total -> pure virtual slot
  type  -> pure virtual slot
  ~Bill -> virtual destructor

OutPatientBill vtable:
  total -> OutPatientBill::total
  type  -> OutPatientBill::type
  ~Bill -> OutPatientBill destructor sequence

InPatientBill vtable:
  total -> InPatientBill::total
  type  -> InPatientBill::type
  ~Bill -> InPatientBill destructor sequence
```
A Bill pointer refers to a derived object. Its hidden vptr identifies the derived vtable; the virtual call follows the corresponding slot. This is a conceptual model; exact ABI layout is compiler-specific.

## Why virtual destructor?
Deleting a derived object through `Bill*` must run the derived destructor before the base destructor. Without a virtual base destructor, that delete has undefined behaviour.

## Alternative
Using `dynamic_cast` tests for each possible derived type costs up to k type checks for k bill types per bill, rather than one virtual dispatch. The object generally stores a vtable pointer (implementation-dependent size) for virtual dispatch.
