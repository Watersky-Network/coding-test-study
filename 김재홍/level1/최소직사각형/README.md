# 내 풀이
```kotlin
class Solution {
    var maxValue: Int = 0
    var maxValueColumn: Int = 0
    lateinit var input: MutableList<MutableList<Int>>
    
    fun solution(sizes: Array<IntArray>): Int {
        var answer: Int = 0
        /**
         * 1. input -> list
         * 2. max value 찾고, 값이 속한 컬럼 찾기 : 가로(0), 세로(1)
         * 3. max value가 속한 컬럼을 우선하여 내림 차순 정렬
         * 4. max value가 속하지 않은 컬럼 값이 속한 컬럼보다 크면, 두 값 swap
         * 5. 변경된 리스트에서 max value가 속하지 않은 컬럼의 max value 찾기
         * 6. 두 컬럼의 max value 곱하기
         */
        input = sizes.map { it.toMutableList() }.toMutableList()
        getMaxValueAndColumn(input)
        if (maxValueColumn == 0) {
            input.sortedWith(compareByDescending<MutableList<Int>> { it[0] }.thenByDescending { it[1] })
            swapValueByCond(0, 1)
            val maxValueOtherColumn: Int = getMaxValueInOtherColumn(1)
            answer = maxValue * maxValueOtherColumn
        } else {
            input.sortedWith(compareByDescending<MutableList<Int>> { it[1] }.thenByDescending { it[0] })
            swapValueByCond(1, 0)
            val maxValueOtherColumn: Int = getMaxValueInOtherColumn(0)
            answer = maxValue * maxValueOtherColumn
        }
        
        return answer
    }
    
    fun getMaxValueAndColumn(input: MutableList<MutableList<Int>>) {
        for (mom in input) {
            val son1: Int = mom[0]
            val son2: Int = mom[1]
            if (son1 > son2) {
                val tempMaxValue = maxOf(maxValue, son1)
                if (maxValue != tempMaxValue) {
                    maxValueColumn = 0
                    maxValue = maxOf(maxValue, son1)
                }

            } else {
                val tempMaxValue = maxOf(maxValue, son2)
                if (maxValue != tempMaxValue) {
                    maxValueColumn = 1
                    maxValue = maxOf(maxValue, son2)
                }
            }
            
        }

    }
    
    fun swapValueByCond(maxValueColumn: Int, otherColumn: Int) {
        for (mom in input) {
            val standard: Int = mom[maxValueColumn]
            val theOther: Int = mom[otherColumn]
            if (standard < theOther) {
                mom[maxValueColumn] = theOther
                mom[otherColumn] = standard
            }
        }
    }
    
    fun getMaxValueInOtherColumn(otherColumn: Int): Int {
        var maxValue: Int = 0
        for (mom in input) {
            val maxValueOtherColumn: Int = mom[otherColumn]
            maxValue = maxOf(maxValue, maxValueOtherColumn)
        }
        return maxValue
    }
}
```

# 다른 사람 풀이
```kotlin
class Solution {
    fun solution(sizes: Array<IntArray>): Int {
        val widths = mutableListOf<Int>()
        val heights = mutableListOf<Int>()

        sizes.forEach {
            widths.add(maxOf(it[0], it[1]))
            heights.add(minOf(it[0], it[1]))
        }
        
        return widths.maxOf{it} * heights.maxOf{it}
    }
}
```
