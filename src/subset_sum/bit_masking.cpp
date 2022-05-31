#include "assignment/subset_sum/bit_masking.hpp"

#include <cassert>  // assert

#include "assignment/bits.hpp"  // is_bit_set, mask2indices

namespace assignment {

  std::vector<std::vector<int>> SubsetSumBitMasking::search(const std::vector<int>& set, int target_sum) const {
    assert(target_sum > 0 && set.size() <= 16);

    std::vector<std::vector<int>> indices;

    const auto num_elems = static_cast<int>(set.size());  // N
    const int num_subsets = 1 << num_elems;               // 2^N

    // 1. Внешний цикл: пробегаемся по всем битовым маскам от 0..00 до 1..11
    for (int i =0; i < num_subsets; i++) {
      std::vector<int> array;
      // 2. Внутренний цикл: проверка разрядов битовой маски и генерация подмножества, ассоциирующегося с этой маской
      for (int j =0; j < num_elems; j++){
        if (is_bit_set(i,j)){
          array.push_back(j);
        }
      }
      // 3. Подсчет суммы текущего подмножества, сохранение индексов подмножества с целевой суммой в результат
      int sum = 0;
      for (int k = 0; k < array.size(); k++){
        sum += set[array[k]];
        // Tips: можно пропустить итерацию, если сумма текущего подмножества стала больше целевой суммы
        if (sum > target_sum){
          break;
        }
      }
      if (sum == target_sum){
        indices.push_back(array);
      }
    }
    return indices;
  }

}  // namespace assignment