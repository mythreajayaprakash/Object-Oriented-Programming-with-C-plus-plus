# Task A3 – Abstract Payer interface

```text
              <<abstract>> Payer
       amountCovered(const Bill&) : double {pure virtual}
                 /       |        \
             SelfPay  Insurance  GovernmentScheme
```
- `SelfPay`: patient pays the full bill total.
- `Insurance`: stores a maximum cover and co-payment percentage. The insured portion is bounded by the remaining cover; the patient co-payment is not counted as insurer payment.
- `GovernmentScheme`: maps bill categories/package codes to fixed package rates and rejects unknown package codes.

Extension: add `CorporateTieUp : Payer` implementing only `amountCovered`. Existing Bill and payer classes remain unchanged because callers use the Payer interface.

Alternative: a function pointer or `std::function<double(const Bill&)>` can hold a runtime policy function. It is O(1) per call for this simple policy, but associated data such as cover limit needs a captured lambda/state object. A Payer class groups policy behaviour and state explicitly.
