# 정리
###[[tistory]](https://chivalrous-hyeop.tistory.com/8)

# 내 풀이
```kotlin
class Solution {
    val dat: MutableMap<Char, Int> = mutableMapOf()
    
    fun solution(keymap: Array<String>, targets: Array<String>): IntArray {
        var answer: IntArray = intArrayOf()
        /**
         * 1. keymap list의 문자열의 Char에 대 DAT 생성 (method 구현 : value = index 최소 값)
         * 2. targets list의 문자열에 대해 for loop를 돌며, DAT[key]에 해당하는 값을 찾아
              최소 버튼 클릭 수 값을 저장하는 변수에 해당 값을 더한다.
         * 3. 최소 버튼 클릭 수 값을 저장하는 변수를 IntArray에 더한다.
         * 번외) DAT에 값이 없으면 최소 버튼 클릭 수 값을 저장하는 변수 값은 -1이다.
         */
        keymap.forEach {
            println("keymap: $it")
            for (idx in 0 until it.length) {
                if (dat[it[idx]] == null) {
                    dat[it[idx]] = idx+1
                } else {
                    getMinValue(it[idx], idx+1) // method 구현
                }
            }
        }
        var result: Int = 0 // 최소 버튼 클릭 수 값을 저장하는 변수
        targets.forEach {
            for (char in it) {
                if (dat[char] == null) {
                    result = -1
                    break
                } else {
                    result += dat[char] ?: 0
                }
            }
            answer += result
            result = 0 // 초기화
        }
        
        return answer
    }
    
    // 최소 값 설정
    fun getMinValue(char: Char, increasedIndex: Int) {
        dat[char]?.let {
            println("key: $char, value: $it, now index: $increasedIndex")
            if (it > increasedIndex) {
                dat[char] = increasedIndex
                println("key: $char, change value: $increasedIndex")
            }
        }
    }
}
```
