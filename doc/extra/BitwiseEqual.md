## BitwiseEqual

* `(x ^ y)` 는 `!=`와 동치다.
그렇다면 `!(x ^ y)` 는 `==`와 동치다.

* 왜 GPU는 비트연산에 취약하다는 것 일까?
  * GPU는 부동 소수점 데이터 유형을 다뤄서?


---

> ### 📄 참고

* https://stackoverflow.com/questions/4161656/replacing-with-bitwise-operators
* https://stackoverflow.com/questions/4364879/integer-calculations-on-gpu
* https://stackoverflow.com/questions/8683720/performance-of-integer-and-bitwise-operations-on-gpu
* https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#arithmetic-instructions__throughput-native-arithmetic-instructions
