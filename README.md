# CLI Calculator
This is a C++ program that converts an infix expression to Reverse Polish Notation,
then, evaluates the expression in the postfix notation.

## Supported operations
* **Addition**: $+$
* **Subtraction**: $-$
* **Multiplication**: $*$
* **Division**: $/$
* **Exponentiation**: $\wedge$
* **Rooting**: either square roots, 'sqrt' or $\wedge{1/k}$ for the $k$-th root
* **Sine**, **Cosine**, **Tangent**: 'sin', 'cos' and 'tan', respectively
* **Logarithm**: for base 10, use 'log'; for base $e$, use 'ln'; for any other base, feel free to use the change of base formula:  
$$log_b(x) = \frac{log_c(x)}{log_c(b)} \: | \: c \in \{e, 10\}$$

## Constants
The following constants are used:
* $\pi$, provided by `std::numbers::pi` (see `include/constants.h`)
* $e$, provided by `std::numbers::e` (see `include/constants.h`)