# Cpp-Performance-Monitor

## Overview

`Cpp-Performance-Monitor` is a C++ class you can use to easily keep track of how long different parts of your code take to run.

## Features

- Lightweight and header-only for easy integration.
- Supports multiple time resolutions: seconds, milliseconds, microseconds, and nanoseconds.
- Human-readable output for easy understanding.
- Ability to track multiple processes or sections.

## Requirements

- C++11 or higher
- Standard Library

## Installation

To include `Cpp-Performance-Monitor` in your project, simply add the header file to your source code and include is as shown

```cpp
#include "Performance.h"
```

## Example

```cpp
#include "Performance.h"

int main() {
    Performance perf;

    int process_sorting = perf.start("Sorting Algorithm", Performance::resolution::milliseconds);

    // Your code here
    // ...

    perf.stop(process_sorting);
    perf.show_results();

    return 0;
}

```

```
---------------------------------------------------------------------------
                             Performance List
---------------------------------------------------------------------------

Sorting Algorithm                                                      0 ms

---------------------------------------------------------------------------
```

## Contact

For any issues, questions, or contributions, feel free to open an issue on this GitHub repository.
