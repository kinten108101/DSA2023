## Elementary
Direct hashing. h(k) = k
Modulo division. h(k) = k % M. M should be prime to minimize collision.

## Non-elementary

### Extraction
Digit extraction. For a number, extract the part that is identificative.
Mid square. mid(k^2) % M. 

### Reduce clustering
Folding. h(123456789) = (123 + 456 + 789) % M or = (321 + 456 + 987) % M
Rotation. Shift the key before hashing. Increases key gap.

Pseudo-random:
```py
h(k) = (A*k + B) % M
```

# Collision Resolution
## Closed Addressing
- Linked list, if there are few collisions 
- Bucket hashing, if there are many collisions. Then do sequential probing
## Open Addressing
hash-probe function. hp(k, p)
some implementations:
- Sequential (linear) probing
```py
hp(k,p) = (h(k) + p) % m
```
May cause primary clustering
- Quadratic probing
```py
hp(k,p) = (h(k) + p^2) % m
```
May cause secondary clustering
- Double hashing
```py
hp(k,p) = (h(k) + p*_h(k)) % m
```
- Key Offset
```py
hp(k,p) = (h(k) + p*(k/m)) % m
```

One-way hashing. Checksum