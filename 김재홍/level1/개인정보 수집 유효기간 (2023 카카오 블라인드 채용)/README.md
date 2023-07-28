# 정리
[[my tistory]]()

# 내 풀이
```kotlin
import java.time.*
import java.time.format.*

class Solution {
    fun solution(today: String, terms: Array<String>, privacies: Array<String>): IntArray {
        var answer: IntArray = intArrayOf()
        /**
         * 1. today: string -> localdate
         * 2. terms: string -> map<String, String>
         * 3. privacies.forEach -> 날짜 비교 후, answer에 index+1 추가
         */
        val formatter = DateTimeFormatter.ofPattern("yyyy.MM.dd")
        val todayToLocalDate = stringToLocalDate(today, formatter)
        val termsMap = stringToMapDividingBlank(terms)
        
        privacies.forEachIndexed { i, privacy ->
            val (string, term) = privacy.split(" ")
            var localDate = stringToLocalDate(string, formatter)

            var expirationDate: LocalDate = localDate.plusMonths(termsMap[term]!!.toLong())
            println("${i+1}번째, $expirationDate, 기간은 $term")
            
            if (expirationDate.getDayOfMonth() > 28) {
                val dayChangedByCond = expirationDate.getDayOfMonth() - 28
                expirationDate = expirationDate.plusMonths(1)
                expirationDate = expirationDate.withDayOfMonth(dayChangedByCond)
                println("28일 기준에 의한 변경 date: $expirationDate")
            }
            
            if (expirationDate.isEqual(todayToLocalDate) || expirationDate.isBefore(todayToLocalDate)) {
                answer += (i+1)
            }
            
        } 
        return answer
    }
    
    fun stringToLocalDate(date: String, formatter: DateTimeFormatter): LocalDate {
        return LocalDate.parse(date, formatter)
    }
    
    fun stringToMapDividingBlank(array: Array<String>): Map<String, String> {
        val map: MutableMap<String, String> = mutableMapOf()
        array.forEach {
            val (key, value) = it.split(" ")
            map[key] = value
        }
        
        return map
        
    }
}
```
