# Project Report: Parallel Image Processing Using Google Test and CI


## 1. Introduction
The project implements optimized BMP image processing operations using parallel computing (OpenMP). To verify performance and correctness, an automated testing system based on Google Test with CI integration was developed.


## 2. Testing Architecture

### Key components:

Google Test Framework: Unit tests for verifying correctness and performance.
GitHub Actions: CI pipeline for automated testing.
GCC Compiler: Build with -O3 optimization and OpenMP support (-fopenmp).

### Test scenario:

1. Trigger CI
2. Install dependencies
3. Compile tests
4. Load test image
5. Execute tests
6. Generate performance report


## 3. Test Results
### Correctness tests: 
#### Passed ✅

CI Output:
![PrtScCI1](./PrtScCI1.jpeg)

### Performance tests:

CI Output:
![PrtScCI2](./PrtScCI2.jpeg)

## 4. Key Performance Metrics

------------------------------------------------------------------------------------
Operation          Sequential Version    Parallel Version    Speedup CI    Status
------------------------------------------------------------------------------------
Rotate             0.111 ± 0.05s         0.077 ± 0.01s       1.45×         ✅ PASS
Gaussian Filter    0.889 ± 0.18s         0.710 ± 0.04s       1.25×         ✅ PASS
------------------------------------------------------------------------------------


## 5. Conclusion

#### The implemented testing system proved the effectiveness of parallel optimizations:
• Average operation speedup: 1.3×
• Guaranteed result correctness
• Stable operation in the CI pipeline
• Transparent performance reporting

The integration of Google Test with CI provides a reliable mechanism for quality and performance control, enabling confident project development while maintaining achieved optimizations.
