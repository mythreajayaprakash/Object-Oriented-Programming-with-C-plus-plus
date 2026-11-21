# Task A1 – Design the polymorphic Bill hierarchy

## Common interface
Every bill needs a patient identifier/name, a bill identifier, `total() const`, `type() const` and `print() const`. `total()` and `type()` are pure virtual because each bill category calculates its own amount. `print()` can be a shared virtual/non-virtual convenience operation that calls the virtual functions.

## UML-style diagram
```text
                 <<abstract>> Bill
        ------------------------------------
        # patient : string
        # billId  : string
        ------------------------------------
        + total() : double {pure virtual}
        + type()  : string {pure virtual}
        + print() : void
        + ~Bill() {virtual}
             /          |          |           \
            /           |          |            \
 OutPatientBill  InPatientBill  DayCareBill  EmergencyBill
 total() override total() override total() override total() override
 type() override  type() override  type() override  type() override
```

## Pseudocode – total all bills
```text
ALGORITHM CalculateDayTotal
INPUT: bills, an array/list of Bill references or pointers
total ← 0
FOR EACH bill IN bills
    total ← total + bill.total()
END FOR
OUTPUT total
END ALGORITHM
```

## Alternative: tagged structure + switch
A single record can store a type tag and fields for every possible bill category. `total()` switches on the tag and applies the relevant formula. Totaling n bills remains O(n), and each switch is O(1) for a fixed number of types. The record may waste space because it must reserve fields for the largest category. Adding a bill type changes the switch and often the shared record, whereas a derived class can be added behind the stable Bill interface.
